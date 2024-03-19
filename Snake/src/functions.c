/*
 * functions.c
 *
 *  Created on: Oct 2, 2023
 *      Author: nyiri
 */

#include "em_device.h"
#include "em_chip.h"
#include "segmentlcd.h"
#include "segmentlcd_individual.h"
#include "functions.h"
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "em_timer.h"
#include "em_core.h"

void turn_off_display(position *active_segments, int length)
{
	for (int i = 0; i < length; i++)
	{
		// first we choose which minidisplay is active, then we turn off the given segment in the
		// active minidisplay
		int active_disp = active_segments[i].minidisplay; // checks the current position's minidisplay value

		// we check which segment is active, and then turn it off
		switch (active_segments[i].segment)
		{
		case 'a':
			lowerCharSegments[active_disp].a = 0;
			break;
		case 'b':
			lowerCharSegments[active_disp].b = 0;
			break;
		case 'c':
			lowerCharSegments[active_disp].c = 0;
			break;
		case 'd':
			lowerCharSegments[active_disp].d = 0;
			break;
		case 'e':
			lowerCharSegments[active_disp].e = 0;
			break;
		case 'f':
			lowerCharSegments[active_disp].f = 0;
			break;
		case 'g':
			lowerCharSegments[active_disp].g = 0;
			lowerCharSegments[active_disp].m = 0;
			break;
		case 'm':
			lowerCharSegments[active_disp].m = 0;
			lowerCharSegments[active_disp].g = 0;
			break;
		}

		SegmentLCD_LowerSegments(lowerCharSegments);
	}
}

void number_decoder(int length, int display_num)
{ // decodes the number so the 7-segment can display it later

	switch (length)
	{

	case 0:
		upperCharSegments[display_num].a = 1;
		upperCharSegments[display_num].f = 1;
		upperCharSegments[display_num].b = 1;
		upperCharSegments[display_num].c = 1;
		upperCharSegments[display_num].e = 1;
		upperCharSegments[display_num].d = 1;
		break;
	case 1:
		upperCharSegments[display_num].b = 1;
		upperCharSegments[display_num].c = 1;
		break;
	case 2:
		upperCharSegments[display_num].a = 1;
		upperCharSegments[display_num].b = 1;
		upperCharSegments[display_num].g = 1;
		upperCharSegments[display_num].e = 1;
		upperCharSegments[display_num].d = 1;
		break;
	case 3:
		upperCharSegments[display_num].a = 1;
		upperCharSegments[display_num].b = 1;
		upperCharSegments[display_num].g = 1;
		upperCharSegments[display_num].c = 1;
		upperCharSegments[display_num].d = 1;
		break;
	case 4:
		upperCharSegments[display_num].f = 1;
		upperCharSegments[display_num].g = 1;
		upperCharSegments[display_num].b = 1;
		upperCharSegments[display_num].c = 1;
		break;
	case 5:
		upperCharSegments[display_num].a = 1;
		upperCharSegments[display_num].f = 1;
		upperCharSegments[display_num].g = 1;
		upperCharSegments[display_num].c = 1;
		upperCharSegments[display_num].d = 1;
		break;
	case 6:
		upperCharSegments[display_num].f = 1;
		upperCharSegments[display_num].g = 1;
		upperCharSegments[display_num].e = 1;
		upperCharSegments[display_num].d = 1;
		upperCharSegments[display_num].c = 1;
		break;
	case 7:
		upperCharSegments[display_num].a = 1;
		upperCharSegments[display_num].b = 1;
		upperCharSegments[display_num].c = 1;
		break;
	case 8:
		upperCharSegments[display_num].a = 1;
		upperCharSegments[display_num].f = 1;
		upperCharSegments[display_num].g = 1;
		upperCharSegments[display_num].b = 1;
		upperCharSegments[display_num].c = 1;
		upperCharSegments[display_num].e = 1;
		upperCharSegments[display_num].d = 1;
		break;
	case 9:
		upperCharSegments[display_num].a = 1;
		upperCharSegments[display_num].f = 1;
		upperCharSegments[display_num].g = 1;
		upperCharSegments[display_num].b = 1;
		upperCharSegments[display_num].c = 1;
	}
}

void upperCharSegments_0()
{ // zeroes out the upper segments
	for (int display_num = 0; display_num < 2; display_num++)
	{
		upperCharSegments[display_num].a = 0;
		upperCharSegments[display_num].b = 0;
		upperCharSegments[display_num].c = 0;
		upperCharSegments[display_num].d = 0;
		upperCharSegments[display_num].e = 0;
		upperCharSegments[display_num].f = 0;
		upperCharSegments[display_num].g = 0;
	}
}

