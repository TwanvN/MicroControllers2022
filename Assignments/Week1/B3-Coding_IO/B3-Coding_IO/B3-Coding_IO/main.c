/*
 * main.c
 *
 * Created: 2/2/2022 11:45:17 AM
 *  Author: Twanv
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

void wait(int ms) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int main(void)
{
	DDRD = 0b10000000;
	DDRC = 0b00000000;
	
    while(1)
    {
        if (PINC == 0b00000001)
        {
			PORTD = 0b10000000;
			wait(500);
			PORTD = 0b00000000;
			wait(500);
        }
    }
}