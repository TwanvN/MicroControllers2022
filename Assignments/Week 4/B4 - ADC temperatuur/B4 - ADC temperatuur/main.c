/*
 * main.c
 *
 * Created: 2/23/2022 11:59:14 AM
 *  Author: Twanv
 */ 
#define F_CPU 8e6

#include <xc.h>
#include <stdio.h>
#include <util/delay.h>
#include "LCD.h"

void adcInit() {
	ADMUX = 0b11100001;
	ADCSRA = 0b11000110;
}

int main(void)
{
	DDRA = 0xFF;
	DDRF = 0x00;
	adcInit();
	
	_delay_ms(1500);
	LCD_init();
	
    while(1)
    {
		LCD_set_cursor(0);
		
		ADCSRA |= (1<<6);
		while ( ADCSRA & (1<<6)) ;
		
		char text[16];
		
		PORTA = ADCH;
		
		sprintf(text, "Temperatuur: %d", ADCH);
		
		LCD_display_text(text);
		_delay_ms(500);
    }
}