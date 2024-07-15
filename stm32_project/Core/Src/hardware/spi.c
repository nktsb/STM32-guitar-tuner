/*
 * -----------------------------------------------------------------------------
 * Project       : STM32-guitar-tuner
 * File          : spi.c
 * Author        : nktsb
 * Created on    : 20.01.2022
 * GitHub        : https://github.com/nktsb/STM32-guitar-tuner
 * -----------------------------------------------------------------------------
 * Copyright (c) 2024 nktsb
 * All rights reserved.
 * -----------------------------------------------------------------------------
 */

#include "spi.h"

#define SPI1_DR_8b	(*(__IO uint8_t *)((uint32_t)SPI1 + 0x0C))

void spiInit(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	GPIOA->MODER |=  GPIO_MODER_MODER6_0;
	GPIOA->OTYPER &=  ~GPIO_OTYPER_OT_6;
	GPIOA->MODER &= ~(GPIO_MODER_MODER5 | GPIO_MODER_MODER7);
	GPIOA->MODER |=  GPIO_MODER_MODER5_1 | GPIO_MODER_MODER7_1;
	GPIOA->AFR[0] &= ~(GPIO_AFRL_AFRL5 | GPIO_AFRL_AFRL7);

	SPI1->CR1 |= SPI_CR1_CPOL | SPI_CR1_CPHA;
	SPI1->CR1 |= SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE;

	SPI1->CR2 |= SPI_CR2_DS_0 | SPI_CR2_DS_1 | SPI_CR2_DS_2;
	SPI1->CR1 &= ~SPI_CR1_LSBFIRST;
	SPI1->CR1 |= SPI_CR1_SSM;
	SPI1->CR1 |= SPI_CR1_SSI;
	SPI1->CR2 &= ~SPI_CR2_SSOE;
	SPI1->CR1 |= SPI_CR1_MSTR;
	SPI1->CR1 |= SPI_CR1_BR_0;
	SPI1->CR1 |= SPI_CR1_SPE;
}

void spiSendByte(uint8_t data)
{
	SPI1_DR_8b = data;
	while (!(SPI1->SR & SPI_SR_TXE));
	while (SPI1->SR & SPI_SR_BSY);
}

void spiSend(uint8_t *buff, uint8_t len)
{
	for(uint8_t i = 0; i < len; i++)
	{
		spiSendByte(*buff);
		buff++;
	}
}
