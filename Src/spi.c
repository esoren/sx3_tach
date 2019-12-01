/**
  ******************************************************************************
  * File Name          : SPI.c
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

/* Includes ------------------------------------------------------------------*/
#include "spi.h"

/* USER CODE BEGIN 0 */
#include "gpio.h"

void generate_spi_clock_pulse(void) {

	//The LCD has a 9th clock bit at the end of every transmission.
	//This function takes control of the CLK line from the SPI peripheral,
	//generates a pulse, then restores control back to the peripheral

	//First power cycle the LCD and backlight
	HAL_GPIO_WritePin(GPIOC, LCD_BLA_ON_Pin|LCD_VDD_ON_Pin, GPIO_PIN_RESET);
	delay_nops(1000);
	HAL_GPIO_WritePin(GPIOC, LCD_BLA_ON_Pin|LCD_VDD_ON_Pin, GPIO_PIN_SET);


	GPIO_InitTypeDef GPIO_InitStruct = {0};

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	delay_nops(1000);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	delay_nops(500);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	delay_nops(1000);
	return;
}

void delay_nops(int nop_count) {
	for (int i = 0; i < nop_count; i++) {
		asm("NOP");
	}
}

void initialize_lcd(void) {
	//The LCD has an initialization function which is not standard SPI.
	//It uses a 12 bit payload. Since its done only once, we can bit-bang it
	//and verify results with saleae

	//Take control of PC3 (MOSI) and PB13 (CLK) from the SPI peripheral.
	//The first time we call spi_generate_clock_pulse() the CLK pin will be
	//handled by SPI peripheral again.

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = GPIO_PIN_3; //DATA
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = GPIO_PIN_13; //CLOCK
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
	delay_nops(2000);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	delay_nops(500);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
	delay_nops(500);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
	delay_nops(500);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	delay_nops(500);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
	delay_nops(500);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
	for(int i = 0; i < 11; i++) {
		generate_spi_clock_pulse();
	}
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
	delay_nops(500);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
	delay_nops(1500);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	delay_nops(500);
	generate_spi_clock_pulse();
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
	for(int i = 0; i < 8; i++) {
		generate_spi_clock_pulse();
	}
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
	generate_spi_clock_pulse();
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
	generate_spi_clock_pulse();
	generate_spi_clock_pulse();
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
	delay_nops(1000);

	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
	delay_nops(1500);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);

	generate_spi_clock_pulse();
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
	for(int i = 0; i < 9; i++) {
		generate_spi_clock_pulse();
	}
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
	generate_spi_clock_pulse();
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET); //here
	generate_spi_clock_pulse();
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);


	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
	delay_nops(1500);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);

	generate_spi_clock_pulse();
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
	for(int i = 0; i < 8; i++) {
		generate_spi_clock_pulse();
	}
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
	generate_spi_clock_pulse();
	generate_spi_clock_pulse();
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
	generate_spi_clock_pulse();
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
	delay_nops(1000);

	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
	delay_nops(1500);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	generate_spi_clock_pulse();
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
	generate_spi_clock_pulse();
	generate_spi_clock_pulse();
	generate_spi_clock_pulse();
	generate_spi_clock_pulse();
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
	generate_spi_clock_pulse();
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
	generate_spi_clock_pulse();
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
	generate_spi_clock_pulse();
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
	generate_spi_clock_pulse();
	generate_spi_clock_pulse();
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
	generate_spi_clock_pulse();
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
	generate_spi_clock_pulse();
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);



	GPIO_InitStruct.Pin = GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);


	return; //whew...

}

