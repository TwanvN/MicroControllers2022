/*
 * main.c
 *
 * Created: 2/2/2022 10:33:08 AM
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
	DDRD = 0xFF;
	
    while(1)
    {
        PORTD = 0xAA;
		wait( 250 );
		PORTD = 0x55;
		wait( 250 );
    }
	
	return 1;
}