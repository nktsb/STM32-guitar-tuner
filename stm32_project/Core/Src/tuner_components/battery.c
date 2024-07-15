/*
 * -----------------------------------------------------------------------------
 * Project       : STM32-guitar-tuner
 * File          : battery.c
 * Author        : nktsb
 * Created on    : 20.01.2022
 * GitHub        : https://github.com/nktsb/STM32-guitar-tuner
 * -----------------------------------------------------------------------------
 * Copyright (c) 2024 nktsb
 * All rights reserved.
 * -----------------------------------------------------------------------------
 */

#include "battery.h"
#include "adc.h"
#include "screens.h"

#define BATTERY_CHECK_PERIOD 20000

#define MAX_BATTERY_LVL 9900
#define LOW_BATTERY_LVL_THRESH 7000
#define CRIT_BATTERY_LVL_THRESH 5700

static struct timer battery_check_timer = {0};

void batteryCheckInit()
{
	adcInit();
	timer_set(&battery_check_timer, 0);
}

uint8_t batteryCheckTask(void)
{
	if(timer_expired(&battery_check_timer))
	{
		timer_set(&battery_check_timer, BATTERY_CHECK_PERIOD);
		adcEnable();
		uint16_t res = adcRead();
		adcDisable();

		res = (res * MAX_BATTERY_LVL)/(0xFFF + 1);

		if(CRIT_BATTERY_LVL_THRESH <= res && res < LOW_BATTERY_LVL_THRESH)
		{
			return 0;
		}
		else
		if(res < CRIT_BATTERY_LVL_THRESH)
		{
			criticalBatScreen();
			__disable_irq();
			while(1);
		}
		return 1;
	}
	return 1;
}
