/*
 * main.c
 *
 * Created: 2/23/2022 11:25:36 AM
 *  Author: Jesse
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}

void adcInit( void )
{
	ADMUX = 0b01100001;
	
	ADCSRA = 0b11100110;
}

int main(void)
{
	DDRF = 0x00;
	DDRA = 0xFF;
	DDRB = 0xFF;
	adcInit();
	
    while(1)
    {
        PORTB = ADCL;
		PORTA = ADCH;
		wait(100);
    }
}