/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lsm6dsl.h"
#include <stdio.h>
#include "stm32f4xx_nucleo_bus.h"
#include "ASCII.h"
#include <stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define red 5
#define green 10

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
LSM6DSL_Object_t MotionSensor;
volatile uint32_t dataRdyIntReceived;

typedef struct {
    unsigned int flag:1;  // This defines a 1-bit unsigned integer
} BitField;
BitField dir_change;

#define TRUE 1
#define FALSE 0

volatile BitField timer_flag;

volatile BitField permissionToWrite;

BitField period;

volatile LSM6DSL_Axes_t acc_axes;

volatile int cnt = 0;

volatile int iterator = 0;



typedef struct {
    double acc_axes_x;
    int cnt;
} Data;


#define BUFFER_SIZE 3000
#define WINDOW_SIZE 10
volatile Data Buffer[BUFFER_SIZE];
volatile int read_idx = 0;
volatile int write_idx = 0;

volatile double movAvgSum = 0; // Sum for moving average calculation
volatile double window[WINDOW_SIZE] = {0};
volatile int window_index = 0;

volatile uint8_t num_data_in_window = 0;

uint8_t velocity_cnt = 0;

//Meanhez:

volatile double runningTotal = 0;
volatile int count = 0;
volatile double currentMean = 0;

double last_acceleration = 0.0;
double last_velocity = 0.0;
double current_velocity = 0.0;
double current_displacement = 0.0;
double centered_velocity = 0;

double runningTotalVelocity = 0.0;
uint8_t zeroCrossing = 0;
double filtered_velocity = 0;

double periodTime = 0;
double realPeriodTime = 0;
double startPeriod = 0;
double endPeriod = 0;

