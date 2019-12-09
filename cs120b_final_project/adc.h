#ifndef adc_h
#define adc_h

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>

void ADC_init(){
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

//This is the website I used to help me modify the ReadADC function
//https://www.electronicwings.com/avr-atmega/nokia5110-graphical-display-interfacing-with-atmega16-32

unsigned short ReadADC(unsigned char ch){
	ch = ch & 0x07;
	ADMUX |= ch;
	
	ADCSRA |= (1<<ADSC);
	
	while(!(ADCSRA & (1<<ADIF)));
	
	ADCSRA |= (1<<ADIF); //adc(1)
	
	return(ADC);
}

#endif
