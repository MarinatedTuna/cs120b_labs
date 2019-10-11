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
    
    state = Start;

    /* Insert your solution below */
    while (1) {
        Tick();
    }
    return 1;
}

void Tick() {
    switch(state) {
        default:
	    break;
    }
}
