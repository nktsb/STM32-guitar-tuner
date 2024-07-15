/*
 * -----------------------------------------------------------------------------
 * Project       : STM32-guitar-tuner
 * File          : stm_timers.c
 * Author        : nktsb
 * Created on    : 20.01.2022
 * GitHub        : https://github.com/nktsb/STM32-guitar-tuner
 * -----------------------------------------------------------------------------
 * Copyright (c) 2024 nktsb
 * All rights reserved.
 * -----------------------------------------------------------------------------
 */

#include "stm_timers.h"
#include "notes.h"

void initTIM1(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

	GPIOA->MODER &= ~(GPIO_MODER_MODER8);
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR8;
	GPIOA->MODER |=  GPIO_MODER_MODER8_1;
	GPIOA->AFR[1] &= ~(GPIO_AFRH_AFRH1);
	GPIOA->AFR[1] |= (0b0010);

	TIM1->PSC = 48 - 1;
	TIM1->ARR = 65535;

	TIM1->CCMR1 |= TIM_CCMR1_CC1S_0;
	TIM1->CCMR1 &= ~(TIM_CCMR1_IC1F | TIM_CCMR1_IC1PSC);

	TIM1->CCER &= ~TIM_CCER_CC1NP;

	TIM1->CCER |= TIM_CCER_CC1E;
	TIM1->SR &= ~TIM_SR_CC1IF;

	TIM1->DIER |= TIM_DIER_CC1IE;
	TIM1->CR1 |= TIM_CR1_CEN;

	NVIC_EnableIRQ(TIM1_CC_IRQn);
	NVIC_SetPriority(TIM1_CC_IRQn, 0);
}


void TIM1_CC_IRQHandler(void)
{
	TIM1->CNT = 0;
	TIM1->SR &= ~TIM_SR_CC1IF;

	updatePeriod(TIM1->CCR1);
}
