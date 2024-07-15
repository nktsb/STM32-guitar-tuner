/*
 * -----------------------------------------------------------------------------
 * Project       : STM32-guitar-tuner
 * File          : led_matrix.c
 * Author        : nktsb
 * Created on    : 20.01.2022
 * GitHub        : https://github.com/nktsb/STM32-guitar-tuner
 * -----------------------------------------------------------------------------
 * Copyright (c) 2024 nktsb
 * All rights reserved.
 * -----------------------------------------------------------------------------
 */
#include "led_matrix.h"
#include "spi.h"
#include "battery.h"
#include "screens.h"

typedef struct matrix_note_st{
	uint8_t trig;
	note_t note;
} matrix_note;

static const uint16_t led_array[][8]={

	{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}, //clear		- 0
	{0x0180, 0x0240, 0x0240, 0x03C0, 0x0240, 0x0000, 0xC000, 0xC000}, //A			- 1
	{0x0C50, 0x12F8, 0x1250, 0x1EF8, 0x1250, 0x0000, 0xC000, 0xC000}, //A#			- 2
	{0x0380, 0x0240, 0x0380, 0x0240, 0x0380, 0x0000, 0xC000, 0xC000}, //B			- 3
	{0x01C0, 0x0200, 0x0200, 0x0200, 0x01C0, 0x0000, 0xC000, 0xC000}, //C			- 4
	{0x0E50, 0x10F8, 0x1050, 0x10F8, 0x0E50, 0x0000, 0xC000, 0xC000}, //C#			- 5
	{0x0380, 0x0240, 0x0240, 0x0240, 0x0380, 0x0000, 0xC000, 0xC000}, //D			- 6
	{0x1C50, 0x12F8, 0x1250, 0x12F8, 0x1C50, 0x0000, 0xC000, 0xC000}, //D#			- 7
	{0x03C0, 0x0200, 0x0380, 0x0200, 0x03C0, 0x0000, 0xC000, 0xC000}, //E			- 8
	{0x03C0, 0x0200, 0x0380, 0x0200, 0x0200, 0x0000, 0xC000, 0xC000}, //F			- 9
	{0x1E50, 0x10F8, 0x1C50, 0x10F8, 0x1050, 0x0000, 0xC000, 0xC000}, //F#			- 10
	{0x01C0, 0x0200, 0x02C0, 0x0240, 0x01C0, 0x0000, 0xC000, 0xC000}, //G			- 11
	{0x0E50, 0x10F8, 0x1650, 0x12F8, 0x0E50, 0x0000, 0xC000, 0xC000}, //G#			- 12
	{0x0000, 0x0000, 0x0FE0, 0x0C30, 0x0C30, 0x0FE0, 0x0000, 0x0000}, //BAT LOW		- 13
	{0x0000, 0x0000, 0x0FE0, 0x0830, 0x0830, 0x0FE0, 0x0000, 0x0000}, //BAT CRIT	- 14
	{0x0000, 0x0030, 0x1E40, 0x0040, 0x0040, 0x1E40, 0x0030, 0x0000}, //=(      	- 15
	{0x0000, 0x0060, 0x1E10, 0x0010, 0x0010, 0x1E10, 0x0060, 0x0000}, //=)		 	- 16
	{0x0000, 0x0260, 0x0210, 0x0210, 0x0010, 0x1E10, 0x0060, 0x0000}  //;)		 	- 17

};

static struct timer clear_timer = {0};
static matrix_note display = {0};

void matrixSetNewNoteAndTrig(note_t note, uint8_t trig)
{
	display.note = note;
	display.trig = trig;
}

void matrixTask(void)
{
	if(timer_expired(&clear_timer))
	{
		timer_set(&clear_timer, CLEAR_PERIOD);
		matrixClear();
	}
	if(display.note && display.note <= G_DIES)
	{
		matrixDisplayNote(display.note, (uint8_t)display.trig);
		display.note = 0;
		timer_set(&clear_timer, CLEAR_PERIOD);
	}
}

void matrixTransmit(uint8_t address, uint16_t data)
{
	csSet();
	uint8_t tx_data[] = {address, (data >> 8), address, (data & 0xFF)};
	spiSend(tx_data, 4);
	csReset();
}

void matrixInit(void)
{
	spiInit();
	matrixTransmit(POWER_ADDR, 0x0000); //power down = 1
	matrixTransmit(DECODING_ADDR, 0x0000); //no decoding
	matrixTransmit(BRIGHT_ADDR, 0x0606); //brightness
	matrixTransmit(SCAN_LIM_ADDR, 0x0707); //scan_limit 8 leds
	matrixTransmit(TEST_ADDR, 0x0000); // test mode off
	matrixClear();
	matrixTransmit(POWER_ADDR, 0x0101); //power down = 0
	timer_set(&clear_timer, CLEAR_PERIOD);
}

void matrixDisplayNote(uint8_t note, uint8_t shift)
{
	uint16_t string = 0;

	for(uint8_t i = 0; i < 8; i++)
	{
		if(i < 6)
			string = led_array[note][i];
		else
			string = led_array[note][i] >> shift;

		matrixTransmit((i + 1), string);
	}
}

void matrixClear(void)
{
	for(uint8_t i = 0; i < 8; i++)
		matrixTransmit((i + 1), led_array[NONE][i]); //clear
}
