/*	Author: jvega008
 *  Partner(s) Name: Joseph Tibog, Jenaro Vega
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


int main(void) {

    void ADC_init(){
        ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
    }
    //DDRD = 0xFF; PORTD = 0x00;
    DDRB = 0xFF; PORTB = 0x00;

    unsigned short my_short = ADC;
    //unsigned char my_char = (char)my_short;
    //unsigned char tmp = 0x00;
    //unsigned char MAX = 46.5;
   
    while (1) {
        if(my_short <= 11.625){
	    PORTB = 0x01;
	}
	else if(my_short <= 23.25){
	    PORTB = 0x03;
	}
        else if(my_short <= 34.875){
	    PORTB = 0x07;
	}
	else if(my_short <= 46.5){
	    PORTB = 0x0F;
	}
	else if(my_short <= 58.125){
	    PORTB = 0x1F;
	}
	else if(my_short <= 69.75){
	    PORTB = 0x3F;
	}
	else if(my_short <= 81.375){
	    PORTB = 0x7F;
	}
	else{
	    PORTB = 0xFF;
	}
    }
    return 1;
}

