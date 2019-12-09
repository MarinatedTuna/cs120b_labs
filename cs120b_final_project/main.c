#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

#define F_CPU 12000000UL

//-------------------TIMER-------------------

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

//-------------------LCD-------------------

void LCD_init();
void LCD_ClearScreen(void);
void LCD_WriteCommand (unsigned char Command);
void LCD_Cursor (unsigned char column);
void LCD_DisplayString(unsigned char column , unsigned char *string);
void LCD_Custom_Char1 (unsigned char loc, unsigned char *msg);
void LCD_Custom_Char2 (unsigned char loc, unsigned char *msg);
void delay_ms(int miliSec);

#define SET_BIT(p,i) ((p) |= (1 << (i)))
#define CLR_BIT(p,i) ((p) &= ~(1 << (i)))
#define GET_BIT(p,i) ((p) & (1 << (i)))

/*-------------------------------------------------------------------------*/
#define DATA_BUS PORTC		// port connected to pins 7-14 of LCD display
#define CONTROL_BUS PORTD	// port connected to pins 4 and 6 of LCD disp.
#define RS 6			// pin number of uC connected to pin 4 of LCD disp.
#define E 7			// pin number of uC connected to pin 6 of LCD disp.
/*-------------------------------------------------------------------------*/

void LCD_ClearScreen(void) {
	LCD_WriteCommand(0x01);
}

void LCD_init(void) {

	//wait for 100 ms.
	LCD_WriteCommand(0x38);
	LCD_WriteCommand(0x06);
	LCD_WriteCommand(0x0f);
	LCD_WriteCommand(0x01);
	delay_ms(10);
}

void LCD_WriteCommand (unsigned char Command) {
	CLR_BIT(CONTROL_BUS,RS);
	DATA_BUS = Command;
	SET_BIT(CONTROL_BUS,E);
	asm("nop");
	CLR_BIT(CONTROL_BUS,E);
	delay_ms(2); // ClearScreen requires 1.52ms to execute
}

void LCD_WriteData(unsigned char Data) {
	SET_BIT(CONTROL_BUS,RS);
	DATA_BUS = Data;
	SET_BIT(CONTROL_BUS,E);
	asm("nop");
	CLR_BIT(CONTROL_BUS,E);
	delay_ms(1);
}

void LCD_DisplayString( unsigned char column, unsigned char* string) {
	LCD_ClearScreen();
	unsigned char c = column;
	while(*string) {
		LCD_Cursor(c++);
		LCD_WriteData(*string++);
	}
}

void LCD_Cursor(unsigned char column) {
	if(column < 17) { //16x1 LCD: column < 9
		LCD_WriteCommand(0x80 + column - 1); //16x2 LCD: column < 17
	}
	else {
		LCD_WriteCommand(0xB8 + column - 9); // 16x1 LCD: column - 1
	}
}

//LINK WEBSITE

//writes custom characters into memory
void LCD_Custom_Char1 (unsigned char loc, unsigned char *msg)
{
	unsigned char j;
	if(loc<8)
	{
		LCD_WriteCommand(0x40 + (loc*8));  /* Command 0x40 and onwards forces the device to point CGRAM address */
		for(j=0;j<7;j++)	/* Write 7 byte for generation of 1 character */
		LCD_WriteData(msg[j]);
	}
}

//outputs custom characters onto screen
void LCD_Custom_Char2 (unsigned char loc, unsigned char *msg)
{
	unsigned char j;
	if(loc<8)
	{
		LCD_WriteCommand(0x80 + (loc*8));  /* Command 0x80 prints characters saved in CGRAM address */
		for(j=0;j<7;j++)	/* Write 7 byte for generation of 1 character */
		LCD_WriteData(msg[j]);
	}
}

void delay_ms(int miliSec) { //for 8 Mhz crystal
	int i,j;
	for(i=0;i<miliSec;i++)
	for(j=0;j<775;j++)
	{
		asm("nop");
	}
}