double delay = 0;
int delay_cnt = 0;
BitField delay_flag;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_SPI2_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
static void MEMS_Init(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */





uint8_t LED_CLEAR[6] = { 0 };
uint8_t LED_0[6] = { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t LED_1[6] = { 0x02, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t LED_2[6] = { 0x04, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t LED_3[6] = { 0x08, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t LED_4[6] = { 0x10, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t LED_5[6] = { 0x20, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t LED_6[6] = { 0x40, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t LED_7[6] = { 0x80, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t LED_8[6] = { 0x00, 0x01, 0x00, 0x00, 0x00, 0x00 };
uint8_t LED_9[6] = { 0x00, 0x02, 0x00, 0x00, 0x00, 0x00 };
uint8_t LED_10[6] = { 0x00, 0x04, 0x00, 0x00, 0x00, 0x00 };
uint8_t LED_11[6] = { 0x00, 0x08, 0x00, 0x00, 0x00, 0x00 };
uint8_t LED_12[6] = { 0x00, 0x10, 0x00, 0x00, 0x00, 0x00 };
uint8_t LED_13[6] = { 0x00, 0x20, 0x00, 0x00, 0x00, 0x00 };
uint8_t LED_14[6] = { 0x00, 0x40, 0x00, 0x00, 0x00, 0x00 };
uint8_t LED_15[6] = { 0x00, 0x80, 0x00, 0x00, 0x00, 0x00 };
uint8_t LED_16[6] = { 0x00, 0x00, 0x01, 0x00, 0x00, 0x00 };
uint8_t LED_17[6] = { 0x00, 0x00, 0x02, 0x00, 0x00, 0x00 };
uint8_t LED_18[6] = { 0x00, 0x00, 0x04, 0x00, 0x00, 0x00 };
uint8_t LED_19[6] = { 0x00, 0x00, 0x08, 0x00, 0x00, 0x00 };
uint8_t LED_20[6] = { 0x00, 0x00, 0x10, 0x00, 0x00, 0x00 };
uint8_t LED_21[6] = { 0x00, 0x00, 0x20, 0x00, 0x00, 0x00 };
uint8_t LED_22[6] = { 0x00, 0x00, 0x40, 0x00, 0x00, 0x00 };
uint8_t LED_23[6] = { 0x00, 0x00, 0x80, 0x00, 0x00, 0x00 };
uint8_t LED_24[6] = { 0x00, 0x00, 0x00, 0x01, 0x00, 0x00 };
uint8_t LED_25[6] = { 0x00, 0x00, 0x00, 0x02, 0x00, 0x00 };
uint8_t LED_26[6] = { 0x00, 0x00, 0x00, 0x04, 0x00, 0x00 };
uint8_t LED_27[6] = { 0x00, 0x00, 0x00, 0x08, 0x00, 0x00 };
uint8_t LED_28[6] = { 0x00, 0x00, 0x00, 0x10, 0x00, 0x00 };
uint8_t LED_29[6] = { 0x00, 0x00, 0x00, 0x20, 0x00, 0x00 };
uint8_t LED_30[6] = { 0x00, 0x00, 0x00, 0x40, 0x00, 0x00 };
uint8_t LED_31[6] = { 0x00, 0x00, 0x00, 0x80, 0x00, 0x00 };
uint8_t LED_32[6] = { 0x00, 0x00, 0x00, 0x00, 0x01, 0x00 };
uint8_t LED_33[6] = { 0x00, 0x00, 0x00, 0x00, 0x02, 0x00 };
uint8_t LED_34[6] = { 0x00, 0x00, 0x00, 0x00, 0x04, 0x00 };
uint8_t LED_35[6] = { 0x00, 0x00, 0x00, 0x00, 0x08, 0x00 };
uint8_t LED_36[6] = { 0x00, 0x00, 0x00, 0x00, 0x10, 0x00 };
uint8_t LED_37[6] = { 0x00, 0x00, 0x00, 0x00, 0x20, 0x00 };
uint8_t LED_38[6] = { 0x00, 0x00, 0x00, 0x00, 0x40, 0x00 };
uint8_t LED_39[6] = { 0x00, 0x00, 0x00, 0x00, 0x80, 0x00 };
uint8_t LED_40[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };
uint8_t LED_41[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x02 };
uint8_t LED_42[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x04 };
uint8_t LED_43[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x08 };
uint8_t LED_44[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x10 };
uint8_t LED_45[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x20 };
uint8_t LED_46[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x40 };
uint8_t LED_47[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x80 };

uint8_t LED_ARRAY[48][6] = {
		{ 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 }, // LED_0
		{ 0x02, 0x00, 0x00, 0x00, 0x00, 0x00 }, // LED_1
		{ 0x04, 0x00, 0x00, 0x00, 0x00, 0x00 }, // LED_2
		{ 0x08, 0x00, 0x00, 0x00, 0x00, 0x00 }, // LED_3
		{ 0x10, 0x00, 0x00, 0x00, 0x00, 0x00 }, // LED_4
		{ 0x20, 0x00, 0x00, 0x00, 0x00, 0x00 }, // LED_5
		{ 0x40, 0x00, 0x00, 0x00, 0x00, 0x00 }, // LED_6
		{ 0x80, 0x00, 0x00, 0x00, 0x00, 0x00 }, // LED_7
		{ 0x00, 0x01, 0x00, 0x00, 0x00, 0x00 }, // LED_8
		{ 0x00, 0x02, 0x00, 0x00, 0x00, 0x00 }, // LED_9
		{ 0x00, 0x04, 0x00, 0x00, 0x00, 0x00 }, // LED_10
		{ 0x00, 0x08, 0x00, 0x00, 0x00, 0x00 }, // LED_11
		{ 0x00, 0x10, 0x00, 0x00, 0x00, 0x00 }, // LED_12
		{ 0x00, 0x20, 0x00, 0x00, 0x00, 0x00 }, // LED_13
		{ 0x00, 0x40, 0x00, 0x00, 0x00, 0x00 }, // LED_14
		{ 0x00, 0x80, 0x00, 0x00, 0x00, 0x00 }, // LED_15
		{ 0x00, 0x00, 0x01, 0x00, 0x00, 0x00 }, // LED_16
		{ 0x00, 0x00, 0x02, 0x00, 0x00, 0x00 }, // LED_17
		{ 0x00, 0x00, 0x04, 0x00, 0x00, 0x00 }, // LED_18
		{ 0x00, 0x00, 0x08, 0x00, 0x00, 0x00 }, // LED_19
		{ 0x00, 0x00, 0x10, 0x00, 0x00, 0x00 }, // LED_20
		{ 0x00, 0x00, 0x20, 0x00, 0x00, 0x00 }, // LED_21
		{ 0x00, 0x00, 0x40, 0x00, 0x00, 0x00 }, // LED_22
		{ 0x00, 0x00, 0x80, 0x00, 0x00, 0x00 }, // LED_23
		{ 0x00, 0x00, 0x00, 0x01, 0x00, 0x00 }, // LED_24
		{ 0x00, 0x00, 0x00, 0x02, 0x00, 0x00 }, // LED_25
		{ 0x00, 0x00, 0x00, 0x04, 0x00, 0x00 }, // LED_26
		{ 0x00, 0x00, 0x00, 0x08, 0x00, 0x00 }, // LED_27
		{ 0x00, 0x00, 0x00, 0x10, 0x00, 0x00 }, // LED_28
		{ 0x00, 0x00, 0x00, 0x20, 0x00, 0x00 }, // LED_29
		{ 0x00, 0x00, 0x00, 0x40, 0x00, 0x00 }, // LED_30
		{ 0x00, 0x00, 0x00, 0x80, 0x00, 0x00 }, // LED_31
		{ 0x00, 0x00, 0x00, 0x00, 0x01, 0x00 }, // LED_32
		{ 0x00, 0x00, 0x00, 0x00, 0x02, 0x00 }, // LED_33
		{ 0x00, 0x00, 0x00, 0x00, 0x04, 0x00 }, // LED_34
		{ 0x00, 0x00, 0x00, 0x00, 0x08, 0x00 }, // LED_35
		{ 0x00, 0x00, 0x00, 0x00, 0x10, 0x00 }, // LED_36
		{ 0x00, 0x00, 0x00, 0x00, 0x20, 0x00 }, // LED_37
		{ 0x00, 0x00, 0x00, 0x00, 0x40, 0x00 }, // LED_38
		{ 0x00, 0x00, 0x00, 0x00, 0x80, 0x00 }, // LED_39
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 }, // LED_40
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x02 }, // LED_41
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x04 }, // LED_42
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x08 }, // LED_43
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x10 }, // LED_44
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x20 }, // LED_45
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x40 }, // LED_46
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x80 }  // LED_47
};

	/* for example: A:
	 *  0 1 1 1 0
	 	1 0 0 0 1
	    1 0 0 0 1
	    1 1 1 1 1
	    1 0 0 0 1
	    1 0 0 0 1
	    0 0 0 0 0
	    0 0 0 0 0

	 would look like this, now i write each column into a vector, and i will light up these leds
	 with a delay to display the character
	 */

void OutputEnable(void) {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET); // Set PB2 low to enable output
}

