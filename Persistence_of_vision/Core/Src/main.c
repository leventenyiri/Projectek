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
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lsm6dsl.h"
#include <stdio.h>
#include "stm32f4xx_nucleo_bus.h"
#include "ASCII.h"
#include <stdlib.h>
#include <elapsed_time.h>
#include "DataProcessing.h"
#include "Display.h"
#include <inttypes.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
LSM6DSL_Object_t MotionSensor;
volatile uint32_t dataRdyIntReceived;
volatile uint8_t timer_flag = FALSE;
uint8_t disp_usable = FALSE;
uint8_t first_positive_velocity_detected = FALSE;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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



// Timer interrupt callback function
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM2) {
        timer_flag = TRUE;
    }
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
  elapsed_time_init();
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
  MX_TIM10_Init();
  /* USER CODE BEGIN 2 */
  OutputDisable();  // Disable outputs during initialization
  SendLEDData(LED_CLEAR);
  OutputEnable();

  MEMS_Init();

  timer_flag = FALSE;

  HAL_TIM_Base_Start_IT(&htim2);

  LatchEnable();

  LSM6DSL_Axes_t acc_axes;

  int acc_cnt = 0;

  uint8_t zeroCrossing = 0;

  double current_displacement = 0.0;

  double max_displacement = 0.0;

  double centered_velocity = 0.0;

  double start_point = 0.0;

  uint16_t ASCII_ARRAY[7][11];

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 11; j++) {

			if (i == 0)
				ASCII_ARRAY[i][j] = 0;
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
				ASCII_ARRAY[i][j] = 0;
			}
	}



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {


		if (timer_flag == TRUE) {

			elapsed_time_start(0);

			LSM6DSL_ACC_GetAxes(&MotionSensor, &acc_axes); // Get new accelerometer data

			//overflow_check();

			update_motion(updateMeanAndCenterData(acc_axes.x), acc_cnt,1,&zeroCrossing, &current_displacement, &max_displacement, &centered_velocity);

			acc_cnt++;

			if (disp_usable) {
				Display(ASCII_ARRAY, max_displacement, centered_velocity, current_displacement,&start_point);
			}


			// Using this if i want to gather data to display in matlab
			//printf("%f %f %f %d\r\n", updateMeanAndCenterData(acc_axes.x),
				//centered_velocity, current_displacement,
			//acc_cnt);

			//printf("%d %d \r\n",acc_axes.x, acc_cnt);


			timer_flag = FALSE;
			elapsed_time_stop(0);
		}



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
  LSM6DSL_ACC_SetOutputDataRate(&MotionSensor, 1660.0f); /* 3330 Hz */
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
