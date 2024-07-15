/*
 * -----------------------------------------------------------------------------
 * Project       : STM32-guitar-tuner
 * File          : spi.h
 * Author        : nktsb
 * Created on    : 20.01.2022
 * GitHub        : https://github.com/nktsb/STM32-guitar-tuner
 * -----------------------------------------------------------------------------
 * Copyright (c) 2024 nktsb
 * All rights reserved.
 * -----------------------------------------------------------------------------
 */

#ifndef __SPI_H__
#define __SPI_H__

#include "main.h"

#define csSet() GPIOA->ODR &= ~GPIO_ODR_6;
#define csReset() GPIOA->ODR |= GPIO_ODR_6;

void spiInit(void);
void spiSendByte(uint8_t data);
void spiSend(uint8_t *buff, uint8_t len);

#endif /* __SPI_H__ */