void OutputDisable(void) {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET); // Set PB2 high to disable output
}

void LatchEnable(void) {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);   // Set PB1 high
	HAL_Delay(1);  // Short delay to ensure the latch pulse is detected
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET); // Set PB1 low again
}


void SendLEDData(uint8_t *data) {
	for (int i = 5; i >= 0; i--) {  // Loop through data array backward
		HAL_SPI_Transmit(&hspi2, &data[i], 1, 100);  // Send 1 byte per driver
	}
	LatchEnable();  // Latch data once all have been transmitted
}

void CombineLEDData(uint8_t *result, uint8_t ledIdx) {

	for (int j = 0; j < 6; j++) {   // Each LED configuration is 6 bytes
		result[j] |= LED_ARRAY[ledIdx][j];
	}

}

void ShiftLEDData(uint8_t *result, uint8_t ledIdx) {

	for (int j = 0; j < 6; j++) {   // Each LED configuration is 6 bytes
		result[j] += LED_ARRAY[ledIdx][j];
	}

}

void CombineAndSendNEW(uint16_t ledMask,uint8_t color) {

	//if the value of a variable is 1, concatenate that LED into the sum
	char a = (ledMask & 0b1000000000000000) >> 15;
	char b = (ledMask & 0b0100000000000000) >> 14;
	char c = (ledMask & 0b0010000000000000) >> 13;
	char d = (ledMask & 0b0001000000000000) >> 12;
	char e = (ledMask & 0b0000100000000000) >> 11;
	char f = (ledMask & 0b0000010000000000) >> 10;
	char g = (ledMask & 0b0000001000000000) >> 9;
	char h = (ledMask & 0b0000000100000000) >> 8;
	char i = (ledMask & 0b0000000010000000) >> 7;
	char j = (ledMask & 0b0000000001000000) >> 6;
	char k = (ledMask & 0b0000000000100000) >> 5;
	char l = (ledMask & 0b0000000000010000) >> 4;
	char m = (ledMask & 0b0000000000001000) >> 3;
	char n = (ledMask & 0b0000000000000100) >> 2;
	char o = (ledMask & 0b0000000000000010) >> 1;
	char p = (ledMask & 0b0000000000000001);

	uint8_t LED[6] = { 0 };
/*
	if(color == red){

		for (int j = 0; j < 6; j++) {   // Each LED configuration is 6 bytes
				LED[j] |= 1;
			}
	}

	if(color == green){
		CombineLEDData(LED,green);
	}
*/

	if (a) {
		CombineLEDData(LED, 0);
	}
	if (b) {
		CombineLEDData(LED, 3);
	}
	if (c) {
		CombineLEDData(LED, 6);
	}
	if (d) {
		CombineLEDData(LED, 9);
	}
	if (e) {
		CombineLEDData(LED, 12);
	}
	if (f) {
		CombineLEDData(LED, 15);
	}
	if (g) {
		CombineLEDData(LED, 18);
	}
	if (h) {
		CombineLEDData(LED, 21);
	}
	if (i) {
		CombineLEDData(LED, 24);
	}
	if (j) {
		CombineLEDData(LED, 27);
	}
	if (k) {
		CombineLEDData(LED, 30);
	}
	if (l) {
		CombineLEDData(LED, 33);
	}
	if (m) {
		CombineLEDData(LED, 36);
	}
	if (n) {
		CombineLEDData(LED, 39);
	}
	if (o) {
		CombineLEDData(LED, 42);
	}
	if (p) {
		CombineLEDData(LED, 45);
	}

	SendLEDData(LED);
}

