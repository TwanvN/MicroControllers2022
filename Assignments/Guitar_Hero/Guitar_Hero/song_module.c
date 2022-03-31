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
	int lightID;
	int pwmSignal;
} SONG_PATTERN;

SONG_PATTERN firstSong[10] = {
	{1, 800},
	{2, 1000},
	{3, 800},
	{4, 600},
	{2, 400},
	{3, 200},
	{2, 100}	
};

int currentLight = 0;

void updateLight() {
	currentLight++;
}

void playFirstSong() {
		
		if (PINB == 0b00000001 << firstSong[currentLight].lightID && currentDistance < 20)
		{
			OCR3B = firstSong[currentLight].pwmSignal;
		} else {
			OCR3B = 0x00;
		}
		
		if (currentLight < (sizeof(firstSong) / sizeof(firstSong[0])))
		{	
			PORTF = 0b00000001 << firstSong[currentLight].lightID;
		}
		
}