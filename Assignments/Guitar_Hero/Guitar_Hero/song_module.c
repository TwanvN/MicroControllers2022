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
} SONG_PATTERN;

SONG_PATTERN firstSong[10] = {
	{1, 0b00010000},
	{2, 0b00000010},
	{3, 0b00000100},
	{4, 0b00001000}	
};

void playFirstSong() {

		int index = 0;

		PORTF = firstSong[index].lightSequence;
		
		while(1) {

			if (PINB == 0b00010000 && index == 0)
			{
				index++;
				PORTF = firstSong[index].lightSequence;
			} else if (PINB == 0b00000010 && index == 1)
			{
				index++;
				PORTF = firstSong[index].lightSequence;
			} else if (PINB == 0b00000100 && index == 2)
			{
				index++;
				PORTF = firstSong[index].lightSequence;
			} else if (PINB == 0b00001000 && index == 3)
			{
				break;
			}
		}
}