int32_t wrap_platform_read(uint8_t Address, uint8_t Reg, uint8_t *Bufp,
		uint16_t len) {
	Reg |= 0x80;
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	BSP_SPI1_Send(&Reg, 1);
	BSP_SPI1_SendRecv(&Reg, Bufp, len);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
	return 0;
}

int32_t wrap_platform_write(uint8_t Address, uint8_t Reg, uint8_t *Bufp,
		uint16_t len) {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	BSP_SPI1_Send(&Reg, 1);
	BSP_SPI1_Send(Bufp, len);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
	return 0;
}

void Delay() {

    delay = (realPeriodTime/2.0)/(9.0);
    delay_flag.flag = TRUE;

    while(delay_flag.flag){

    }
}

void Display_char(uint16_t (*ASCII)[9], int32_t x){


	//if we move it to the right read the array from 0->9
	if (x > 200 && dir_change.flag == 1) {
		for (int a = 0; a < 7; a++) {
			for (int i = 0; i < 9; i++) {
				CombineAndSendNEW(ASCII[a][i], red);
				HAL_Delay(calculateDelay());
			}
		}

		dir_change.flag ^= 1;
	}

	//if we move it to the left read the array backwards
	else if (x < -200 && dir_change.flag == 0) {
		for (int b = 0; b < 7; b++) {
			for (int j = 8; j >= 0; j--) {
				CombineAndSendNEW(ASCII[b][j], red);
				HAL_Delay(calculateDelay());
			}
		}

		dir_change.flag ^= 1;
	}
}

