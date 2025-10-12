/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "display.h"
#include <stdio.h>
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
ADC_HandleTypeDef hadc1;

RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
uint8_t rtc_tick;
RTC_TimeTypeDef clkTime;
RTC_DateTypeDef clkDate;
const char *weekDays[7] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_RTC_Init(void);
static void MX_ADC1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void Get_Time_Now(char *timeStr){
	HAL_RTC_GetTime(&hrtc, &clkTime, RTC_FORMAT_BIN);
	timeStr[0] = '0' + clkTime.Hours / 10;
	timeStr[1] = '0' + clkTime.Hours % 10;
	timeStr[2] = ':';
	timeStr[3] = '0' + clkTime.Minutes / 10;
	timeStr[4] = '0' + clkTime.Minutes % 10;
	timeStr[5] = ':';
	timeStr[6] = '0' + clkTime.Seconds / 10;
	timeStr[7] = '0' + clkTime.Seconds % 10;
	timeStr[8] = '\0';
}

void Get_Date_Now(char *dateStr, uint8_t format){
	HAL_RTC_GetDate(&hrtc, &clkDate, RTC_FORMAT_BIN);


	uint8_t pos = 0;
	if(format >> 0 & 1){
		const char *day = weekDays[clkDate.WeekDay];
        for(uint8_t i = 0; i < 3; i++){
        	dateStr[pos++] = day[i];
        }
		dateStr[pos++] = ' ';
	}

	if(format >> 1 & 1){
		dateStr[pos++] = '0' + clkDate.Date / 10;
		dateStr[pos++] = '0' + clkDate.Date % 10;
		dateStr[pos++] = '.';
	}

	if(format >> 2 & 1){
		dateStr[pos++] = '0' + clkDate.Month / 10;
		dateStr[pos++] = '0' + clkDate.Month % 10;
		dateStr[pos++] = '.';
	}

	if(format >> 3 & 1){
		dateStr[pos++] = '0' + clkDate.Year / 10;
		dateStr[pos++] = '0' + clkDate.Year % 10;
		dateStr[pos++] = '.';
	}


	dateStr[pos-1] = '\0';
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
  __HAL_RCC_PWR_CLK_ENABLE(); // PWR
  HAL_PWR_EnableBkUpAccess();// backup-домену
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_RTC_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
  HAL_ADCEx_Calibration_Start(&hadc1);//калебровка
  LCD_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  char timeStr[9];
  char dateStr[13] = {0}; //WWW DD/MM/YY
  uint8_t dataFormat = 0b1111;//YYMMDDWW
  uint32_t tp = 0;
  char str_tp[11];

  Get_Time_Now(timeStr);
  Get_Date_Now(dateStr, dataFormat);

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  LCD_Clear();

	  LCD_DrawText(8, 16, timeStr, 1);
	  LCD_DrawText(16, 36, dateStr, 0);

	  if (rtc_tick) {
	      rtc_tick = 0;
	      Get_Time_Now(timeStr);
		  //HAL_RTC_GetDate(&hrtc, &clkTime, RTC_FORMAT_BCD);
		  if(clkTime.Hours == 0x00 && clkTime.Minutes == 0x00 && (clkTime.Seconds == 0x00)){
			  Get_Date_Now(dateStr, dataFormat);
		  }
	  }

	  HAL_ADC_Start(&hadc1);
	  HAL_ADC_PollForConversion(&hadc1, 10);//10ms
	  tp = HAL_ADC_GetValue(&hadc1);

	  snprintf(str_tp, 11, "%lu", tp);
	  LCD_DrawText(16, 48, str_tp, 0);


	  HAL_Delay(256);
	  LCD_Update();

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_ADC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef DateToUpdate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */
  if (HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1) != 0x32F)
    {
  	  	sTime.Hours = 0x15;
  	    sTime.Minutes = 0x18;
  	    sTime.Seconds = 0x40;

  	    if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  	    {
  	      Error_Handler();
  	    }
  	    DateToUpdate.WeekDay = RTC_WEEKDAY_SATURDAY;
  	    DateToUpdate.Month = RTC_MONTH_OCTOBER;
  	    DateToUpdate.Date = 0x11;
  	    DateToUpdate.Year = 0x25;

  	    if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD) != HAL_OK)
  	    {
  	      Error_Handler();
  	    }

  	    HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x32F);//set flag
  	    //save DATE wdDDMMYY
  	    HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR2, DateToUpdate.WeekDay);
  	    HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR3, DateToUpdate.Date);
  	    HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR4, DateToUpdate.Month);
  	    HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR5, DateToUpdate.Year);
    }else{
  	    DateToUpdate.WeekDay = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR2);
  	    DateToUpdate.Date    = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR3);
  	    DateToUpdate.Month   = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR4);
  	    DateToUpdate.Year    = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR5);
  	    HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD);
    }
  /* USER CODE END Check_RTC_BKUP */

  /* USER CODE BEGIN RTC_Init 2 */
  HAL_NVIC_SetPriority(RTC_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(RTC_IRQn);
  __HAL_RTC_SECOND_ENABLE_IT(&hrtc, RTC_IT_SEC);
  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(P13_GPIO_Port, P13_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LCD_A0_Pin|LCD_RST_Pin|LCD_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : P13_Pin */
  GPIO_InitStruct.Pin = P13_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(P13_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_A0_Pin LCD_RST_Pin LCD_CS_Pin */
  GPIO_InitStruct.Pin = LCD_A0_Pin|LCD_RST_Pin|LCD_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
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
	  HAL_GPIO_TogglePin(P13_GPIO_Port, P13_Pin);
	  HAL_Delay(250);
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
