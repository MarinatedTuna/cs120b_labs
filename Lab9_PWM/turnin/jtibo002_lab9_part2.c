/*	Author: jvega008
 *  Partner(s) Name: Joseph Tibog, Jenaro Vega
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
   
void set_PWM(double frequency){
    static double current_frequency;
        if(frequency != current_frequency){
	if(!frequency){ TCCR3B &= 0x08; }
	else { TCCR3B |= 0x03; }
	if(frequency < 0.954) { OCR3A = 0xFFFF; }
	else if(frequency > 31250) { OCR3A = 0x0000; }
	else { OCR3A = (short)(8000000 / (128 * frequency)) - 1; }
	TCNT3 = 0;
	current_frequency = frequency;
    }
}
void PWM_on(){
    TCCR3A = (1 << COM3A0);
    TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
    set_PWM(0);
}
void PWM_off(){
    TCCR3A = 0x00;
    TCCR3B = 0x00;
}

unsigned long arr[] = {261.63,293.66,329.63,349.23,392.00,440.00,493.88,523.25};
unsigned char i = 0;
enum States{off, on, down, up, wait} state;
    void tick(){
	switch(state){
	     case off: 
		if(~PINA == 0x01){
		    while(~PINA == 0x01){}
		    state = on;
		    break;
	        }
		else{
		    state = off;
		    break;
		}
	    case on:
		state = wait;
		break;
	    case up:
		state = wait;
		break;
	    case down:
		state = wait;
		break;
	    case wait:
		if(~PINA == 0x01){
		    while(~PINA == 0x01){}
		    state = off;
		    break;
		}
		else if(~PINA == 0x02){
		    while(~PINA == 0x02){}
		    state = up;
		    break;
		}
		else if(~PINA == 0x04){
		    while(~PINA == 0x04){}
		    state = down;
		    break;
		}
		else{
		    state = wait;
		    break;
		}
	    default:
		state = off;
		break;
        }
	switch(state){
	    case off:
		PWM_off();
		break;
	    case on:
	    	PWM_on();
		i = 0;
		set_PWM(arr[i]);
		state = wait;
		break;
	    case up:
		if(i == 7){
		    state = wait;
		    break;
		}
		else{
		    i++;
		    set_PWM(arr[i]);
		    state = wait;
		    break;
		}
	    case down:
		if(i == 0){
		    state = wait;
		    break;
		}
		else{
		    i--;
		    set_PWM(arr[i]);
		    state = wait;
		    break;
		}
	    case wait:
		break;
	}
    } 

int main() {
		
    DDRB = 0x40; PORTB = 0x00;
    DDRA = 0x00; PORTA = 0xFF;

    while (1) {
        tick();
    }
    return 1;
}
