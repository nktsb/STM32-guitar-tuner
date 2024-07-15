/*
 * -----------------------------------------------------------------------------
 * Project       : STM32-guitar-tuner
 * File          : battery.h
 * Author        : nktsb
 * Created on    : 20.01.2022
 * GitHub        : https://github.com/nktsb/STM32-guitar-tuner
 * -----------------------------------------------------------------------------
 * Copyright (c) 2024 nktsb
 * All rights reserved.
 * -----------------------------------------------------------------------------
 */

#ifndef __BATTERY_H__
#define __BATTERY_H__

#include "main.h"

void batteryCheckInit(void);
uint8_t batteryCheckTask(void);

#endif /* __BATTERY_H__ */
