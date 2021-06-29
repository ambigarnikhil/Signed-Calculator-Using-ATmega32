/*
 * main.c
 *
 * Created: 6/26/2021 10:18:31 PM
 * Author : Nikhil
 */

#include "calc.h"   

static long int a,b; 
int main(void)
{
	
	cal_init();
	
	dis_string(0,0,"When      Come    ;)");
	dis_string(1,4,"Dreams    True ;)");
	
	_delay_ms(50);
	
	for (int start = 0;start < 25; ++start)
	{
		_delay_ms(5);
		dis_shift('L');
	}
	
	while(1)
	{
		calculate();
	}
}

