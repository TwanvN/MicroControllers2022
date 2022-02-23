/*
 * main.c
 *
 * Created: 2/23/2022 11:59:14 AM
 *  Author: Twanv
 */ 
#define F_CPU 8e6

#include <xc.h>
#include <util/delay.h>

void adcInit() {
	ADMUX = 0b01100001;
	ADCSRA = 0b11100110;
}

int main(void)
{
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRF = 0x00;
	adcInit();
	
    while(1)
    {
        PORTB = ADCL;
		PORTA = ADCH;
		_delay_ms(100);
    }
}