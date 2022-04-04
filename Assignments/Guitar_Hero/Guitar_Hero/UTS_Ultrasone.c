/*
 * UTS_Ultrasone.c
 *
 * Created: 29-3-2022 09:19:27
 *  Author: Jesse
 */ 
#include "UTS_Ultrasone.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <xc.h>

// Defines
#define TRIGGER_PIN 0
#define ECHO_PIN 7

#define TICK_CM 58.0

int currentDistance = 0;
char ticksOnTrigger = 0;

/************************************************************************/
/* Starts the timer for counting distances                              */
/************************************************************************/
static void initTimer();

/************************************************************************/
/* Interrupt triggered on rising and falling edge,                      */
/* Calculates the distance from the sensor                              */
/************************************************************************/
ISR ( INT7_vect )
{    
    // Setting the time from the timer on PE7 going high
    if( PINE & (1 << ECHO_PIN) )
        ticksOnTrigger = TCNT2;
    
    else
    {
        unsigned char diff = TCNT2 - ticksOnTrigger;        // Getting the difference from timer and start
        
        currentDistance = ( diff * ( 32.0 / TICK_CM ) );    // Calculating cm
        
        
        ticksOnTrigger = 0;                                 // resetting ticksOnTrigger
    }
    
}

/************************************************************************/
/* Overflow interrupt for timer 2                                       */
/************************************************************************/
ISR ( TIMER2_OVF_vect )
{
    TCNT2 = 0; // Resetting timer
}

/************************************************************************/
/* Inits the ultrasone sensor                                           */
/************************************************************************/
void UTS_Init( void )
{
    DDRE |= (1 << TRIGGER_PIN);      // PORTE 0 to output
    DDRE &= ~(1 << ECHO_PIN);        // PORTE 7 to input
    
    // Init Interrupt hardware
    EICRB |= 0x40;					// ISC7 Rising edge and falling edge
    EIMSK |= 0x80;					// Enable INT7
    
    initTimer();
}

/************************************************************************/
/* Triggers the ultrasone sensor for update                             */
/************************************************************************/
void UTS_Trigger( void )
{
    PORTE |= (1 << TRIGGER_PIN);	// Trigger pin high
    
    _delay_us(10);                  // 10 micro-seconds delay
    
    PORTE &= ~(1 << TRIGGER_PIN);   // Trigger pin low
}

/************************************************************************/
/* Sets all the registers for the ultrasone                             */
/************************************************************************/
static void initTimer()
{
    TCNT2 = 0;              // Set start value for timer to zero
    TIMSK |= 0b01000000;	// Enable the overflow interrupt for timer 2 
    TCCR2 = 0b00001100;     // Enable wave form generation with 256 pre-scaler
    sei();                  // Enable interrupts
}