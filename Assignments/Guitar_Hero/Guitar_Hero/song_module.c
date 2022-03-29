/*
 * song_module.c
 *
 * Created: 16/03/2022 11:35:46
 *  Author: Twanv
 */ 

#define F_CPU 8e6

#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include "song_module.h"

typedef struct SongPattern {
	int stepNumber;
	char lightSequence;
	int lightID;
	int pwmSignal;
} SONG_PATTERN;

SONG_PATTERN firstSong[10] = {
	{1, 0b00010000, 1, 10},
	{2, 0b00000010, 2, 20},
	{3, 0b00000100, 3, 50},
	{4, 0b00001000, 4, 60},
	{5, 0b00000010, 2, 90}	
};

int currentLight = 0;

void updateLight() {
	currentLight++;
}

void playFirstSong() {

		PORTF = firstSong[currentLight].lightSequence;
		
		while(1) {
			
			if (PINB == 0b00010000 && firstSong[currentLight].lightID == 1)
			{
				OCR3B = firstSong[currentLight].pwmSignal;
			} else if (PINB == 0b00000010 && firstSong[currentLight].lightID == 2)
			{
				OCR3B = firstSong[currentLight].pwmSignal;
			} else if (PINB == 0b00000100 && firstSong[currentLight].lightID == 3)
			{
				OCR3B = firstSong[currentLight].pwmSignal;
			} else if (PINB == 0b00001000 && firstSong[currentLight].lightID == 4)
			{
				OCR3B = firstSong[currentLight].pwmSignal;
			} else {
				OCR3B = 0x00;
			}
			
			if (currentLight >= (sizeof(firstSong) / sizeof(firstSong[0])))
			{
				break;
			} else {
				PORTF = firstSong[currentLight].lightSequence;
			}
		}
}