/*
 * -----------------------------------------------------------------------------
 * Project       : STM32-guitar-tuner
 * File          : notes.h
 * Author        : nktsb
 * Created on    : 20.01.2022
 * GitHub        : https://github.com/nktsb/STM32-guitar-tuner
 * -----------------------------------------------------------------------------
 * Copyright (c) 2024 nktsb
 * All rights reserved.
 * -----------------------------------------------------------------------------
 */

#ifndef __NOTES_H__
#define __NOTES_H__

#include "main.h"

typedef enum{
	NONE = 0,
	A,
	A_DIES,
	B,
	C,
	C_DIES,
	D,
	D_DIES,
	E,
	F,
	F_DIES,
	G,
	G_DIES,

	NOTES_NUM
} note_t;

typedef struct note_boards {
	uint16_t board_val;
	uint16_t frequency;
	note_t note;
} note_boards_st;

void noteCalculationInit(void);
void noteCalculationTask(void);
uint8_t collectNote(note_boards_st note_info, uint32_t freq);
void updatePeriod(uint32_t period_value);

#endif /* __NOTES_H__ */
