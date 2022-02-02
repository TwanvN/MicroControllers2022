/*
 * main.c
 *
 * Created: 2/2/2022 12:19:13 PM
 *  Author: Twanv
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int main(void)
{
	DDRD = 0b11111111;
	PORTD = 0b00000001;
	
    while(1)
    {
		if (PORTD == 0b10000000)
		{
			PORTD = 0b00000001;
		} else {
			PORTD = PORTD << 1;
		}
		
        wait(50);
    }
}