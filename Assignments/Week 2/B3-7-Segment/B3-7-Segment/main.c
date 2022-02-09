/*
 * main.c
 *
 * Created: 2/9/2022 11:22:18 AM
 *  Author: Twanv
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <xc.h>
#include <util/delay.h>

char letterCodes[] = {
	0x77,
	0x44,
	0x6B,
	0x6E,
	0x5C,
	0x3E,
	0x3F,
	0x64,
	0x7F,
	0x7E,
	0x7D,
	0x1F,
	0x33,
	0x4F,
	0x3B,
	0x39
};

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
};

void display(int digit){
	if (digit < 0 || digit > 15)
	{
		PORTA = letterCodes[14];
	} else {
		PORTA = letterCodes[digit];
	}
};

void loopDigits() {
	for (int i = 0; i < (sizeof(letterCodes) / sizeof(letterCodes[0])); i++)
	{
		display(i);
		wait(1000);
	}
};

int main(void)
{
	DDRA = 0xFF;
	
	int digit = 0;
	
	display(digit);
	
    while(1)
    {
        if (PINC == 0b00000001)
        {
			digit++;
			display(digit);
        } else if (PINC == 0b00000010)
        {
			digit--;
			display(digit);
        } else if (PINC == 0b00000011) {
			digit = 0;
			display(digit);
		}
		
		wait(250);
    }
}