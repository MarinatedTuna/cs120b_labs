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

enum States {Start, OFF, ON} state;

void Tick();

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF; //input    
    DDRB = 0xFF; PORTB = 0x00; //output

    state = Start;

    /* Insert your solution below */
    while (1) {
        Tick();
    }
    return 1;
}

void Tick() {
    switch(state) {
        case Start:
            state = OFF;
            break;
        case OFF:
            state = PB0 ? ON : OFF;
	    break;
	case ON:
	    state = PB0 ? OFF : ON; // check again
	    break;
        default:
	    break;
    } // Transitions

    switch(state) {
	case Start:
	    break;
	case OFF:
	    PORTB = 0x00; //check again later
	    break;
	case ON:
	    PORTB = 0x01; 
	    break;
	default:
	    break;
    } // State actions
}
