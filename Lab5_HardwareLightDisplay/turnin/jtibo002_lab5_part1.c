/*	Author: jtibo002
 *  Partner(s) Name: Jenaro Vega
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

    DDRA = 0x00; PORTA = 0xFF; //inputs 
    DDRC = 0xFF; PORTC = 0x00; //outputs
    
    while (1) {
        if(PINA == (!PA3 && !PA2 && !PA1 && !PA0)) {
            PORTC = 0x00; // Level 0
	}
	else if(PINA == 1 || PINA == 2) {
	    PORTC = 0x20; // Level 1 or 2
	}
	else if(PINA == 3 || PINA == 4) {
	    PORTC = 0x30; // Level 3 or 4
	}
	else if(PINA == 5 || PINA == 6) {
	    PORTC = 0x38;
	}
	else if(PINA == 7 || PINA == 8 || PINA == 9) {
	    PORTC = 0x3C;
	}
	else if(PINA == 10 || PINA == 11 || PINA == 12) {
	    PORTC = 0x3E;
	}
	else if(PINA == 13 || PINA == 14 || PINA == 15) {
	    PORTC = 0x3F;
	}	
    }
    return 1;
}
