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

enum States {Start, PRESSPA0, PRESSPA1, RELEASEBOTH} state;

void Tick();

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF; //input    
    DDRC = 0xFF; PORTC = 0x00; //output

    state = Start;

    /* Insert your solution below */
    while (1) {
        PORTC = 7;
        Tick();
    }
    return 1;
}

void Tick() {
    switch(state) {
        case Start:
            //state = OFF;
            if(PA0 && PORTC <= 9) {
	        state = PRESSPA0;
	    }
            break;
        case PRESSPA0:
            //state = PB0 ? ON : OFF;

	    break;
	case PRESSPA1:
	    //state = PB0 ? OFF : ON; // check again
	    break;
	case RELEASEBOTH:
	    break;
        default:
	    break;
    } // Transitions

    switch(state) {
	case Start:
	    break;
	case PRESSPA0:
	    PORTC = PORTC + 1; //check again later
	    break;
	case PRESSPA1:
	    PORTC = PORTC - 1; 
	    break;
	case RELEASEBOTH:
	    PORTC = 0;
	    break;
	default:
	    break;
    } // State actions
}