void display_length(int length)
{

	upperCharSegments_0();
	SegmentLCD_UpperSegments(upperCharSegments); // we have to turn off the numbers that have already been displayed
												 // otherwise the display will become nonsense

	int upper_decimal = length / 10; // to get the upper decimal we have to divide the length by 10

	int lower_decimal = length - 10 * upper_decimal;

	number_decoder(lower_decimal, 0); // we activate the needed segments with the decoder, on the first( number 0) display

	if (upper_decimal != 0)
	{
		number_decoder(upper_decimal, 1); // if the number has at least two digits, then we display the upper number too
	}

	SegmentLCD_UpperSegments(upperCharSegments);
}

void blink_dots(int blinkFlag)
{

	if (blinkFlag == 1)
	{
		// Turn on all dots
		SegmentLCD_Symbol(LCD_SYMBOL_DP2, 1);
		SegmentLCD_Symbol(LCD_SYMBOL_DP3, 1);
		SegmentLCD_Symbol(LCD_SYMBOL_DP4, 1);
		SegmentLCD_Symbol(LCD_SYMBOL_DP5, 1);
		SegmentLCD_Symbol(LCD_SYMBOL_DP6, 1);
	}
	else
	{
		// Turn off all dots
		SegmentLCD_Symbol(LCD_SYMBOL_DP2, 0);
		SegmentLCD_Symbol(LCD_SYMBOL_DP3, 0);
		SegmentLCD_Symbol(LCD_SYMBOL_DP4, 0);
		SegmentLCD_Symbol(LCD_SYMBOL_DP5, 0);
		SegmentLCD_Symbol(LCD_SYMBOL_DP6, 0);
	}
}

void display_position(position *active_segments, int length)
{

	for (int i = 0; i < length; i++)
	{
		// first we choose which minidisplay is active, then we display the given segment in the
		// active minidisplay
		int active_disp = active_segments[i].minidisplay; // checks the current position's minidisplay value

		// we check which segment is active, and then display it
		switch (active_segments[i].segment)
		{
		case 'a':
			lowerCharSegments[active_disp].a = 1;
			break;
		case 'b':
			lowerCharSegments[active_disp].b = 1;
			break;
		case 'c':
			lowerCharSegments[active_disp].c = 1;
			break;
		case 'd':
			lowerCharSegments[active_disp].d = 1;
			break;
		case 'e':
			lowerCharSegments[active_disp].e = 1;
			break;
		case 'f':
			lowerCharSegments[active_disp].f = 1;
			break;
		case 'g':
			lowerCharSegments[active_disp].g = 1;
			lowerCharSegments[active_disp].m = 1;
			break;
		case 'm':
			lowerCharSegments[active_disp].m = 1;
			lowerCharSegments[active_disp].g = 1;
			break;
		}

		SegmentLCD_LowerSegments(lowerCharSegments); // turns the selected segments on
	}
}

void delay(int divider)
{
	for (int d = 0; d < 1500000 / divider; d++); //software delay function

}

position G_snake_direction(direction snake_direction, direction previous_direction, position *snake)
{

	position new_head = snake[0];
	switch (previous_direction)
	{ // we check where we were going before changing directions
	case RIGHT:
		switch (snake_direction)
		{ // knowing where we were previously, we know where we need to
			// go next given a specific direction
		case RIGHT:
			new_head.minidisplay = snake[0].minidisplay + 1; // e.g.: if we were going right previously, then we
															 // just need to go to the next minidisplay
			break;
		case UP:
			if (snake[0].minidisplay == 6)
			{ // e.g.: if we were going right previously, then
				// if we go up, and we were on G/M then now we have to
				// go to 'f' segment of the next minidisplay
				// here the exception is if we were on the last minidisplay
				// then we have to use the 'b' and 'c' segments too, which we
				// normally wouldnt, so in this case we have to go to the 'b' segment
				new_head.segment = 'b';
			}
			else
			{
				new_head.minidisplay = snake[0].minidisplay + 1;
				new_head.segment = 'f';
			}
			break;
		case DOWN:
			if (snake[0].minidisplay == 6)
			{ // e.g.: if we were going right before, and now we are going down
				// then we were on G/M then we have to go to the next minidisplays
				//'e' segment (exception is pretty much the same as the previous one)
				new_head.segment = 'c';
			}
			else
			{
				new_head.minidisplay = snake[0].minidisplay + 1;
				new_head.segment = 'e';
			}
			break;
		}
		break;

	case LEFT:
		switch (snake_direction)
		{
		case LEFT:
			new_head.minidisplay = snake[0].minidisplay - 1; // if we were going left previously and we are still going left
															 // then we just need to decrease the value of the minidisplay
			break;
		case UP:
			new_head.segment = 'f'; // if we were going left and now we are going up, then we will land on
									//'f' if we were on G/M previously
			break;
		case DOWN:
			new_head.segment = 'e'; // if we were going left and now we are going down, then we will land on
									//'e' if we were on G/M previously
			break;
		}
		break; // the rest of these type of direction functions all work in this manner
	}
	return new_head;
}

