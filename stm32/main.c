/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MPU6050_ADDR 0xD0
#define PWR_MGMT_1_REG 0x6B
#define SMPLRT_DIV_REG 0x19
#define GYRO_CNFG_REG 0x1B
#define ACCEL_CNFG_REG 0x1C

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
 I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */
uint8_t Received[32];
char msg[16];
uint8_t data, Data;
uint8_t buffer[2], tuffer[6], cuffer[6];
int16_t gyro_raw[3], accel_raw[3];
float gyro_calibrated[3];
int16_t acc_total_vector;
float angle_pitch_gyro, angle_roll_gyro, angle_yaw_gyro;
float angle_pitch_acc, angle_roll_acc, angle_yaw_acc;
float angle_pitch, angle_roll, angle_yaw;
int i;
float prevtime, prevtime1, prevtime2, time1, time2, elapsedtime1, elapsedtime2;
float acc_total_vector_float;
float rec_powers_float[32];
HAL_StatusTypeDef set_gyro;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

	uint8_t Data[60]; // Tablica przechowujaca wysylana wiadomosc.
	uint16_t size = 0;

	size=sprintf(Data, "%s\r\n", Received);
	HAL_UART_Transmit_IT(&huart3, Data, 16); // Rozpoczecie nadawania danych z wykorzystaniem przerwan
	HAL_UART_Receive_IT(&huart3, Received, 32); // Ponowne włączenie nasłuchiwania
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int __io_putchar(int ch) {
	HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
	return 1;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
  int connection_iter = 0;
  /*konfiguracja rejestru PWR_MGMT_1_REG */
  data = 0x00;
  HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, PWR_MGMT_1_REG, 1, &data, 1, HAL_MAX_DELAY);

  /* konfiguracja rejestru GYRO_CNFG_REG (+-500deg/sek)*/
  data = 0x08;
  HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, GYRO_CNFG_REG, 1, &data, 1, HAL_MAX_DELAY);

  /* konfiguracja rejestru ACCEL_CNFG_REG (+-8g)/*/
  data = 0x10;
  HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, ACCEL_CNFG_REG, 1, &data, 1, HAL_MAX_DELAY);

  for(i=0; i<2000; i++) {

	  prevtime2 = time2;
	  time2 = HAL_GetTick();
	  elapsedtime2 = (time2-prevtime2)*1000;

	  cuffer[0] = 0x43;
	  HAL_I2C_Master_Transmit(&hi2c1, MPU6050_ADDR, cuffer, 1, HAL_MAX_DELAY);
	  HAL_I2C_Master_Receive(&hi2c1, MPU6050_ADDR, cuffer, 6, HAL_MAX_DELAY);

	  gyro_raw[0] = (cuffer[0] << 8 | cuffer [1]);
	  gyro_raw[1] = (cuffer[2] << 8 | cuffer [3]);
	  gyro_raw[2] = (cuffer[4] << 8 | cuffer [5]);

	  gyro_calibrated[0] += gyro_raw[0];
	  gyro_calibrated[1] += gyro_raw[1];
	  gyro_calibrated[2] += gyro_raw[2];

	  HAL_Delay(3);



  }

  gyro_calibrated[0] /= 2000;
  gyro_calibrated[1] /= 2000;
  gyro_calibrated[2] /= 2000;


  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
  HAL_Delay(1000);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  prevtime1 = time1;
	  time1 = HAL_GetTick();
	  elapsedtime1 = (time1 - prevtime1)*1000;

	  tuffer[0] = 0x3B;
	  HAL_I2C_Master_Transmit(&hi2c1, MPU6050_ADDR, tuffer, 1, HAL_MAX_DELAY);
	  HAL_I2C_Master_Receive(&hi2c1, MPU6050_ADDR, tuffer, 6, HAL_MAX_DELAY);

	  accel_raw[0] = (tuffer[0] << 8 | tuffer [1]);
	  accel_raw[1] = (tuffer[2] << 8 | tuffer [3]);
	  accel_raw[2] = (tuffer[4] << 8 | tuffer [5]);




	  cuffer[0] = 0x43;
	  HAL_I2C_Master_Transmit(&hi2c1, MPU6050_ADDR, cuffer, 1, HAL_MAX_DELAY);
	  HAL_I2C_Master_Receive(&hi2c1, MPU6050_ADDR, cuffer, 6, HAL_MAX_DELAY);

	  gyro_raw[0] = (cuffer[0] << 8 | cuffer [1]);
	  gyro_raw[1] = (cuffer[2] << 8 | cuffer [3]);
	  gyro_raw[2] = (cuffer[4] << 8 | cuffer [5]);

	  gyro_raw[0] -= gyro_calibrated[0];
	  gyro_raw[1] -= gyro_calibrated[1];
	  gyro_raw[2] -= gyro_calibrated[2];

	  angle_pitch_gyro += gyro_raw[0] * 0.0000611;
	  angle_roll_gyro += gyro_raw[1] * 0.0000611;
	  angle_yaw_gyro += gyro_raw[2] * 0.0000611;

	  angle_pitch_gyro += angle_roll_gyro * sin(gyro_raw[2] * 0.000001066);
	  angle_roll_gyro += angle_pitch_gyro * sin(gyro_raw[2] * 0.000001066);
	  angle_yaw_gyro += angle_yaw_gyro * sin(gyro_raw[2] * 0.000001066);

	  //całkowity wektor przyspieszenia kątowego
	  acc_total_vector = sqrt((accel_raw[0]*accel_raw[0])+(accel_raw[1]*accel_raw[1])+(accel_raw[2]*accel_raw[2]));

	  //wyliczenie kąta pitch na podstawie danych z akcelerometru
	  angle_pitch_acc = asin((float)accel_raw[0]/acc_total_vector)* 57.296;

	  //wyliczenie kąta roll na podstawie danych z akcelerometru
	  angle_roll_acc = asin((float)accel_raw[1]/acc_total_vector)* -57.296;

	  //wyliczenie kąta yaw na podstawie danych z akcelerometru
	  angle_yaw_acc = asin((float)accel_raw[2]/acc_total_vector)* -57.296;

	  angle_pitch_acc -= 0.00;
	  angle_roll_acc -= 0.00;
	  angle_yaw_acc -= 0.00;

	  if(set_gyro) {
		  angle_pitch = angle_pitch_gyro * 0.9996 + angle_pitch_acc * 0.0004;
		  angle_roll = angle_roll_gyro * 0.9996 + angle_roll_acc * 0.0004;
		  angle_yaw = angle_yaw_gyro * 0.9996 + angle_yaw_acc * 0.0004;
	  }
	  else
	  {
		  angle_pitch = angle_pitch_acc;
		  set_gyro = true;
	  }

	  while((HAL_GetTick() - prevtime)*1000 < 4000);
	  prevtime = HAL_GetTick();


	  HAL_UART_Receive_IT(&huart3, Received, 32);



    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if(connection_iter < 2) {
	  		  /* Connection LORA*/
	  		  do {
	  			  /* TX
	  			       AT+ID=DevEui
	  			       */
	  			  printf("AT+ID=DevEui\r\n");
	  			  HAL_Delay(1000);
	  			  /* RX
	  			      +ID: DevEui, 2C:F7:F1:20:24:90:07:11
	  			  */
	  			 /* TX
	  			     AT+ID=AppEui
	  			  */
	  			  printf("AT+ID=AppEui\r\n");
	  			  HAL_Delay(1000);
	  			  /* RX
	  			      +ID: AppEui, 00:00:00:00:00:00:00:00
	  			  */
	  			/* TX
	  			     AT+DR=EU868
	  			  */
	  			  printf("AT+DR=EU868\r\n");  // frequency868
	  			  HAL_Delay(1000);
	  			  /* RX
	  			       +DR: EU868
	  			  */
	  			 /* Tx
	  			      AT+CH=NUM,0-2
	  			  */
	  			  printf("AT+CH=NUM,0-2\r\n");   // channel
	  			  HAL_Delay(1000);
	  			  /* RX
	  			       +CH: NUM, 0-2
	  			  */


	  		      /* Tx
	  		           AT+MODE=LWOTAA
	  		           */
	  			  printf("AT+MODE=LWOTAA\r\n");
	  			  HAL_Delay(1000);
	  			  /* RX
	  			       +MODE: LWOTAA
	  			       */
	  			  /* Tx
	  			       AT+KEY=APPKEY
	  			  */
	  			  printf("AT+KEY=APPKEY,\"203D28CB595993050B89DBE1A43C1C8F\"\r\n");
	  			  HAL_Delay(1000);
	  			  /* RX
	  			     +KEY: APPKEY B71DED6CDA06912D9800C1031FBC5828
	  			  */

	  			  /* Tx
	  			       AT+ID
	  			  */
	  			  printf("AT+ID\r\n");
	  			  HAL_Delay(1000);
	  			  /* RX
	  			     +ID: DevAddr, 24:90:07:11
	  			     +ID: DevEui, 2C:F7:F1:20:24:90:07:11
	  			     +ID: AppEui, 00:00:00:00:00:00:00:00
	  			   */
	  			 /* Tx
	  			      AT+JOIN
	  			 */
	  			  printf("AT+JOIN\r\n");
	  			  HAL_Delay(10000);
	  			  /* RX
	  			       +JOIN: Start
	  			       +JOIN: NORMAL
	  			       +JOIN: Network joined
	  			       +JOIN: NetID 000013 DevAddr 26:01:5F:66
	  			       +JOIN: Done
	  			  */
	  			  connection_iter++;
	  		  }
	  		  while(connection_iter < 2);
	  	  }
	  	  //	/* Sending data (STRING FORMAT) */
	  	  //	printf("AT+MSG=HELLO\r\n");
	  	  //	HAL_Delay(10000);
	  	  //
	  	  //	/* Sending data (HEX FORMAT) */
	  	  //	printf("AT+MSGHEX=\"00 11 22 33 44\"\r\n");
	  	  //	HAL_Delay(10000);

          acc_total_vector_float = (float) acc_total_vector;

          //wysłanie danych z czujnika MCU6050
	  	  printf("AT+MSG=%s_%f_%f_%f_%f_%f\r\n",Received, angle_pitch_gyro, angle_yaw_gyro, angle_pitch_acc, angle_yaw_acc, acc_total_vector_float);
	  	  HAL_Delay(10000);

	  	  //wysłanie danych reprezentujących pierwszą odebraną moc
          printf("AT+MSG=%c%c%c%c\r\n",Received[9],
				  Received[12],
				  Received[13],
        		  Received[14]);
          HAL_Delay(10000);

          //wysłanie danych reprezentujących drugą odebraną moc
          printf("AT+MSG=%c%c%c%c\r\n",
				  Received[25],
				  Received[28],
        		  Received[29],
				  Received[30]);

	  	  HAL_Delay(10000);



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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 8;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00300F38;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

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
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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