void Display(uint16_t ASCII[9], int32_t x) {

	if (x > 100 && dir_change.flag == 1) {

		for (int i = 0; i < 9; i++) {
			CombineAndSendNEW(ASCII[i], red);
			Delay();
		}

		dir_change.flag ^= 1;
	}

	else if (x < -200 && dir_change.flag == 0) {

		for (int j = 8; j >= 0; j--) {
			CombineAndSendNEW(ASCII[j], red);
			Delay();
		}

		dir_change.flag ^= 1;
	}
}

// Update mean and center data dynamically
double updateMeanAndCenterData(double newData) {
    runningTotal += newData;
    count++;
    currentMean = runningTotal / count;
    return newData - currentMean;
}

double centerVelocity(double newData) {
    runningTotal += newData;
    count++;
    currentMean = runningTotal / count;
    return newData - currentMean;
}



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM2) {
		LSM6DSL_ACC_GetAxes(&MotionSensor, &acc_axes);

		// Write data to the active buffer
		Buffer[write_idx].acc_axes_x = updateMeanAndCenterData((int) acc_axes.x);
		Buffer[write_idx].cnt = cnt;
		write_idx = (write_idx + 1) % BUFFER_SIZE;
		cnt++;

		timer_flag.flag = TRUE;
	}

	//Delay:
	if(delay_flag.flag){



		if(delay_cnt >= delay){

			delay_flag.flag = FALSE;
		}

		delay_cnt++;
	}
	delay_cnt=0;
}

