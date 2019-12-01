/**
  ******************************************************************************
  * File Name          : SPI.h
  * Description        : This file provides code for the configuration
  *                      of the SPI instances.
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __spi_H
#define __spi_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern SPI_HandleTypeDef hspi2;

/* USER CODE BEGIN Private defines */
#define LCD_CHAR_0 0b01111101
#define LCD_CHAR_1 0b00000101
#define LCD_CHAR_2 0b01101011
#define LCD_CHAR_3 0b01001111
#define LCD_CHAR_4 0b00010111
#define LCD_CHAR_5 0b01011110
#define LCD_CHAR_6 0b01111110
#define LCD_CHAR_7 0b00001101
#define LCD_CHAR_8 0b01111111
#define LCD_CHAR_9 0b01011111
#define LCD_FLAG_TAPPING 0b100000
#define LCD_FLAG_STOP 0b01
#define LCD_FLAG_FORWARD 0b1000
#define LCD_FLAG_REVERSE 0b1000000
#define LCD_FLAG_DIGIT_0 0b10000


/* USER CODE END Private defines */

void MX_SPI2_Init(void);

/* USER CODE BEGIN Prototypes */
void delay_nops(int nop_count);
void generate_spi_clock_pulse(void);
void initialize_lcd(void);
void write_to_lcd(uint16_t number_to_display, uint8_t flags);
uint8_t convert_num_to_7segment(uint8_t num);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ spi_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