unsigned short x; //was initially considered. no longer needed
unsigned short y; //to navigate through story
unsigned char led = 0x00; //for joystick
unsigned char score = 3; //for lcd score based on choices

//-------------------LCD-------------------
	
void ADC_init(){
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

unsigned short ReadADC(unsigned char ch){
	ch = ch & 0x07;
	ADMUX |= ch;
	
	ADCSRA |= (1<<ADSC);
	
	while(!(ADCSRA & (1<<ADIF)));
	
	ADCSRA |= (1<<ADIF); //adc(1)
	
	return(ADC);
}

//-------------------STATE MACHINES FOR GAME-------------------

enum States {init, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, 
			_11, _12, _13, _14, _15, _16, _17, _18, _19, _20, 
			_21, _22, _23, _24, _25, _26, _27, _28, _29, _30,
			_31, _32, _33, _34, _35, _36, _37, _38, _39, _40,
			_41, _42, _43, _44, _45, _46, _47, _48, _49, _50,
			_51, _52, _53, _54, _55, _56, menu, quit, lose, win,
			mission_statement} state;

int check_score(int state){
	if(score < 1){
		LCD_DisplayString(1, "GAME OVER");
		_delay_ms(20000);
		LCD_DisplayString(1, "You failed to   get Jeff'd...");
		_delay_ms(15000);
		LCD_DisplayString(1, "Try again? ^");
		_delay_ms(15000);
		score = 3;
		state = _0;
	}
	return state;
}

int sm_tick(int state){
	switch(state) { //transitions
		case init:
			state = menu;
			break;
		case _0: 
			state = _1;
			break;
		case _1:
			state = _2;
			break;
		case _2:
			state = _3;
			break;
		case _3:
			if(y < 100){ 
				state = _4;
			}
			else if(y > 900){
				state = _5;
			}
			break;
		case _4:
			state = _6;
			break;
		case _5:
			state = _7;
			break;
		case _6:
			state = _8;
			break;
		case _7:
			state = _8;
			break;
		case _8:
			state = _9;
			break;
		case _9:
			state = _10;
			break;
		case _10:
			if(y < 100){
				state = _11;
			}
			else if(y > 900){
				state = _12;
			}
			break;
		case _11:
			state = _13;
			break;
		case _12:
			state = _14;
			break;
		case _13:
			state = _15;
			break;
		case _14:
			state = _15;
			break;
		case _15:
			state = _16;
			break;
		case _16:
			state = _17;
			break;
		case _17:
			state = _18;
			break;
		case _18:
			if(y < 100){
				state = _19;
			}
			else if(y > 900){
				state = _20;
			}
			break;
		case _19:
			state = _21;
			break;
		case _20:
			state = _22;
			break;
		case _21:
			state = _23;
			break;
		case _22:
			state = _23;
			break;
		case _23:
			state = _24;
			break;
		case _24:
			state = _25;
			break;
		case _25:
			state = _26;
			break;
		case _26:
			if(y < 100){
				state = _27;
			}
			else if(y > 900){
				state = _28;
			}
			break;
		case _27:
			state = _29;
			break;
		case _28:
			state = _30;
			break;
		case _29:
			state = _31;
			break;
		case _30:
			state = _31;
			break;
		case _31:
			state = _32;
			break;
		case _32:
			state = _33;
			break;
		case _33:
			state = _34;
			break;
		case _34:
			state = _35;
			break;
		case _35:
			if(y < 100){
				state = _36;
			}
			else if(y > 900){
				state = _37;
			}
			break;
		case _36:
			state = _38;
			break;
		case _37:
			state = _39;
			break;
		case _38:
			state = _40;
			break;
		case _39:
			state = _41;
			break;
		case _40:
			state = _42;
			break;
		case _41:
			state = _42;
			break;
		case _42:
			state = _43;
			break;
		case _43:
			state = _44;
			break;
		case _44:
			state = _45;
			break;
		case _45:
			if(y < 100){
				state = _46;
			}
			else if(y > 900){
				state = _47;
			}
			break;
		case _46:
			state = _48;
			break;
		case _47:
			state = _49;
			break;
		case _48:
			state = _50;
			break;
		case _49:
			state = _50;
			break;
		case _50:
			state = _51;
			break;
		case _51:
			state = _52;
			break;
		case _52:
			state = _53;
			break;
		case _53:
			if(y < 100){
				state = _54;
			}
			else if(y > 900){
				state = _55;
			}
			break;
		case _54:
			state = _56;
			break;
		case _55:
			state = _56;
			break;
		case _56:
			state = win;			
			break;
		case menu:
			if(y < 100){
				state = _0;
			}
			else if(y > 900){
				state = quit;
			}
			break;
		case win:
			state = menu;
			break;
		case lose:
			state = menu;
			break;
		case quit:
			state = menu;
			break;
		default:
			break;
	}
	
	switch(state) { //actions. tabbing/spacing for LCD purposes
		case _0:                //|             //|             //|
			LCD_DisplayString(1, "You wake up.");
			_delay_ms(12000);
			LCD_DisplayString(1, "Then head to    school. ^");	
			_delay_ms(12000);
			break;
		case _1:
			LCD_DisplayString(1, "It's the first  day of school.");
			_delay_ms(12000);
			LCD_DisplayString(1, "You meet a cute girl(guy?)");
			_delay_ms(12000);
			LCD_DisplayString(1, "It's Jeffrey    McDaniel! ^");
			_delay_ms(12000);
			break;
		case _2:
			LCD_DisplayString(1, "She/he(?) is    looking at you.");
			_delay_ms(12000);
			LCD_DisplayString(1, "What do         you say? ^");
			_delay_ms(12000);
			break;
		case _3:
			LCD_DisplayString(1, "^ Hi!           v Just stare."); //spacing corrected
			_delay_ms(12000);	
			break;
		case _4:
			LCD_DisplayString(1, "Jeff is         pleased");
			_delay_ms(12000);
			LCD_DisplayString(1, "that you said   hi to her/him. ^");		
			_delay_ms(12000);	
			break;
		case _5:
			LCD_DisplayString(1, "Jeff            thinks that");
			_delay_ms(12000);
			LCD_DisplayString(1, "you're weird    for not saying");					
			_delay_ms(12000);
			LCD_DisplayString(1, "anything        at all. ^");				
			_delay_ms(12000);
			break;
		case _6:
			LCD_DisplayString(1, "Jeff: Do you    want to");
			_delay_ms(12000);
			LCD_DisplayString(1, "talk about      state machines?^");
			_delay_ms(12000);
			break;
		case _7:
			LCD_DisplayString(1, "Jeff: Oh no.    That's not");
			_delay_ms(12000);
			LCD_DisplayString(1, "good at all.    Help me.");
			score = score - 1;
			state = check_score(state);
			_delay_ms(12000);
			LCD_DisplayString(1, "^ Score: ");
			LCD_WriteData(score + '0');
			_delay_ms(12000);
			break;
		case _8:
			LCD_DisplayString(1, "After talking   to Jeff");
			_delay_ms(12000);
			LCD_DisplayString(1, "for a while,    he asks you");
			_delay_ms(12000);
			LCD_DisplayString(1, "something deep  and personal. ^");
			_delay_ms(12000);
			break;
		case _9:
			LCD_DisplayString(1, "Jeff: Do you    have a heart?");
			_delay_ms(12000);
			LCD_DisplayString(1, "What do         you say? ^");
			_delay_ms(12000);
			break;
		case _10:
			LCD_DisplayString(1, "^ Yes?          v Nope.");
			_delay_ms(12000);	
			break;
		case _11:
			LCD_DisplayString(1, "That's too bad  because");
			_delay_ms(12000);
			LCD_DisplayString(1, "I'm a heartless person. ^");			
			_delay_ms(12000);
			break;
		case _12:
			LCD_DisplayString(1, "Jeff: Good then we'll");
			_delay_ms(12000);
			LCD_DisplayString(1, "get along       just fine ^");
			_delay_ms(12000);
			break;
		case _13:
			LCD_DisplayString(1, "Jeff seems      displeased by");	
			_delay_ms(12000);
			LCD_DisplayString(1, "your answer.");	
			score = score - 1;
			state = check_score(state);
			_delay_ms(12000);	
			LCD_DisplayString(1, "^ Score: ");
			LCD_WriteData(score + '0');
			_delay_ms(12000);
			break;
		case _14:
			LCD_DisplayString(1, "Jeff seems      pleased by");		
			_delay_ms(12000);		
			LCD_DisplayString(1, "your answer. ^");
			_delay_ms(12000);		
			break;
		case _15:
			LCD_DisplayString(1, "Jeff took a     marker then");
			_delay_ms(12000);	
			LCD_DisplayString(1, "dropped it      on the floor. ^");
			_delay_ms(12000);		
			break;
		case _16:
			LCD_DisplayString(1, "After talking   for 3 minutes, ");	
			_delay_ms(12000);	
			LCD_DisplayString(1, "you already felta connection");		
			_delay_ms(12000);	
			LCD_DisplayString(1, "with him/her ^");	
			_delay_ms(12000);				
			break;
		case _17:
			LCD_DisplayString(1, "Jeff: You wanna go out this weekend");
			_delay_ms(12000);	
			LCD_DisplayString(1, "and read about  embedded systems");
			_delay_ms(12000);				
			LCD_DisplayString(1, "at the park? ^");
			_delay_ms(12000);		
			break;
		case _18:
			LCD_DisplayString(1, "^ Yes. Raincheckv YES!! PLEASE!!");			
			_delay_ms(12000);	
			break;
		case _19:
			LCD_DisplayString(1, "Jeff: Perfect!  Let me know when");
			_delay_ms(12000);		
			LCD_DisplayString(1, "you've set your time delay");
			_delay_ms(12000);		
			LCD_DisplayString(1, "Get it? ^");
			_delay_ms(12000);
			break;
		case _20:
			LCD_DisplayString(1, "Jeff: Sounds a  bit desperate. ^");
			_delay_ms(12000);		
			break;
		case _21:
			LCD_DisplayString(1, "Jeff is pointingat you to see");
			_delay_ms(12000);
			LCD_DisplayString(1, "if you get the  joke ^");
			_delay_ms(12000);
			break;
		case _22:
			LCD_DisplayString(1, "Jeff: Maybe     sub-communicate");
			_delay_ms(12000);	
			LCD_DisplayString(1, "the abundance   mindset");
			_delay_ms(12000);		
			LCD_DisplayString(1, "next time?");
			score = score - 1;
			state = check_score(state);
			_delay_ms(12000);
			LCD_DisplayString(1, "^ Score: ");
			LCD_WriteData(score + '0');
			_delay_ms(12000);
			break;
		case _23:
			LCD_DisplayString(1, "While you are   at the park, ");
			_delay_ms(12000);	
			LCD_DisplayString(1, "Jeff tries to   impress you ");
			_delay_ms(12000);		
			LCD_DisplayString(1, "with his        knowledge");
			_delay_ms(12000);
			LCD_DisplayString(1, "of state        machines. ^");
			_delay_ms(12000);
			break;
		case _24:
			LCD_DisplayString(1, "However, in one of your");
			_delay_ms(12000);
			LCD_DisplayString(1, "conversations,  Jeff said he");
			_delay_ms(12000);			
			LCD_DisplayString(1, "likes while(1)  loops but you");
			_delay_ms(12000);
			LCD_DisplayString(1, "believe in      for(;;) loops ^");
			_delay_ms(12000);
			break;
		case _25:
			LCD_DisplayString(1, "Should you      pretend to agree");
			_delay_ms(12000);		
			LCD_DisplayString(1, "with him or     speak your mind?");
			_delay_ms(12000);	
			LCD_DisplayString(1, "What do         you say? ^");
			_delay_ms(12000);
			break;
		case _26:
			LCD_DisplayString(1, "^ Agree         v Disagree");
			_delay_ms(12000);			
			break;
		case _27:
			LCD_DisplayString(1, "Jeff: Good one. I know that ");
			_delay_ms(12000);	
			LCD_DisplayString(1, "you're lying    to me. ^");
			_delay_ms(12000);		
			break;
		case _28:
			LCD_DisplayString(1, "Jeff: I'd love  to debate with");
			_delay_ms(12000);		
			LCD_DisplayString(1, "you on that. ^");
			_delay_ms(12000);	
			break;
		case _29:
			LCD_DisplayString(1, "Jeff: Don't justagree to");
			_delay_ms(12000);		
			LCD_DisplayString(1, "everything I    say to");
			_delay_ms(12000);	
			LCD_DisplayString(1, "try and impress me.");
			score = score - 1;
			state = check_score(state);
			_delay_ms(12000);
			LCD_DisplayString(1, "^ Score: ");
			LCD_WriteData(score + '0');
			_delay_ms(12000);
			break;
		case _30:
			LCD_DisplayString(1, "Jeff: You seem  more real");
			_delay_ms(12000);			
			LCD_DisplayString(1, "since you have  something you");
			_delay_ms(12000);
			LCD_DisplayString(1, "disagree with. ^");
			_delay_ms(12000);
			break;
		case _31:
			LCD_DisplayString(1, "After talking   to Jeff");
			_delay_ms(12000);	
			LCD_DisplayString(1, "for another 2   minutes, you");
			_delay_ms(12000);	
			LCD_DisplayString(1, "feel like he is now your uh...");
			_delay_ms(12000);	
			LCD_DisplayString(1, "husbando?       Waifu? Yeah! ^");
			_delay_ms(12000);
			break;
		case _32:
			LCD_DisplayString(1, "Jeff: Life is   like a ");
			_delay_ms(12000);
			LCD_DisplayString(1, "state machine.  There are many");
			_delay_ms(12000);
			LCD_DisplayString(1, "ways to         interpret it. ^");
			_delay_ms(12000);
			break;	
		case _33:
			LCD_DisplayString(1, "That message wasso deep and");
			_delay_ms(12000);	
			LCD_DisplayString(1, "inspiring that  you started");
			_delay_ms(12000);
			LCD_DisplayString(1, "making...       animal noises. ^");
			_delay_ms(12000);
			break;		
		case _34:
			LCD_DisplayString(1, "Jeff slides an  eraser across");
			_delay_ms(12000);
			LCD_DisplayString(1, "the grass then  starts to");
			_delay_ms(12000);
			LCD_DisplayString(1, "turn red with   anime eyes.");
			_delay_ms(12000);
			LCD_DisplayString(1, "Should you      say something? ^");
			_delay_ms(12000);
			break;				
		case _35:
			LCD_DisplayString(1, "^ Tease Jeff    v Don't tease.");
			_delay_ms(12000);	
			break;		
		case _36:
			LCD_DisplayString(1, "MC: You don't   have to be so");
			_delay_ms(12000);		
			LCD_DisplayString(1, "nervous around  me you know. ^");
			_delay_ms(12000);	
			break;	
		case _37:
			LCD_DisplayString(1, "You just watch  in amazement");
			_delay_ms(12000);	
			LCD_DisplayString(1, "at him          blushing. ^");
			_delay_ms(12000);		
			break;
		case _38:
			LCD_DisplayString(1, "You smile to    let him know");
			_delay_ms(12000);	
			LCD_DisplayString(1, "you're just     teasing. ^");
			_delay_ms(12000);	
			break;
		case _39:
			LCD_DisplayString(1, "Jeff notices    this and is now");
			_delay_ms(12000);			
			LCD_DisplayString(1, "more            uncomfortable. ^");
			_delay_ms(12000);	
			break;
		case _40:
			LCD_DisplayString(1, "Jeff: I'm not   blushing! Cmon!");
			_delay_ms(12000);	
			LCD_DisplayString(1, "He says this    while laughing.");
			_delay_ms(12000);
			LCD_DisplayString(1, "You've          successfully");
			_delay_ms(12000);	
			LCD_DisplayString(1, "released        tension. ^");
			_delay_ms(12000);	
			break;
		case _41:
			LCD_DisplayString(1, "Jeff: Well now  there's more");
			_delay_ms(12000);
			LCD_DisplayString(1, "tension than    before.");
			_delay_ms(12000);		
			score = score - 1;
			state = check_score(state);
			LCD_DisplayString(1, "^ Score: ");
			LCD_WriteData(score + '0');
			_delay_ms(12000);
			break;
		case _42:
			LCD_DisplayString(1, "Jeff is still   red. He drops");
			_delay_ms(12000);
			LCD_DisplayString(1, "more markers    and slides");
			_delay_ms(12000);		
			LCD_DisplayString(1, "more erasers. ^");
			_delay_ms(12000);	
			break;
		case _43:
			LCD_DisplayString(1, "He throws a     dead marker");
			_delay_ms(12000);	
			LCD_DisplayString(1, "to the          heavens. ^");
			_delay_ms(12000);			
			break;
		case _44:
			LCD_DisplayString(1, "Reading his     body language");
			_delay_ms(12000);	
			LCD_DisplayString(1, "the signs seem  right.");
			_delay_ms(12000);
			LCD_DisplayString(1, "Should I ask to kiss or not? ^");
			_delay_ms(12000);	
			break;		
		case _45:
			LCD_DisplayString(1, "^ Ask to kiss   v Slowly lean in");
			_delay_ms(12000);	
			break;
		case _46:
			LCD_DisplayString(1, "Jeff: Can you   not read my ");
			_delay_ms(12000);
			LCD_DisplayString(1, "body language? ^");
			_delay_ms(12000);
			break;
		case _47:	
			LCD_DisplayString(1, "Jeff responds bykissing back. ^");
			_delay_ms(12000);
			break;	
		case _48:
			LCD_DisplayString(1, "Jeff: Asking    ruins the mood.");
			score = score - 1;
			state = check_score(state);
			_delay_ms(12000);
			LCD_DisplayString(1, "^ Score: ");
			LCD_WriteData(score + '0');
			_delay_ms(12000);
			break;		
		case _49:
			LCD_DisplayString(1, "Something       somewhere.");
			_delay_ms(12000);
			LCD_DisplayString(1, "Got set from    0 to 1.");
			_delay_ms(12000);
			LCD_DisplayString(1, "If you know whatI mean. ^");
			_delay_ms(12000);
			break;			
		case _50:
			LCD_DisplayString(1, "After spending  the whole day");
			_delay_ms(12000);
			LCD_DisplayString(1, "reading about   embedded systems");
			_delay_ms(12000);	
			LCD_DisplayString(1, "something weird happens. ^");
			_delay_ms(12000);		
			break;
		case _51:
			LCD_DisplayString(1, "You teleport to his house.");
			_delay_ms(12000);
			LCD_DisplayString(1, "Then go         incognito.");
			_delay_ms(12000);
			LCD_DisplayString(1, "Oh my... ^");
			_delay_ms(12000);
			break;		
		case _52:
			LCD_DisplayString(1, "Should I ask    for consent? ^");
			_delay_ms(12000);	
			break;		
		case _53:
			LCD_DisplayString(1, "^ Ask for it    v Dont ask");
			_delay_ms(12000);
			break;			
		case _54:
			LCD_DisplayString(1, "Jeff: Yes and   thanks");
			_delay_ms(12000);	
			LCD_DisplayString(1, "for asking. ^");
			_delay_ms(12000);		
			break;
		case _55:
			LCD_DisplayString(1, "Jeff: Why no askfor consent?");
			_delay_ms(12000);		
			LCD_DisplayString(1, "Jeff: What if I don't want to?");
			score = score - 1;
			state = check_score(state);
			_delay_ms(12000);	
			LCD_DisplayString(1, "^ Score: ");
			LCD_WriteData(score + '0');
			_delay_ms(12000);
			break;
		case _56:
			LCD_DisplayString(1, "Jeff makes a    duck face.");
			_delay_ms(12000);
			LCD_DisplayString(1, "And quacks very very loudly. ^");
			_delay_ms(12000);	
			break;		
		case mission_statement: //There is no way to get to this state.
			LCD_DisplayString(1, "Visual novels   can change");
			_delay_ms(12000);	
			LCD_DisplayString(1, "the world.      And create");
			_delay_ms(12000);		
			LCD_DisplayString(1, "a new social    movement.");
			_delay_ms(12000);
			LCD_DisplayString(1, "Let's create    a new");
			_delay_ms(12000);
			LCD_DisplayString(1, "entertainment   culture!");
			_delay_ms(12000);
			LCD_DisplayString(1, "Together!");
			_delay_ms(12000); //Rather it serves as a piece to data mine.
			break; //Some visual novel readers read the game's files to find
		case menu: //how to get certain dialogue in the game.
			score = 3;
			LCD_DisplayString(1, "Jeffrey McDanielDating Simulator");
			_delay_ms(18000);
			LCD_DisplayString(1, "Yes you read    that right."); 
			_delay_ms(12000);
			LCD_DisplayString(1, "Are you ready   for an exciting"); 
			_delay_ms(12000);
			LCD_DisplayString(1, "adventure with  your idol?"); 
			_delay_ms(12000);
			LCD_DisplayString(1, "Press up when   you see ^"); 
			_delay_ms(12000);
			LCD_DisplayString(1, "Press down when you see v"); 
			_delay_ms(12000);
			LCD_DisplayString(1, "Win by making   less than");
			_delay_ms(12000);
			LCD_DisplayString(1, "3 wrong choices.");
			_delay_ms(12000);
			LCD_DisplayString(1, "Score: ");
			LCD_WriteData(score + '0');
			_delay_ms(12000);
			LCD_DisplayString(1, "^ Play          v Quit"); 
			_delay_ms(12000);	
			break;		
		case quit:
			LCD_DisplayString(1, "Oh okay then.   I see."); 
			_delay_ms(12000);			
			LCD_DisplayString(1, "It's not like I wanted you"); 
			_delay_ms(12000);
			LCD_DisplayString(1, "to play this    game or anything"); 
			_delay_ms(12000);
			LCD_DisplayString(1, "B-baka!!"); 
			_delay_ms(20000);
			LCD_DisplayString(1, "Press up to     return to menu ^");
			_delay_ms(12000);
			break;
		case win:
			LCD_DisplayString(1, "THE END");
			_delay_ms(20000);		
			LCD_DisplayString(1, "Congrats you're a beast!");
			_delay_ms(12000);
			LCD_DisplayString(1, "You won!! And   got Jeff'd!");
			_delay_ms(12000);	
			LCD_DisplayString(1, "Play again? ^");
			_delay_ms(12000);
			break;
		case lose:
			LCD_DisplayString(1, "GAME OVER");
			_delay_ms(20000);	
			LCD_DisplayString(1, "You failed to   get Jeff'd... ^");
			_delay_ms(12000);
			break;
		default:
			break;
	}
	return state;
}

//---------------------LED MATRIX----------------------

struct number{
	unsigned char name;
	unsigned char arr_C[8];
	unsigned char arr_B[8];
	unsigned char length;
};

int main(void) {
	
	DDRA = 0x00; PORTA = 0xFF; //accepts joystick inputs
	DDRB = 0xFF; PORTB = 0x00; //outputs colors on LED Matrix
	DDRC = 0xFF; PORTC = 0x00; //outputs colors on LED Matrix and characters to LCD
	DDRD = 0xFF; PORTD = 0x00; //outputs led lights to debug ADC used for joystick
	
	//initialize timer
	TimerSet(1000);
	TimerOn();
	
	//initialize game
	state = init;
	
	//initialize ADC and LCD
	ADC_init();
	LCD_init();
		
	score = 3; //initial score
	LCD_ClearScreen();
	LCD_Cursor(1);
	
	struct number dir[3] = {
		{'1',{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},3},
		{'2',{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},3},
		{'3',{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},3}
	};


	//variables for LED matrix
	unsigned char j = 0;
	unsigned char k = 0;
	unsigned short i = 0;

	unsigned char ArrowUp[8] = { 0x4,0xE,0x1F,0x4,0x4,0x4,0x4,0x0 };
	unsigned char ArrowDown[8] = { 0x4,0x4,0x4,0x4,0x1F,0xE,0x4,0x0 };
	unsigned char Heart[8] = { 0x0,0xA,0x15,0x11,0xA,0x4,0x0,0x0 };
	unsigned char Smile[8] = { 0x0,0xa,0xa,0x0,0x11,0xe,0x0,0x0 };
	unsigned char Frown[8] = { 0x0,0xa,0xa,0x0,0xe,0x11,0x0,0x0 };
	unsigned char Sample5[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18 };
	unsigned char Sample6[8] = { 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x00, 0x00 };
	unsigned char Sample7[8] = { 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00 };

	LCD_Custom_Char1(0, ArrowUp);
	LCD_Custom_Char1(1, ArrowDown);
	LCD_Custom_Char1(2, Heart);
	LCD_Custom_Char1(3, Smile);
	LCD_Custom_Char1(4, Frown);
	LCD_Custom_Char1(5, Sample5);
	LCD_Custom_Char1(6, Sample6);
	LCD_Custom_Char1(7, Sample7);

	LCD_Custom_Char2(0, ArrowUp);  //Test output custom chars
	LCD_Custom_Char2(1, ArrowDown);
	LCD_Custom_Char2(2, Heart);
	LCD_Custom_Char2(3, Smile);
	LCD_Custom_Char2(4, Frown);
	LCD_Custom_Char2(5, Sample5);
	LCD_Custom_Char2(6, Sample6);
	LCD_Custom_Char2(7, Sample7);

	_delay_ms(20000);

	LCD_DisplayString(1, "Press up to     initialize game ^"); 

	while(1) {
		
		x = ReadADC(0);
		y = ReadADC(1);
		
		led = 0x00;
		
		//reset button
		if(PINA == 0xF7){ 
			LCD_Custom_Char2(0, ArrowUp);  //Test output custom chars
			LCD_Custom_Char2(1, ArrowDown);
			LCD_Custom_Char2(2, Heart);
			LCD_Custom_Char2(3, Smile);
			LCD_Custom_Char2(4, Frown);
			LCD_Custom_Char2(5, Sample5);
			LCD_Custom_Char2(6, Sample6);
			LCD_Custom_Char2(7, Sample7);
			_delay_ms(10000);
			LCD_DisplayString(1, "Game reset! ^"); 
			_delay_ms(12000);
			state = init;
		}
		
		if(y > 900) {
			led = 0x01;
			state = sm_tick(state);
		}
		else if(y < 100) {
			led = 0x02;
			state = sm_tick(state);
		}
		
		PORTD = led; //to debug direction of joystick

		//to test LED matrix
		if(i == 400){
			j++;
			if(j == 4){
				j = 0;
			}
			i = 0;
		}
		PORTB = dir[j].arr_B[k];
		PORTC = dir[j].arr_C[k];
		
		k = k + 1;
		i = i + 1;
		
		if(k == dir[j].length){
			k = 0;
		}
		
		while(!TimerFlag);
		TimerFlag = 0;
	}
	return 1;
}
