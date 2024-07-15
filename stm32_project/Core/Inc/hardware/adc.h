/*
 * -----------------------------------------------------------------------------
 * Project       : STM32-guitar-tuner
 * File          : adc.h
 * Author        : nktsb
 * Created on    : 20.01.2022
 * GitHub        : https://github.com/nktsb/STM32-guitar-tuner
 * -----------------------------------------------------------------------------
 * Copyright (c) 2024 nktsb
 * All rights reserved.
 * -----------------------------------------------------------------------------
 */

#ifndef __ADC_H__
#define __ADC_H__

#include "main.h"

void adcInit(void);
uint16_t adcRead(void);
void adcEnable(void);
void adcDisable(void);

#endif /* __ADC_H__ */
