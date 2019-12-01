/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LCD_BLA_ON_Pin GPIO_PIN_0
#define LCD_BLA_ON_GPIO_Port GPIOC
#define LCD_VDD_ON_Pin GPIO_PIN_1
#define LCD_VDD_ON_GPIO_Port GPIOC
#define LED_ON_Pin GPIO_PIN_10
#define LED_ON_GPIO_Port GPIOD
#define LCD_CS_Pin GPIO_PIN_9
#define LCD_CS_GPIO_Port GPIOA
#define BUT4_INPUT_Pin GPIO_PIN_0
#define BUT4_INPUT_GPIO_Port GPIOD
#define BUT3_INPUT_Pin GPIO_PIN_1
#define BUT3_INPUT_GPIO_Port GPIOD
#define BUT2_INPUT_Pin GPIO_PIN_2
#define BUT2_INPUT_GPIO_Port GPIOD
#define BUT1_INPUT_Pin GPIO_PIN_3
#define BUT1_INPUT_GPIO_Port GPIOD
#define BUT5_INPUT_Pin GPIO_PIN_4
#define BUT5_INPUT_GPIO_Port GPIOD
#define BUT6_INPUT_Pin GPIO_PIN_5
#define BUT6_INPUT_GPIO_Port GPIOD
#define BUT7_INPUT_Pin GPIO_PIN_6
#define BUT7_INPUT_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
