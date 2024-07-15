/*
 * -----------------------------------------------------------------------------
 * Project       : STM32-guitar-tuner
 * File          : adc.c
 * Author        : nktsb
 * Created on    : 20.01.2022
 * GitHub        : https://github.com/nktsb/STM32-guitar-tuner
 * -----------------------------------------------------------------------------
 * Copyright (c) 2024 nktsb
 * All rights reserved.
 * -----------------------------------------------------------------------------
 */

#include "adc.h"

void adcInit(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	GPIOA->MODER |=  GPIO_MODER_MODER1;

	ADC1->CHSELR |= ADC_CHSELR_CHSEL1;
	ADC1->SMPR |= (ADC_SMPR_SMP_0 | ADC_SMPR_SMP_2);
	ADC1->SMPR &= ~ADC_SMPR_SMP_1;
	ADC1->CR |= ADC_CR_ADCAL;
	while(ADC1->CR & ADC_CR_ADCAL);
	ADC1->CR |= ADC_CR_ADEN;
}

void adcEnable(void)
{
	ADC1->CR |= ADC_CR_ADEN;
}

void adcDisable(void)
{
//    RCC->APB2ENR &= ~RCC_APB2ENR_ADC1EN;
	ADC1->CR &= ~ADC_CR_ADEN;
}

uint16_t adcRead(void)
{
	while(!(ADC1->ISR & ADC_ISR_ADRDY));

	ADC1->CR |= ADC_CR_ADSTART;
	while(!(ADC1->ISR & ADC_ISR_EOC));

	uint16_t adc_res = ADC1->DR;

	ADC1->CR |= ADC_CR_ADSTP;
	return adc_res;
}
