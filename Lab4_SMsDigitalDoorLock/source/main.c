/*	Author: jtibo002
 *  Partner(s) Name: Jenaro Vega
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, PRESS, RELEASE, PRESS2} state;

void Tick();

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF; //input    
    DDRC = 0xFF; PORTC = 0x00; //output

    /* Insert your solution below */
    while (1) {
	PORTC = 0;
        Tick();
    }
    return 1;
}

void Tick() {
    switch(state) {
	case Start:
	    if(PA2) {
	        state = PRESS;
	    }
	    else {
	        state = Start;
	    }	        
        default:
	    break;
    } // Transitions

    switch(state) {
	default:
	    break;
    } // State actions
}