position M_snake_direction(direction snake_direction, direction previous_direction, position *snake)
{

	position new_head = snake[0];
	switch (previous_direction)
	{

	case RIGHT:
		switch (snake_direction)
		{

		case RIGHT:
			new_head.minidisplay = snake[0].minidisplay + 1;
			break;
		case UP:
			if (snake[0].minidisplay == 6)
			{
				new_head.segment = 'b';
			}
			else
			{
				new_head.minidisplay = snake[0].minidisplay + 1;
				new_head.segment = 'f';
			}
			break;
		case DOWN:
			if (snake[0].minidisplay == 6)
			{
				new_head.segment = 'c';
			}
			else
			{
				new_head.minidisplay = snake[0].minidisplay + 1;
				new_head.segment = 'e';
			}
			break;
		}
		break;

	case LEFT:
		switch (snake_direction)
		{

		case LEFT:
			new_head.minidisplay = snake[0].minidisplay - 1;
			break;
		case UP:
			new_head.segment = 'f';
			break;
		case DOWN:
			new_head.segment = 'e';
			break;
		}
		break;
	}
	return new_head;
}

position A_snake_direction(direction snake_direction, direction previous_direction, position *snake)
{

	position new_head = snake[0];
	switch (previous_direction)
	{

	case RIGHT:
		switch (snake_direction)
		{

		case RIGHT:
			new_head.minidisplay = snake[0].minidisplay + 1;
			break;
		case UP:
			if (snake[0].minidisplay == 6)
			{
				new_head.segment = 'c';
			}
			else
			{
				new_head.minidisplay = snake[0].minidisplay + 1;
				new_head.segment = 'e';
			}
			break;
		case DOWN:
			if (snake[0].minidisplay == 6)
			{
				new_head.segment = 'b';
			}
			else
			{
				new_head.minidisplay = snake[0].minidisplay + 1;
				new_head.segment = 'f';
			}
			break;
		}
		break;

	case LEFT:
		switch (snake_direction)
		{

		case LEFT:
			new_head.minidisplay = snake[0].minidisplay - 1;
			break;
		case UP:
			new_head.segment = 'e';
			break;
		case DOWN:
			new_head.segment = 'f';
			break;
		}
		break;
	}
	return new_head;
}
// case d and a works the same way , but because the way switch case works, i have to repeat it
position D_snake_direction(direction snake_direction, direction previous_direction, position *snake)
{

	position new_head = snake[0];
	switch (previous_direction)
	{

	case RIGHT:
		switch (snake_direction)
		{

		case RIGHT:
			new_head.minidisplay = snake[0].minidisplay + 1;
			break;
		case UP:
			if (snake[0].minidisplay == 6)
			{
				new_head.segment = 'c';
			}
			else
			{
				new_head.minidisplay = snake[0].minidisplay + 1;
				new_head.segment = 'e';
			}
			break;
		case DOWN:
			if (snake[0].minidisplay == 6)
			{
				new_head.segment = 'b';
			}
			else
			{
				new_head.minidisplay = snake[0].minidisplay + 1;
				new_head.segment = 'f';
			}
			break;
		}
		break;

	case LEFT:
		switch (snake_direction)
		{

		case LEFT:
			new_head.minidisplay = snake[0].minidisplay - 1;
			break;
		case UP:
			new_head.segment = 'e';
			break;
		case DOWN:
			new_head.segment = 'f';
			break;
		}
		break;
	}
	return new_head;
}

position F_snake_direction(direction snake_direction, direction previous_direction, position *snake)
{

	position new_head = snake[0];
	switch (previous_direction)
	{

	case UP:
		switch (snake_direction)
		{

		case RIGHT:
			new_head.segment = 'a';
			break;
		case UP:
			new_head.segment = 'e';
			break;
		case LEFT:
			new_head.minidisplay = snake[0].minidisplay - 1;
			new_head.segment = 'a';
		}
		break;

	case DOWN:
		switch (snake_direction)
		{

		case RIGHT:
			new_head.segment = 'g';
			break;
		case LEFT:
			new_head.minidisplay = snake[0].minidisplay - 1;
			new_head.segment = 'g';
			break;
		case DOWN:
			new_head.segment = 'e';
			break;
		}
		break;
	}
	return new_head;
}

