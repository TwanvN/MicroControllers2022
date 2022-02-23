/*
 * main.c
 *
 * Created: 2/23/2022 11:49:18 AM
 *  Author: Twanv
 */ 

#include <xc.h>

int main(void)
{
    ADMUX = 0b01100001;		//AREF = VCC, result left adjusted, pin F1
	ADCSRA = 0b11100110;	//ADC-enable, no interrupt, start, free running, devision 64
}