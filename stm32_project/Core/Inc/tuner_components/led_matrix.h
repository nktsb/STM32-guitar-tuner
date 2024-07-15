/*
 * -----------------------------------------------------------------------------
 * Project       : STM32-guitar-tuner
 * File          : led_matrix.h
 * Author        : nktsb
 * Created on    : 20.01.2022
 * GitHub        : https://github.com/nktsb/STM32-guitar-tuner
 * -----------------------------------------------------------------------------
 * Copyright (c) 2024 nktsb
 * All rights reserved.
 * -----------------------------------------------------------------------------
 */

#ifndef __LED_MATRIX_H__
#define __LED_MATRIX_H__

#include "main.h"
#include "notes.h"

#define	POWER_ADDR		0x0C
#define DECODING_ADDR	0x09
#define	BRIGHT_ADDR		0x0A
#define	SCAN_LIM_ADDR	0x0B
#define	TEST_ADDR		0x0F

#define CLEAR_PERIOD 1000

void matrixInit(void);
void matrixTask(void);
void matrixTransmit(uint8_t address, uint16_t data);
void matrixDisplayNote(uint8_t note, uint8_t shift);
void matrixClear(void);
void matrixSetNewNoteAndTrig(note_t note, uint8_t trig);

#endif /* __LED_MATRIX_H__ */