void update_motion(double new_acceleration, double new_time, double delta_t) {
    static double velocity_buffer[WINDOW_SIZE] = {0};
    static int buffer_index = 0;
    static int samples_collected = 0;

    const double alpha = 0.98;  // Smoothing factor for velocity low-pass filter
    const double beta = 0.02;   // Smoothing factor for baseline estimation

    static double baseline = 0; // Baseline estimation for velocity

    double average_acceleration = (last_acceleration + new_acceleration) / 2.0;
    current_velocity += average_acceleration * delta_t;

    // Low-pass filter to smooth the velocity
    if (samples_collected == 0) {
        filtered_velocity = current_velocity;
    } else {
        filtered_velocity = alpha * current_velocity + (1 - alpha) * filtered_velocity;
    }

    // Estimate and update the baseline using a slower EMA
    baseline = beta * filtered_velocity + (1 - beta) * baseline;

    // Center the velocity by subtracting the estimated baseline
    centered_velocity = filtered_velocity - baseline;

    // Store the centered velocity in the buffer for analysis or other use
    velocity_buffer[buffer_index] = centered_velocity;
    buffer_index = (buffer_index + 1) % WINDOW_SIZE;

    if (samples_collected < WINDOW_SIZE) {
        samples_collected++;
    }

    // Additional computations
    double average_velocity = (last_velocity + centered_velocity) / 2.0;
    double abs_velocity = (fabs(last_velocity) + fabs(centered_velocity)) / 2.0;
    current_displacement += abs_velocity * delta_t;

    // Check for zero crossings
    if ((last_velocity > 0 && centered_velocity < 0) || (last_velocity < 0 && centered_velocity > 0)) {
        zeroCrossing++;
    }

    if (zeroCrossing == 2) {
        current_displacement = 0;
        zeroCrossing = 0;
    }

    // Update last values for next iteration
    last_acceleration = new_acceleration;
    last_velocity = centered_velocity;
}



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	period.flag = FALSE;
	delay_flag.flag = FALSE;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_SPI2_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  OutputDisable();  // Disable outputs during initialization
  SendLEDData(LED_CLEAR);
  OutputEnable();

  MEMS_Init();


  int delayTime;

  timer_flag.flag = 0;

  HAL_TIM_Base_Start_IT(&htim2);



  dir_change.flag =1; //using a flag to detect the change of direction


  uint16_t ASCII_ARRAY[7][9];

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 9; j++) {

			if (i == 0)
				ASCII_ARRAY[i][j] = BLANK[j];
			if (i == 1)
				ASCII_ARRAY[i][j] = E[j];
			if (i == 2)
				ASCII_ARRAY[i][j] = R[j];
			if (i == 3)
				ASCII_ARRAY[i][j] = I[j];
			if (i == 4)
				ASCII_ARRAY[i][j] = K[j];
			if (i == 5)
				ASCII_ARRAY[i][j] = A[j];
			if (i == 6)
				ASCII_ARRAY[i][j] = BLANK[j];
		}
	}



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {

		//Every 0.5ms write out the x axis value
		if (timer_flag.flag == TRUE) {

			update_motion(Buffer[read_idx].acc_axes_x, Buffer[read_idx].cnt,1);

			printf("%f %f %f %d\r\n", Buffer[read_idx].acc_axes_x,
					centered_velocity, current_displacement,
					Buffer[read_idx].cnt);

			read_idx = (read_idx + 1) % BUFFER_SIZE;

			timer_flag.flag = FALSE;
		}

		//Display(A,acc_axes.x);

		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV8;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 8400-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_LE_Pin|LED_OE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_LE_Pin LED_OE_Pin */
  GPIO_InitStruct.Pin = LED_LE_Pin|LED_OE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : LSM6DSL_INT1_EXTI11_Pin */
  GPIO_InitStruct.Pin = LSM6DSL_INT1_EXTI11_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(LSM6DSL_INT1_EXTI11_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
static void MEMS_Init(void)
{
  LSM6DSL_IO_t io_ctx;
  uint8_t id ;
  LSM6DSL_AxesRaw_t axes;
  float odr;

  /* Link I2C functions to the LSM6DSL driver */
	io_ctx.BusType = LSM6DSL_SPI_4WIRES_BUS;
	io_ctx.Address = 0;
	io_ctx.Init = BSP_SPI1_Init;
	io_ctx.DeInit = BSP_SPI1_DeInit;
	io_ctx.ReadReg = wrap_platform_read;
	io_ctx.WriteReg = wrap_platform_write;
	io_ctx.GetTick = BSP_GetTick;
	LSM6DSL_RegisterBusIO(&MotionSensor, &io_ctx);

  /* Read the LSM6DSL WHO_AM_I register */
  LSM6DSL_ReadID(&MotionSensor, &id);
  if (id != LSM6DSL_ID) {
    Error_Handler();
  }

  /* Initialize the LSM6DSL sensor */
  LSM6DSL_Init(&MotionSensor);

  /* Configure the LSM6DSL accelerometer (ODR, scale and interrupt) */
  LSM6DSL_ACC_SetOutputDataRate(&MotionSensor, 3330.0f); /* 26 Hz */
  LSM6DSL_ACC_SetFullScale(&MotionSensor, 8);          /* [-4000mg; +4000mg]  old*/
  LSM6DSL_ACC_Set_INT1_DRDY(&MotionSensor, ENABLE);    /* Enable DRDY */
  LSM6DSL_ACC_GetAxesRaw(&MotionSensor, &axes);        /* Clear DRDY */



  /* Start the LSM6DSL accelerometer */
  LSM6DSL_ACC_Enable(&MotionSensor);

  LSM6DSL_ACC_GetOutputDataRate(&MotionSensor, &odr);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == GPIO_PIN_11) {
    dataRdyIntReceived++;
  }
}

int _write(int fd, char * ptr, int len)
{
  HAL_UART_Transmit(&huart2, (uint8_t *) ptr, len, HAL_MAX_DELAY);
  return len;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
