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
	    if(PINA == 0x04) {
	        state = PRESS;
	    }
	    else {
	        state = Start;
	    }
	    break;	
	case PRESS:
	    if(PINA == 0xFB) {
	        state = RELEASE;
	    }
	    else {
	        state = Start;
	    }
	    break;
	case RELEASE:	
	    if(PINA == 0x02) {
	        state = PRESS2;
	    }
	    else {
		state = Start;
	    }
	    break;
	case PRESS2:
	    if(PINA == 0x80) {
	        state = Start;
	    }
	    else {
		state = PRESS2;
	    }
	    break;        
        default:
	    break;
    } // Transitions

    switch(state) {
	case Start:
	    PORTC = 0;
	    break;
	case PRESS:
	    PORTC = 0;
	    break;
	case RELEASE:
	    PORTC = 0;
	    break;
	case PRESS2:
	    PORTC = 1;
	    break;
	default:
	    break;
    } // State actions
}
