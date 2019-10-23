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
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;


void TimerOn(){
	TCCR1B = 0x0B;


	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;

	SREG = 0x80;
}

void TimerOff(){
	TCCR1B = 0x00;
}

void TimerISR(){
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect){
	_avr_timer_cntcurr--;
	if(_avr_timer_cntcurr == 0){
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M){
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

enum States {led1, led2, led3, led2_, wait} state;

int sm_tick(int state){
	switch(state){
		case led1:
		if(PINA == 0xFF && TimerFlag == 1){
			state = led2;
			TimerFlag = 0;
			break;
		}
		else if(PINA == 0xFE){
			while(PINA == 0xFE){}
			state = wait;
			break;
		}
		else{
			state = led1;
			break;
		}
		case led2:
		if(PINA == 0xFF && TimerFlag == 1){
			state = led3;
			TimerFlag = 0;
			break;
		}
		else if(PINA == 0xFE){
			while(PINA == 0xFE){}
			state = wait;
			break;
		}
		else{
			state = led2;
			break;
		}
		case led3:
		if(PINA == 0xFF && TimerFlag == 1){
			state = led2_;
			TimerFlag = 0;
			break;
		}
		else if(PINA == 0xFE){
			while(PINA == 0xFE){}
			state = wait;
			break;
		}
		else{
			state = led3;
			break;
		}
		case led2_:
		if(PINA == 0xFF && TimerFlag == 1){
			state = led1;
			TimerFlag = 0;
			break;
		}
		else if(PINA == 0xFE){
			while(PINA == 0xFE){}
			state = wait;
			break;
		}
		else{
			state = led2_;
			break;
		}
		case wait:
		if (PINA == 0xFE){
			while(PINA == 0xFE){}
			state = led1;
			TimerFlag = 0;
			break;
		}
		else{
			state = wait;
			break;
		}
		default:
		state = led1;
		TimerFlag = 0;
		break;
	}
	switch(state){
		case led1:
		PORTC = 0x01;
		break;
		case led2:
		PORTC = 0x02;
		break;
		case led3:
		PORTC = 0x04;
		break;
		case led2_:
		PORTC = 0x02;
		break;
		case wait:
		break;

	}
	return state;
}


int main(void) {
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRC = 0xFF;
	PORTC = 0x00;
	TimerSet(50);
	TimerOn();
	
	int state = led1;

	while (1) {
		state = sm_tick(state);
	}
	return 1;
}
