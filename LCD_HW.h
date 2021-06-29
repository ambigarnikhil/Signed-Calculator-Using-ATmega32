/*
 * LCD_HW.h
 *  Author: Nikhil
 */ 


#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#include <avr/io.h>

#include <util/delay.h>

#define set_bit(reg,pos) reg|=(1<<pos)		// used to set bit x on register x to 1

#define clr_bit(reg,pos) reg&=~(1<<pos)		// used to clear bit x on register x to 0

#define tog_bit(reg,pos) reg^=(1<<pos)		// used to toggle bit x on register x from x to x`

/********************************************************************************************************/

/*SEND DATA TO HW PORT*/

void port(char cmd_port);

void port(char cmd_port)
{
	if(cmd_port&1)
	set_bit(PORTB,0);		//IF 1ST BIT = 1 RAISE PB0
	else
	clr_bit(PORTB,0);		//IF 1ST BIT = 0 CLR PB0
	
	if(cmd_port&2)
	set_bit(PORTB,1);		//IF 2ND BIT = 1 RAISE PB1
	else
	clr_bit(PORTB,1);		//IF 2ND BIT = 0 CLR PB1
	
	if(cmd_port&4)
	set_bit(PORTB,2);		//IF 3RD BIT = 1 RAISE PB2
	else
	clr_bit(PORTB,2);		//IF 3RD BIT = 0 CLR PB2
	
	if(cmd_port&8)
	set_bit(PORTB,3);		//IF 4TH BIT = 1 RAISE PB3
	else
	clr_bit(PORTB,3);		//IF 4TH BIT = 0 CLR PB3
}

/*SWITCH BETWEEN COMMAND MODE OR DATA MODE*/

void mode_select(char m);

void mode_select(char m)	 
{
	if ( m == 0)
	clr_bit(PORTB,5);		// RS = 0 --> SWITCH TO LCD CONTROL REGISTER - COMMAND MODE
	
	if ( m == 1)
	set_bit(PORTB,5);		// RS = 1 --> SWITCH TO LCD DATA REGISTER - DATA MODE
}

/*TRIIGERS THE ENABLE BIT*/

void enb_tri(void);

void enb_tri(void)
{
	set_bit(PORTB,4);		//RAISE ENABLE EN = 1
	_delay_us(50);
	
	clr_bit(PORTB,4);		//TOGGLE ENABLE
	_delay_us(500);			//HIGH DELAY TO PREVENT DATA OVER FLOW
}

/*INITIALIZE DATABUS TO HW PORT*/

void set_port(void);

void set_port(void)
{
	DDRB |= 0X3F;	//ASSIGN DATABUS PB0-PB3, CONTROLBUS EN-PB4 RS-PB5
}