position E_snake_direction(direction snake_direction, direction previous_direction, position *snake)
{

	position new_head = snake[0];
	switch (previous_direction)
	{

	case UP:
		switch (snake_direction)
		{

		case RIGHT:
			new_head.segment = 'g';
			break;
		case UP:
			new_head.segment = 'f';
			break;
		case LEFT:
			new_head.minidisplay = snake[0].minidisplay - 1;
			new_head.segment = 'g';
		}
		break;

	case DOWN:
		switch (snake_direction)
		{

		case RIGHT:
			new_head.segment = 'd';
			break;
		case LEFT:
			new_head.minidisplay = snake[0].minidisplay - 1;
			new_head.segment = 'd';
			break;
		case DOWN:
			new_head.segment = 'f';
			break;
		}
		break;
	}
	return new_head;
}

position C_snake_direction(direction snake_direction, direction previous_direction, position *snake)
{

	position new_head = snake[0];
	switch (previous_direction)
	{

	case UP:
		switch (snake_direction)
		{

		case RIGHT:
			new_head.minidisplay = snake[0].minidisplay + 1;
			new_head.segment = 'g';
			break;
		case UP:
			new_head.segment = 'b';
			break;
		case LEFT:
			new_head.segment = 'g';
		}
		break;

	case DOWN:
		switch (snake_direction)
		{

		case RIGHT:
			new_head.segment = 'd';
			new_head.minidisplay = snake[0].minidisplay + 1;
			break;
		case LEFT:
			new_head.segment = 'd';
			break;
		case DOWN:
			new_head.segment = 'b';
			break;
		}
		break;
	}
	return new_head;
}

position B_snake_direction(direction snake_direction, direction previous_direction, position *snake)
{

	position new_head = snake[0];
	switch (previous_direction)
	{

	case UP:
		switch (snake_direction)
		{

		case RIGHT:
			new_head.minidisplay = snake[0].minidisplay + 1;
			new_head.segment = 'a';
			break;
		case UP:
			new_head.segment = 'c';
			break;
		case LEFT:
			new_head.segment = 'a';
		}
		break;

	case DOWN:
		switch (snake_direction)
		{

		case RIGHT:
			new_head.segment = 'g';
			break;
		case LEFT:
			new_head.minidisplay = snake[0].minidisplay + 1;
			new_head.segment = 'g';
			break;
		case DOWN:
			new_head.segment = 'c';
			break;
		}
		break;
	}
	return new_head;
}

position calculate_new_head(direction snake_direction, direction previous_direction, position *snake)
{
	// we only need to check the head of the snake,
	// which is the first item in the active_body_segments array

	// first we look at where we are currently, and then make a decision about where to move next
	// in the light of the current direction that we are moving in

	direction snake_direction_ = snake_direction;
	direction previous_direction_ = previous_direction;
	position *snake_ = snake;
	position new_head = snake[0];

	switch (snake[0].segment)
	{ // first we look at where we are, depending on which segment we are on, we
	  // have to make different decisions regarding where to move next
	  // we also have to use different logic depending on which direction were we
	  // moving previously, which is handled in a function in every case
	  // There is also some comments about the inner workings of these functions at the start of
	  // the G_snake_direction function, they all work in the same manner
	case 'g':

		new_head = G_snake_direction(snake_direction_, previous_direction_, snake_);
		break;

	case 'm':

		new_head = M_snake_direction(snake_direction_, previous_direction_, snake_);
		break;

	case 'a':

		new_head = A_snake_direction(snake_direction_, previous_direction_, snake_);
		break;

	case 'd':

		new_head = D_snake_direction(snake_direction_, previous_direction_, snake_);
		break;

	case 'f':

		new_head = F_snake_direction(snake_direction_, previous_direction_, snake_);
		break;

	case 'e':

		new_head = E_snake_direction(snake_direction_, previous_direction_, snake_);
		break;

	case 'c':

		new_head = C_snake_direction(snake_direction_, previous_direction_, snake_);
		break;

	case 'b':

		new_head = B_snake_direction(snake_direction_, previous_direction_, snake_);
		break;
	}
	// if we go out of one side of the minidisplays, we have to come back in on the other side
	if (new_head.minidisplay == 7)
	{
		new_head.minidisplay = 0;
	}
	else if (new_head.minidisplay == -1)
	{
		new_head.minidisplay = 6;
	}

	return new_head;
}


