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

    //outputs
    DDRC = 0xFF; PORTC = 0x00;

    unsigned char store = 0;

    /* Insert your solution below */
    while (1) {
	if(PINA == 1 || PINA == 2){
	    //PA0 or PA1 is 1
	    //PC5 = 1;
	    PINC = PC5;
	    PORTC = PINC;
	}
	if(PINA == 3 || PINA == 4) {
	    store = PC5 + PC4;
	    PINC = store;
	    PORTC = PINC;
	}
	if(PINA == 5 || PINA == 6) {
	    store = PC5 + PC4 + PC3;
	    PINC = store;
	    PORTC = PINC;	
	}
    }
    return 1;
}
