/*	Author: jvega008
 *	 *  Partner(s) Name: Joseph Tibog, Jenaro Vega
 *	  *	Lab Section:
 *	   *	Assignment: Lab #  Exercise #
 *	    *	Exercise Description: [optional - include for your own benefit]
 *	     *
 *	      *	I acknowledge all content contained herein, excluding template or example
 *	       *	code, is my own original work.
 *	        */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;

	while (1) {
		if(PINA == 0xFF){ //was 0xFF
			PORTC = 0x40;
		}
		if(PINA == 0xFE || PINA == 0xFE){ //was 0xFE
			PORTC = 0x60;
		}
		if(PINA == 0xFB || PINA == 0xFB){ //was 0xFB
			PORTC = 0x70;
		}
		if(PINA == 0xFA || PINA == 0xF9){
			PORTC = 0x38;
		}
		if(PINA == 0xF8 || PINA == 0xF7 || PINA == 0xF6){
			PORTC = 0x3C;
		}
		if(PINA == 0xF5 || PINA == 0xF4 || PINA == 0xF3){
			PORTC = 0x3E;
		}
		if(PINA == 0xF2 || PINA == 0XF1 || PINA == 0xF0){ //was 0xF2 || 0xF1 || 0xF0
			PORTC = 0x3F;
		}

	}
    return 1;
}
