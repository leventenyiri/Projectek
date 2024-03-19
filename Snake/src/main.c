#include "em_device.h"
#include "em_chip.h"
#include "segmentlcd.h"
#include "segmentlcd_individual.h"
#include "functions.h"
#include "em_rmu.h"
#include "em_cmu.h"
#include "em_timer.h"
#include "em_gpio.h"
#include "em_core.h"
#include "bsp_stk_buttons.h"

volatile bool turn_left = false;
volatile bool turn_right = false;

void GPIO_EVEN_IRQHandler(void)
{ // PB1 is connected to pin 10 -> even GPIO ISR
	turn_right = true;
	GPIO_IntClear(0x0000FFFF); // Clear the interrupt flag for BUTTON1
}

void GPIO_ODD_IRQHandler(void)
{ // PB0 is connected to pin 9 -> odd GPIO ISR
	turn_left = true;
	GPIO_IntClear(0x0000FFFF); // Clear the interrupt flag for BUTTON0
}

int main(void)
{
	CHIP_Init();

	//*********************************************
	// * CMU configuration *
	//*********************************************
	// enable clock signals
	// CMU_ClockEnable(CMU_Clock_TypeDef clock, bool enable);
	CMU_ClockEnable(cmuClock_GPIO, true);
	CMU_ClockEnable(cmuClock_TIMER0, true);

	// *******************************
	// * TIMER config *
	// *******************************
	TIMER_Init_TypeDef TIMER0_init = TIMER_INIT_DEFAULT;
	TIMER0_init.prescale = timerPrescale1; // no prescale
	TIMER_Init(TIMER0, &TIMER0_init);
	TIMER_Enable(TIMER0, true); // timer starts counting

	// *******************************
	// * Initialize PB0 and PB1 *
	// *******************************
	// Configure PB0 and PB1 as input pins
	BSP_ButtonsInit();

	// Enable external interrupt for BUTTON0 and BUTTON1
	GPIO_IntConfig(gpioPortB, BUTTON0, false, true, true);
	GPIO_IntConfig(gpioPortB, BUTTON1, false, true, true);

	// Enable GPIO interrupts
	NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn); // clearing the interrupt flags before enabling the interrupts
	NVIC_ClearPendingIRQ(GPIO_ODD_IRQn);
	NVIC_EnableIRQ(GPIO_EVEN_IRQn);
	NVIC_EnableIRQ(GPIO_ODD_IRQn);

	// Enable LCD module
	SegmentLCD_Init(false);

	int snake_length = 1;
	position active_body_segments[37] = {}; // 6*5+7 on the first 6 minidisplays only 5 segments can be active
											// on the last one however there can be 7
	position food;							// stores the position of the food

	direction snake_direction = RIGHT;	  // 1 = right, 2 = up, 3 = left, 4 = down
										  // at the start the snake goes right
	direction previous_direction = RIGHT; // at the start the snake goes right

	bool dead = false;		// checks if the snake is alive
	bool blink_flag = true; // after the snake dies helps with the dot blinking
	position new_head = {}; // determines the next position of the head of the snake

	start_init(active_body_segments, &food); // we initialize the snake and the food's starting state

	while (!dead)
	{

		display_position(active_body_segments, snake_length); // display the position of the snake
		display_position(&food, 1);							  // display the food
		display_length(snake_length);						  // display the snake's length
		delay(5);

		if (turn_left || turn_right)
		{ // if any of the buttons were pressed, we change the snake's direction
			snake_direction = update_direction(snake_direction, turn_left, turn_right);

			turn_left = false; // turning off the interrupt detection flags after they were evaluated
			turn_right = false;
		}

		new_head = calculate_new_head(snake_direction, previous_direction, active_body_segments); // update the active_body_segments
																								  // according to the previous and current directions

		move(active_body_segments, snake_length, new_head); // takes the new head of the snake and adds it to the body

		dead = collision_with_snake(active_body_segments, snake_length); // checks if the snake ate itself

		snake_length = collision_with_food(active_body_segments, snake_length, &food); // checks if the snake ate the food

		previous_direction = snake_direction; // after updating, the previously current direction becomes the
											  // previous direction
	}

	turn_off_display(active_body_segments, snake_length); // after the snake died we turn off the snake and the food
	turn_off_display(&food, 1);

	while (1)
	{
		blink_dots(blink_flag); // if we died, then the dots will be blinking
		blink_flag = !blink_flag; //we invert the flag for the blinking effect
		delay(5);
	}
}