void write_to_lcd(uint16_t number_to_display, uint8_t flags) {

	volatile uint8_t message[2];
	uint8_t digit0 = 0; //flags and ones
	uint8_t digit1 = 0; //tens
	uint8_t digit2 = 0; //hundreds
	uint8_t digit3 = 0; //thousands

	uint16_t temp = 0;

	temp = number_to_display;
	temp = temp % 10000; //ignore any extra digits
	digit3 = temp / 1000;
	temp = temp % 1000;
	digit2 = temp / 100;
	temp = temp % 100;
	digit1 = temp / 10;

	digit0 = LCD_FLAG_DIGIT_0 | flags;
	digit1 = convert_num_to_7segment(digit1);
	digit2 = convert_num_to_7segment(digit2);
	digit3 = convert_num_to_7segment(digit3);

	//first split out the digits into separate characters



	  HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	  delay_nops(200);
	  message[0] = 160;
	  message[1] = digit3;
	  HAL_SPI_Transmit(&hspi2, (uint8_t *)message, strlen(message), HAL_MAX_DELAY);
	  generate_spi_clock_pulse();
	  HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
	  delay_nops(1000);

	  HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	  delay_nops(200);
	  message[0] = 161;
	  message[1] = digit2;
	  HAL_SPI_Transmit(&hspi2, (uint8_t *)message, strlen(message), HAL_MAX_DELAY);
	  generate_spi_clock_pulse();
	  HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
	  delay_nops(1000);
	  HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);

	  delay_nops(200);
	  message[0] = 162;
	  message[1] = digit1;
	  HAL_SPI_Transmit(&hspi2, (uint8_t *)message, strlen(message), HAL_MAX_DELAY);
	  delay_nops(1000);

	  /*force data line low due to an issue where the 'STOP' flag was influenced by the ten's digit segment 'G' value. Hack. */
		GPIO_InitTypeDef GPIO_InitStruct = {0};
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
	  GPIO_InitStruct.Pin = GPIO_PIN_3; //DATA
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);



	  generate_spi_clock_pulse();
	  HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
	  delay_nops(1000);
	  HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);

	  GPIO_InitStruct.Pin = GPIO_PIN_3;
	  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	  delay_nops(200);
	  message[0] = 163;
	  message[1] = digit0;
	  HAL_SPI_Transmit(&hspi2, (uint8_t *)message, strlen(message), HAL_MAX_DELAY);
	  generate_spi_clock_pulse();
	  HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
	  delay_nops(1000);


	return;
}

uint8_t convert_num_to_7segment(uint8_t num) {
	uint8_t segment = 0;
	switch(num) {
	case(0):
		segment = LCD_CHAR_0;
		break;
	case(1):
		segment = LCD_CHAR_1;
		break;
	case(2):
		segment = LCD_CHAR_2;
		break;
	case(3):
		segment = LCD_CHAR_3;
		break;
	case(4):
		segment = LCD_CHAR_4;
		break;
	case(5):
		segment = LCD_CHAR_5;
		break;
	case(6):
		segment = LCD_CHAR_6;
		break;
	case(7):
		segment = LCD_CHAR_7;
		break;
	case(8):
		segment = LCD_CHAR_8;
		break;
	case(9):
		segment = LCD_CHAR_9;
		break;
	}



	return segment;
}
/* USER CODE END 0 */

SPI_HandleTypeDef hspi2;

/* SPI2 init function */
void MX_SPI2_Init(void)
{

  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi2.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(spiHandle->Instance==SPI2)
  {
  /* USER CODE BEGIN SPI2_MspInit 0 */

  /* USER CODE END SPI2_MspInit 0 */
    /* SPI2 clock enable */
    __HAL_RCC_SPI2_CLK_ENABLE();
  
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**SPI2 GPIO Configuration    
    PC3     ------> SPI2_MOSI
    PB13     ------> SPI2_SCK 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI2_MspInit 1 */

  /* USER CODE END SPI2_MspInit 1 */
  }
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==SPI2)
  {
  /* USER CODE BEGIN SPI2_MspDeInit 0 */

  /* USER CODE END SPI2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI2_CLK_DISABLE();
  
    /**SPI2 GPIO Configuration    
    PC3     ------> SPI2_MOSI
    PB13     ------> SPI2_SCK 
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_3);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_13);

  /* USER CODE BEGIN SPI2_MspDeInit 1 */

  /* USER CODE END SPI2_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
