/*
 * song_module.c
 *
 * Created: 16/03/2022 11:35:46
 *  Author: Twanv
 */ 

#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include "song_module.h"
#include "UTS_Ultrasone.h"

typedef struct SongPattern {
	int stepNumber;
	char lightSequence;
	int lightID;
	int pwmSignal;
} SONG_PATTERN;

SONG_PATTERN firstSong[10] = {
	{1, 0b00000010, 1, 800},
	{2, 0b00000100, 2, 1000},
	{3, 0b00001000, 3, 800},
	{4, 0b00010000, 4, 600},
	{5, 0b00000100, 2, 400},
	{5, 0b00001000, 3, 200},
	{5, 0b00000100, 2, 100}	
};

int currentLight = 0;

void updateLight() {
	currentLight++;
}

void playFirstSong() {
		
		if (PINB == 0b00000010 && firstSong[currentLight].lightID == 1 && currentDistance < 20)
		{
			OCR3B = firstSong[currentLight].pwmSignal;
		} else if (PINB == 0b00000100 && firstSong[currentLight].lightID == 2 && currentDistance < 20)
		{
			OCR3B = firstSong[currentLight].pwmSignal;
		} else if (PINB == 0b00001000 && firstSong[currentLight].lightID == 3 && currentDistance < 20)
		{
			OCR3B = firstSong[currentLight].pwmSignal;
		} else if (PINB == 0b00010000 && firstSong[currentLight].lightID == 4 && currentDistance < 20)
		{
			OCR3B = firstSong[currentLight].pwmSignal;
		} else {
			OCR3B = 0x00;
		}
		
		if (currentLight < (sizeof(firstSong) / sizeof(firstSong[0])))
		{	
			PORTF = firstSong[currentLight].lightSequence;
		}
		
}