char convert_int_to_char(int randsegment)
{
	char randchar;

	switch (randsegment) //converts the int value into an eligible char value which can be displayed
	{
	case 0:
		randchar = 'a';
		break;
	case 1:
		randchar = 'f';
		break;
	case 2:
		randchar = 'g';
		break;
	case 3:
		randchar = 'e';
		break;
	case 4:
		randchar = 'd';
		break;
	case 5:
		randchar = 'c';
		break;
	case 6:
		randchar = 'b';
		break;
	}

	return randchar;
}

void generate_food(position *food, position *snake)
{
	int randsegment;
	int rand_minidisplay = (TIMER_CounterGet(TIMER0) % 7); // choose a random minidisplay (from 0 to 6)
														   // we get the random seed from TIMER0

	if (rand_minidisplay == 6)
	{												  // if the last minidisplay gets chosen, we can get one of the 7 segments selected
		randsegment = (TIMER_CounterGet(TIMER0) % 7); // choose a random segment (from 0 to 6)
	}
	else
	{												  // otherwise we can only choose from 5 different segments
		randsegment = (TIMER_CounterGet(TIMER0) % 5); // choose a random segment (from 0 to 4)
	}

	// we need to convert the randsegment to char
	food->minidisplay = rand_minidisplay;
	food->segment = convert_int_to_char(randsegment); //we have to convert the int values into char so that
													  //it can be displayed

	if (food->minidisplay == snake->minidisplay && food->segment == snake->segment)
		generate_food(food, snake); // if the apple spawns inside the snake, we generate a new one
}

void start_init(position *starting_segment, position *starting_food)
{

	starting_segment[0].minidisplay = 0; // the head is the first value in the array
	starting_segment[0].segment = 'g';	 // thats the starting position

	generate_food(starting_food, starting_segment);
}

/* calculate the new direction where the snake will go
					  UP
					  |
					  2
			 LEFT <-3   1 -> RIGHT
					  4
					  |
					 DOWN
pressing PB0 the snake rotates left, which increases current direction's value
pressing PB1 the snake rotates right, which decreases current direction's value
 */
direction update_direction(direction previous_direction, bool left, bool right)
{
	int new_direction = (int)previous_direction; // we cast previous_direction back to int
	if (left)
	{ // so that we can use int operations on it
		new_direction++;
		if (new_direction == 5)
			new_direction = 1;
	}

	if (right)
	{
		new_direction--;
		if (new_direction == 0)
			new_direction = 4;
	}
	return (direction)new_direction; // we cast the return value back to direction type
}


// we check if the snake ate itself
bool collision_with_snake(position *snake, int length)
{
	bool is_dead = false; // flag checks if the snake has collided with itself

	for (int i = 1; i < length; i++)
	{ // we skip the collision comparison for the head with itself
		if (snake[0].minidisplay == snake[i].minidisplay && snake[0].segment == snake[i].segment)
			is_dead = true;
	}
	return is_dead;
}

// we check if the snake has collided with the food
int collision_with_food(position *snake, int snake_length, position *food)
{
	int length = snake_length;
	if (snake[0].minidisplay == food->minidisplay && snake[0].segment == food->segment)
	{												   // check if the snake ate the food
		snake[length].minidisplay = food->minidisplay; // food makes the snake longer by attaching a segment to it's tail
		snake[length].segment = food->segment;
		length++; // snake becomes longer

		turn_off_display(food, 1); // after the food has been eaten, we turn the segment off
		generate_food(food, snake);
	}
	return length;
}

void move(position *snake, int snake_length, position snake_head)
{

	position new_snake[37] = {};
	position tail; // we will turn this off on the display
	tail = snake[snake_length - 1];

	turn_off_display(&tail, 1);

	for (int i = 1; i <= snake_length; i++)
	{

		new_snake[i].minidisplay = snake[i - 1].minidisplay; //we load the body of the snake into a helper array
															//but we shift each segment to the right
		new_snake[i].segment = snake[i - 1].segment;
	}

	new_snake[0].minidisplay = snake_head.minidisplay; // we load the new head into the first position of the new
													   // array
	new_snake[0].segment = snake_head.segment;


	for (int i = 0; i < snake_length; i++)
	{
		snake[i].minidisplay = new_snake[i].minidisplay; //we load the helper array back into the body of the snake
		snake[i].segment = new_snake[i].segment;
	}
}

