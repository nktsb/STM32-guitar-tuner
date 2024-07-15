/*
 * -----------------------------------------------------------------------------
 * Project       : STM32-guitar-tuner
 * File          : screens.h
 * Author        : nktsb
 * Created on    : 20.01.2022
 * GitHub        : https://github.com/nktsb/STM32-guitar-tuner
 * -----------------------------------------------------------------------------
 * Copyright (c) 2024 nktsb
 * All rights reserved.
 * -----------------------------------------------------------------------------
 */

#ifndef __SCREENS_H__
#define __SCREENS_H__

#include "main.h"

typedef enum{
	LOW_BAT = 13,
	CRIT_BAT,
	SAD,
	SMILE,
	WINK
}icons;

void lowBatScreen(void);
void criticalBatScreen(void);
void helloWorldScreen(void);

#endif /* __SCREENS_H__ */
