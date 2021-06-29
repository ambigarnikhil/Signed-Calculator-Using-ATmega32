/*
 * calc.h
 *  Author: Nikhil
 */ 

#include <stdio.h>

#include "keypad.h"

#include "LCD_ML.h"



static unsigned int key;		//key variable to store pressed key

static unsigned int op;			//op variable to store operation ID and op_char for operation symbol

static char op_char;
		
static long int a, b;					//a & b variables to store two numbers of operation
			
static float result;			//result value should be stored in this variable
			
char lcd_buf[50];		//lcd_buf array is the lcd buffer

int c,d;


/*initialize keypad and lcd*/
void cal_init(void);

void cal_init(void)
{		
	Key_init();
	
	lcd_init();
}

/*determine calculator operation*/
void cal_op(void);

void cal_op(void)
{
	 if(key==0x0D)			//operation add
	{
		key=0;
		op=1;
		op_char='+';
	}
	
	else if(key==0x0C)		//operation subtraction
	{
		key=0;
		op=2;
		op_char='-';
	}
	
	else if(key==0x0B)		//operation multiplication
	{
		key=0;
		op=3;
		op_char='x';
	}

	else if(key==0x0A)		//operation division
	{
		key=0;
		op=4;
		op_char='/';
	}
	
	else if(key==0x0E)		//operation execution
	{
		key=0;
		op=5;
	}

	else if(key=='0')		//allow ZERO-Bug Fix
	{
		key=0;
	}
	
	else if(key==0x0F)		//operation on/clear
	{
		a=0;	
		b=0;
		result=0;
		op=0;
		key = 0;
		clr_dis();
	}
}

/*run the calculation process*/
void cal_run(void);

void cal_run(void)
{

		if(op==0)										//if no operation is selected then store the first number
		{
			a=a*10+key;			//storing number of n digits
			c=a;
			sprintf(lcd_buf,"%1li",a);
			dis_string(0,0,lcd_buf);
		}
														//if Any operation is selected then start storing the second number
		else if(op==1 || op==2 || op==3 || op==4)
		{
			//key = key_scan();
			b=b*10+key;									//display both numbers at the same time through lcd buffer
			//result=a+b;
			d=b;
			sprintf(lcd_buf,"%1li%c%1li",a,op_char,b);
			dis_string(0,0,lcd_buf);
		}
		
		else if(op==5)									//if operation execute is selected
		{	
		    int c;
														//select between different operations 
			if(op_char=='+')
			{
				c=a+b;
				sprintf(lcd_buf,"%1li%c%1li=%d",a,op_char,b,c);
				//sprintf(lcd_buf,"%1li",c);
				dis_string(0,0,lcd_buf);
				//result=(c+d);
			}
			
			else if(op_char=='-')
			{
				c=a-b;
				sprintf(lcd_buf,"%1li%c%1li=%d",a,op_char,b,c);
				//sprintf(lcd_buf,"%1li",c);
				dis_string(0,0,lcd_buf);
				//result=(c-d);
			}
			
			else if(op_char=='x')
			{
				//result=c*d;
				c=a*b;
				sprintf(lcd_buf,"%1li%c%1li=%d",a,op_char,b,c);
				//sprintf(lcd_buf,"%1li",c);
				dis_string(0,0,lcd_buf);
			}
			else if(op_char=='/')
			{
				//result=(float)c/d;
				c=a/b;
				sprintf(lcd_buf,"%1li%c%1li=%d",a,op_char,b,c);
				//sprintf(lcd_buf,"%1li",c);
				dis_string(0,0,lcd_buf);
			}
														//display the result 
			//sprintf(lcd_buf,"=%f",result);
			//dis_string(1,1,lcd_buf);
				
			a=0;										//clear the memory for next calculation
			b=0;
			result=0;
			op=0;
		}
}

/*run the calculator*/
void calculate(void);

void calculate(void)
{
		key = key_scan();		//obtain key pressed
				
		if (key != 0)			//if key = true
		{
			cal_op();			//first check if pressed key is operation identifier
			cal_run();			//store number or apply operation
			key = 0;			//clear key for next trial
		}
}