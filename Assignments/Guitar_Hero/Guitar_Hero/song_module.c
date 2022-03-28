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
} SONG_PATTERN;

SONG_PATTERN firstSong[10] = {
	{1, 0b00010000, 1},
	{2, 0b00000010, 2},
	{3, 0b00000100, 3},
	{4, 0b00001000, 4},
	{5, 0b00001000, 2}	
};

int currentLight = 0;

void updateLight() {
	currentLight++;
}

void playFirstSong() {

		PORTF = firstSong[currentLight].lightSequence;
		
		while(1) {
			
			/*
			if (PINB == 0b00010000 && firstSong[currentLight].lightID == 1)
			{
				currentLight++;
			} else if (PINB == 0b00000010 && firstSong[currentLight].lightID == 2)
			{
				currentLight++;
			} else if (PINB == 0b00000100 && firstSong[currentLight].lightID == 3)
			{
				currentLight++;
			} else if (PINB == 0b00001000 && firstSong[currentLight].lightID == 4)
			{
				currentLight++;
			}
			*/
			
			if (currentLight >= (sizeof(firstSong) / sizeof(firstSong[0])))
			{
				break;
			} else {
				PORTF = firstSong[currentLight].lightSequence;
			}
		}
}