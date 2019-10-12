/*	Author: jvega008
 *  Partner(s) Name: Joseph Tibog, Jenaro Vega
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


enum States {init, press_sub, press_add, rel_sub, rel_add, wait, reset_p, reset_r} state;

int sm_tick(int state){
    unsigned char A0_add = PINA & 0x01;
    unsigned char A1_sub = PINA & 0x02;
    if(state == init){
	PORTC = 7;
    }   
    switch(state){
        case init:
	    if(A1_sub && A0_add){
		state = reset_p;
		break;
	    }
	    else if(A0_add){
	        state = press_add;
		break;
	    }
	    else if(A1_sub){
		state = press_sub;
		break;
	    }
	    else{
		state = init;
		break;
	    }
	case press_sub:
	     if(!A1_sub && !A0_add){
		state = rel_sub;
		break;
	    }
	    else if(A1_sub && A0_add){
		state = reset_p;
		break;
	    }
	    else{
                state = press_sub;
                break;
            }
	case press_add:
             if(!A1_sub && !A0_add){
                state = rel_add;
                break;
            }
            else if(A1_sub && A0_add){
                state = reset_p;
                break;
            }
            else{
                state = press_add;
                break;
            }
	case rel_sub:
	    state = wait;
	    break;
	case rel_add:
	    state = wait;
	    break;
	case wait:
	    if(A0_add && A1_sub){
		state = reset_p;
		break;
	    }
	    else if(A1_sub && (PORTC > 0)){
		state = press_sub;
		break;
	    }
	    else if(A0_add && (PORTC < 9)){
		state = press_add;
		break;
	    }
	    else{
		state = wait;
		break;
	    }
	case reset_p:
	    if(A0_add && A1_sub){
		state = reset_p;
		break;
	    }
	    else{
		state = reset_r;
		break;
	    }
	case reset_r:
	    if(A0_add && !A1_sub){
		state = press_add;
		break;
	    }
	    else if(A1_sub && !A0_add){
		state = press_sub;
		break;
	    }
	    else if(A1_sub && A0_add){
		state = reset_p;
		break;
	    }
	    else{
		state = reset_r;
		break;
	    }
	default:
	    state = init;
	    break;

    }
    switch(state){
	case init:
	    PORTC = 7; 
	    break;
	case press_add:
	    break;
	case press_sub:
	    break;
	case rel_add:
	    PORTC = PORTC + 1;
	    state = wait;
	    break;
	case rel_sub:
	    PORTC = PORTC - 1;
	    state = wait;
	    break;
	case wait: 
	    break;
	case reset_p:
	    break;
	case reset_r:
	    PORTC = 0;
	    break;
    }

return state;

}

int main(void) {
    
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
   
    int state = init;
    while (1) {
	state = sm_tick(state);
	
    }
    return 1;
}
