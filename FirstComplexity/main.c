#include <avr/io.h>
#include <util/delay.h>
#include "ADC_H.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


int main(void) {

	void ADC_init(){
		ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	}
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned short my_short = ADC;

	int x_direction = PINA0; //PA0
	int y_direction = PINA1; //PA1
	int switch = 0;
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
