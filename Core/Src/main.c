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
#include "gpdma.h"
#include "icache.h"
#include "memorymap.h"
#include "octospi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>	// for sprintf()

#include "../ls012b7dd06_stm32_lib/ls012b7dd06_config.h"
#include "../ls012b7dd06_stm32_lib/ls012b7dd06.h"
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

uint8_t lcd_buf_1[OUT_DATA_BUF_SIZE] = {0};

char uart_msg_buf[256] = "No error.\r\n";
char hal_status_str[4][12] = {"HAL_OK\0", "HAL_ERROR\0", "HAL_BUSY\0", "HAL_TIMEOUT\0"};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void SystemPower_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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

  /* Configure the System Power */
  SystemPower_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_GPDMA1_Init();
  MX_ICACHE_Init();
  MX_OCTOSPI1_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_TIM1_Init();
  MX_TIM15_Init();
  MX_TIM6_Init();
  MX_TIM16_Init();
  /* USER CODE BEGIN 2 */

  HAL_StatusTypeDef lcd_status;
  lcd_init_t lcd_init = {
		  .hospi = &hospi1,
		  .hhalfline_tim = &htim15,
		  .hdelay_tim = &htim6,
		  .hadv_tim = &htim1,
		  .hpwr_tim = &htim16,
		  .hintb_port = LCD_INTB_GPIO_Port,
		  .intb_pin = LCD_INTB_Pin,
		  .buf1 = lcd_buf_1
  };

  LCD_init(0, &lcd_init);
  LCD_setActive(0);

  sprintf( uart_msg_buf, "OSPI after init status = 0x%08lX, OSPI error code = 0x%08lX\r\n",
  	  			hospi1.State, hospi1.ErrorCode );
  HAL_UART_Transmit( &huart1, (uint8_t *)uart_msg_buf, sizeof(uart_msg_buf), 10 );

  HAL_GPIO_TogglePin(test_pin_GPIO_Port, test_pin_Pin );
  HAL_Delay(50);
  HAL_GPIO_TogglePin(test_pin_GPIO_Port, test_pin_Pin );
  HAL_Delay(50);
  HAL_GPIO_TogglePin(test_pin_GPIO_Port, test_pin_Pin );
  HAL_Delay(50);
  HAL_GPIO_TogglePin(test_pin_GPIO_Port, test_pin_Pin );
  HAL_Delay(50);

  // Init frame
  LCD_cls();
  // LCD should not be busy yet,
  // so result checking can be avoided
  (void) LCD_displayFrame();

  HAL_Delay(50);

  LCD_PWM_power_enable();

  HAL_Delay(1000);

  // Draw a test figure
  LCD_drawTestFigure();

  do {
	  lcd_status = LCD_displayFrame();
	  HAL_Delay(1);
  } while (lcd_status != HAL_OK);

  HAL_Delay(5000);

  // Draw only a white square or line
  LCD_cls();
  lcd_colour_t colour;
  colour.val = COLOUR_WHITE;
//  LCD_drawSquare(60, 60, 140, 140, colour);
  LCD_drawLine(60, 60, 143, 167, colour);

  do {
  	  lcd_status = LCD_displayFrame();
  	  HAL_Delay(1);
  } while (lcd_status != HAL_OK);

  HAL_Delay(5000);

  // Shutdown frame
  LCD_cls();
  LCD_displayFrame();

  HAL_Delay(1000);

  LCD_PWM_power_disable();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_0;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLMBOOST = RCC_PLLMBOOST_DIV4;
  RCC_OscInitStruct.PLL.PLLM = 3;
  RCC_OscInitStruct.PLL.PLLN = 15;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLLVCIRANGE_1;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief Power Configuration
  * @retval None
  */
static void SystemPower_Config(void)
{
  PWR_PVDTypeDef sConfigPVD = {0};

  /*
   * PVD Configuration
   */
  sConfigPVD.PVDLevel = PWR_PVDLEVEL_0;
  sConfigPVD.Mode = PWR_PVD_MODE_NORMAL;
  HAL_PWR_ConfigPVD(&sConfigPVD);

  /*
   * Enable the PVD Output
   */
  HAL_PWR_EnablePVD();
/* USER CODE BEGIN PWR */
/* USER CODE END PWR */
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
  HAL_UART_Transmit( &huart1, (uint8_t*)uart_msg_buf, sizeof(uart_msg_buf), 10 );
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
