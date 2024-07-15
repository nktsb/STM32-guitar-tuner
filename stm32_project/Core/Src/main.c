/*
 * -----------------------------------------------------------------------------
 * Project       : STM32-guitar-tuner
 * File          : main.c
 * Author        : nktsb
 * Created on    : 20.01.2022
 * GitHub        : https://github.com/nktsb/STM32-guitar-tuner
 * -----------------------------------------------------------------------------
 * Copyright (c) 2024 nktsb
 * All rights reserved.
 * -----------------------------------------------------------------------------
 */

#include "main.h"
#include "led_matrix.h"
#include "battery.h"
#include "screens.h"

void SystemClock_Config(void);

int main(void)
{
	SystemClock_Config();

	matrixInit();
	batteryCheckInit();

	delay(10);

	if(batteryCheckTask() == 0)
		lowBatScreen();

	helloWorldScreen();

	noteCalculationInit();

	while (1)
	{
		matrixTask();
		noteCalculationTask();
		batteryCheckTask();
	}
}

void SystemClock_Config(void)
{

	LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SYSCFG);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

	LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);
	while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_1);
	LL_RCC_HSE_Enable();

	while(LL_RCC_HSE_IsReady() != 1);
	LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLL_MUL_3, LL_RCC_PREDIV_DIV_1);
	LL_RCC_PLL_Enable();

	while(LL_RCC_PLL_IsReady() != 1);
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

	while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL);
	LL_Init1msTick(48000000);
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	NVIC_SetPriority(SysTick_IRQn, 3);
	LL_SetSystemCoreClock(48000000);
}


void Error_Handler(void)
{
	__disable_irq();
	while (1);
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
