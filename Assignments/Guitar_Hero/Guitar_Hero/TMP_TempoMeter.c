/*
 * TMP_TempoMeter.c
 *
 * Created: 31-3-2022 09:13:16
 * Author: Jesse
 */
#include "TMP_TempoMeter.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <xc.h>

#include "UTS_Ultrasone.h"

#define HAND_TRIGGER_DISTANCE 32
#define MISSED_TRIGGER_DELAY 5

int lastTrigerValue = 0;
int numberOfTriggers = 0;

void TMP_init_meassure()
{
	UTS_Init();
	
	// Calling the first trigger of the ultrasone sensor
	UTS_Trigger();
}

void TMP_meassure()
{
	// Reading the value from the last trigger
	if ( (lastTrigerValue > HAND_TRIGGER_DISTANCE && currentDistance <= HAND_TRIGGER_DISTANCE) ||  
		 (lastTrigerValue <= HAND_TRIGGER_DISTANCE && currentDistance > HAND_TRIGGER_DISTANCE) )
	{
		// Change the number of triggers to zero, since value's are not equal
		numberOfTriggers = 0;
	}
	else numberOfTriggers++;	
	
	// Update the last trigger
	lastTrigerValue = currentDistance;
	
	//PORTD = numberOfTriggers;
	
	// Call the trigger again for next round
	UTS_Trigger();
}

int TMP_isPlaying()
{
	return numberOfTriggers < MISSED_TRIGGER_DELAY;
}