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
unsigned char threeLEDs_ = 0x00;
unsigned char threeLEDs = 0x00;
enum State1{one,two,three} state1;
void ThreeLEDsSM(){
     switch(state1){
	case one:
	     threeLEDs = 0x01 | threeLEDs_;
	     state1 = two;
             break;
	case two:
	     threeLEDs = 0x02 | threeLEDs_;
	     state1 = three;
	     break;
	case three:
             threeLEDs = 0x04 | threeLEDs_;
	     state1 = one;
	      break;
	default:
	     threeLEDs = 0x00;
	     state1 = one;
	     break;
     }
}
enum State2{on,off} state2;
void BlinkingLEDSM(){
     switch(state2){
	case on:
	     threeLEDs_ = 0x08;
	     state2 = off;
	     break;
	case off:
	     threeLEDs_ =  0x00;
	     state2 = on;
	     break;
	default:
	     state2 = on;
	     break;
      }
}
unsigned char x = 0x00;
enum State3{up, down}state3;
void Speaker(){
     switch(state3){
	case up:
             x = 0x10;
	      state3 = down;
	      break;
	case down:
              x = 0x00;
	      state3 = up;
	      break;
	default:
              state3 = up;
	      break;
      }	
}

int main(void) {
DDRB = 0xFF;
PORTB = 0x00;
DDRA = 0x00;
PORTA = 0xFF;
TimerSet(4);
TimerOn();
unsigned char i = 0;
unsigned char j = 0;
unsigned char k = 0;
	

while (1) {
     if(i >= 250){
	 BlinkingLEDSM();
         i = 0;
     }
     if(j >= 75){
         ThreeLEDsSM();
	 j = 0;
     }
     if(PINA == 0xFE){
         if(k >= 0){
	     Speaker();
	     k = 0;
         }   
     }
		
     i++;
     j++;
     k++;
     if(x == 0x10){
	PORTB = threeLEDs | x;
     }
     else{
	PORTB = threeLEDs & 0xEF;
     }
     while(!TimerFlag);
	TimerFlag = 0;
     }
return 1;
}
