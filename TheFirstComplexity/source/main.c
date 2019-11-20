#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "ADC_H.h"
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
	ADMUX = (1<<REFS0);
		
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

uint16_t adc_read(uint8_t ch){
	ch = ch & 0x07;
	
	ADMUX = (ADMUX & 0xF8) | ch;
	
	while(ADCSRA & (1 << ADSC));
	return (ADC);
}

int main(void) {
	
	ADC_init();
	
	DDRA = 0xFF; PORTA = 0x00; //input
	DDRC = 0xFF; PORTC = 0x00; //output
	
	unsigned short my_short = ADC;

	int x_direction = ReadADC(PA0); //PA0
	int y_direction = ReadADC(PA1); //PA1
	int left = 400;
	int right = 600;
	int up = 600;
	int down = 400;
	
	
	while (1) {
			if(my_short <= left || x_direction <= left){
				PORTC = 0x01;
			}
			else if(my_short >= right || x_direction >= right){
				PORTC = 0x02;
			}
			else if(my_short >= up || y_direction >= up){
				PORTC = 0x04;
			}
			else if(my_short <= down || y_direction <= down){
				PORTC = 0x08;
			}
	}
	return 1;
}
