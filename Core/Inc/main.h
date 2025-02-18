/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
//extern TIM_HandleTypeDef htim1;
extern char uart_msg_buf[256];
extern char hal_status_str[4][12];
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LCD_PX_D4_Pin GPIO_PIN_1
#define LCD_PX_D4_GPIO_Port GPIOC
#define LCD_PX_D5_Pin GPIO_PIN_2
#define LCD_PX_D5_GPIO_Port GPIOC
#define LCD_BSP_Pin GPIO_PIN_3
#define LCD_BSP_GPIO_Port GPIOC
#define LCD_PX_CLK_Pin GPIO_PIN_3
#define LCD_PX_CLK_GPIO_Port GPIOA
#define LCD_PX_D3_Pin GPIO_PIN_6
#define LCD_PX_D3_GPIO_Port GPIOA
#define LCD_PX_D2_Pin GPIO_PIN_7
#define LCD_PX_D2_GPIO_Port GPIOA
#define LCD_PX_D1_Pin GPIO_PIN_0
#define LCD_PX_D1_GPIO_Port GPIOB
#define LCD_PX_D0_Pin GPIO_PIN_1
#define LCD_PX_D0_GPIO_Port GPIOB
#define LCD_GSP_Pin GPIO_PIN_13
#define LCD_GSP_GPIO_Port GPIOB
#define LCD_GCK_Pin GPIO_PIN_15
#define LCD_GCK_GPIO_Port GPIOB
#define LCD_GEN_Pin GPIO_PIN_8
#define LCD_GEN_GPIO_Port GPIOA
#define LCD_INTB_Pin GPIO_PIN_4
#define LCD_INTB_GPIO_Port GPIOB
#define test_pin_Pin GPIO_PIN_5
#define test_pin_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
