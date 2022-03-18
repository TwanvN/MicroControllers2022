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

void playFirstSong() {

		int index = 0;

		PORTF = firstSong[index].lightSequence;
		
		while(1) {

			if (PINB == 0b00010000 && firstSong[index].lightID == 1)
			{
				index++;
			} else if (PINB == 0b00000010 && firstSong[index].lightID == 2)
			{
				index++;
			} else if (PINB == 0b00000100 && firstSong[index].lightID == 3)
			{
				index++;
			} else if (PINB == 0b00001000 && firstSong[index].lightID == 4)
			{
				index++;
			}
			
			if (index >= (sizeof(firstSong) / sizeof(firstSong[0])))
			{
				break;
			} else {
				PORTF = firstSong[index].lightSequence;
			}
		}
}