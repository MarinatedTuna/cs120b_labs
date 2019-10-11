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

enum States {Start, PRESSPA0, PRESSPA1, RELEASEBOTH} state;

void Tick();

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF; //input    
    DDRC = 0xFF; PORTC = 0x00; //output

    /* Insert your solution below */
    while (1) {
	state = Start;
        PORTC = 7;
        Tick();
    }
    return 1;
}

void Tick() {
    switch(state) {
        case Start:
            //state = OFF;
            if(PINA == 0x01 && PORTC <= 9) {
		//PINA = PA0
	        state = PRESSPA0;
	    }
	    else if(PINA == 0x02 && PORTC >= 0) {
	        //PINA = PA1
	        state = PRESSPA1;
	    }
	    else {
		state = Start;
	    }
            break;
        case PRESSPA0:
            //state = PB0 ? ON : OFF;
	    if(PA1 && PORTC >= 0) {
	        state = PRESSPA1;
	    }
	    else if(PA0 && PA1){
	        state = RELEASEBOTH;
	    }
	    else {
	        state = PRESSPA0;
	    }
	    break;
	case PRESSPA1:
	    if(PA0 && PORTC <= 9) {
	        state = PRESSPA0;
	    }
	    else if(PA0 && PA1) {
	        state = RELEASEBOTH;
	    }
	    else {
		state = PRESSPA1;
	    }
	    break;
	case RELEASEBOTH:
	    if (PA0) {
	        state = PRESSPA0;
	    }
	    else {
	        state = RELEASEBOTH;
	    }
	    break;
        default:
	    break;
    } // Transitions

    switch(state) {
	case Start:
	    PORTC = 7;
	    break;
	case PRESSPA0:
	    PORTC = PORTC + 1; 
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
