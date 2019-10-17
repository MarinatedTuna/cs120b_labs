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
	else if(PINA == 0x01 || PINA == 0x02) {
	    PORTC = 0x10; // Level 1 or 2
	}
	else if(PINA == 0x03 || PINA == 0x04) {
	    PORTC = 0x18; // Level 3 or 4
	}	
    }
    return 1;
}
