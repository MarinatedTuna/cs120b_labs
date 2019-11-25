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
 
void ADC_init(){
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}
 
unsigned short ReadADC(unsigned char ch){
	ch = ch & 0x07;
	ADMUX |= ch;
	
	ADCSRA |= (1<<ADSC);
 
        while(!(ADCSRA & (1<<ADIF)));
	
	ADCSRA |= (1<<ADIF);
	
	return(ADC);
}
 
int main(void) {
	DDRD = 0xFF; PORTD = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
	
	unsigned short x;
	unsigned short y;
	unsigned char led = 0x00;
	
	ADC_init();
	
	while (1) {

		led = 0x00; //init
		
		x = ReadADC(0);
		if(x < 300){
			led |= 0x08; //left
		}
		if(x > 900){
			led |= 0x04; //right
		}
		
		y = ReadADC(1);
		if(y < 300){
			led |= 0x01; //down
		}
		if(y > 900){
			led |= 0x02; //up
		}
		
		PORTC = led;
	}
	return 1;
}


