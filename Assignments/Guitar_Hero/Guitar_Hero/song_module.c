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

/************************************************************************/
/* Struct which contains 2 variables for the light to light up and the  */
/* corresponding pwm signal to send to the buzzer						*/
/************************************************************************/
typedef struct SongPattern {
	int lightID;
	int pwmSignal;
} SONG_PATTERN;

/************************************************************************/
/* Array of SongPattern structs to create a pattern for the lights      */
/* to light up.															*/
/************************************************************************/
SONG_PATTERN firstSong[10] = {
	{1, 800},
	{2, 1000},
	{3, 800},
	{6, 600},
	{2, 400},
	{3, 200},
	{2, 100}	
};

/************************************************************************/
/* Variable which keeps track off the current light                     */
/************************************************************************/
int currentLight = 0;

/************************************************************************/
/* Method which updates the current light                               */
/************************************************************************/
void updateLight() {
	currentLight++;
}

/************************************************************************/
/* Method which checks if a button is pressed corresponding to the      */
/* light and plays the corresponding frequency. If the button is		*/
/* incorrect the buzzer won't play any frequency.						*/
/************************************************************************/
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