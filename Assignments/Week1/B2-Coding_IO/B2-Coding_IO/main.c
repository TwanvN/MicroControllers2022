/*
 * main.c
 *
 * Created: 2/2/2022 11:28:58 AM
 *  Author: Jesse
 */ 

#define F_CPU 8e6


#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

void wait( int ms )
{
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}


int main(void)
{
	DDRD = 0b01100000;
	
    while(1)
    {
        PORTD = 0b10000000;
		wait(500);
		PORTD = 0b01000000;
		wait(500);
    }
	
	return 1;
}