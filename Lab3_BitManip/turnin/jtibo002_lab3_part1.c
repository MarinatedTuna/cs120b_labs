/*	Author: jtibo002
 *  Partner(s) Name: Jenaro Vega
 *	Lab Section:
 *	Assignment: Lab #3  Exercise #1
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
    /* Insert DDR and PORT initializations */

    //inputs
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0x00; PORTB = 0xFF;

    //outputs
    DDRC = 0xFF; PORTC = 0x00;

    //temp variables
//    unsigned char count = 0;

    /* Insert your solution below */
    while (1) {
	if(PA0 == 0 && PA1 == 0 && PA2 == 0 && PA3 == 0 && PA4 == 0 && PA5 == 0 && PA6 == 0 && PA7 == 0) {
	    PORTC = PINA;
	}
        if(PA0 == 1) {
            PINA = PINA + 1;
	    PORTC = PINA;
	}
	if(PA1 == 1) {
	    PINA = PINA + 1;
	    PORTC = PINA;
	}
	if(PA2 == 1) {
	    PINA = PINA + 1;
	    PORTC = PINA;
	}
	if(PA3 == 1) {
	    PINA = PINA + 1;
	    PORTC = PINA;
	}
	if(PA4 == 1) {
	    PINA = PINA + 1;
	    PORTC = PINA;
	}
	if(PA5 == 1) {	
	    PINA = PINA + 1;
	    PORTC = PINA;
	}
	if(PA6 == 1) {
	    PINA = PINA + 1;
	    PORTC = PINA;
	}
	if(PA7 == 1) {
	    PINA = PINA + 1;
	    PORTC = PINA;
	}

	//Now add PINB 1's
	
	if(PB0 == 1) {
	    PINB = PINB + 1;
	    PORTC = PINA + PINB;
	}
	if(PB1 == 1) {
	    PINB = PINB + 1;
	    PORTC = PINA + PINB;
	}
	if(PB2 == 1) {
	    PINB = PINB + 1;
	    PORTC = PINA + PINB;
	}
	if(PB3 == 1) {
	    PINB = PINB + 1;
	    PORTC = PINA + PINB;
	}
	if(PB4 == 1) {
	    PINB = PINB + 1;
	    PORTC = PINA + PINB;
	}
	if(PB5 == 1) {
	    PINB = PINB + 1;
	    PORTC = PINA + PINB;
	}
	if(PB6 == 1) {
	    PINB = PINB + 1;
	    PORTC = PINA + PINB;
	}
	if(PB7 == 1) {
	    PINB = PINB + 1;
	    PORTC = PINA + PINB;
	}			
    }
    return 1;
}
