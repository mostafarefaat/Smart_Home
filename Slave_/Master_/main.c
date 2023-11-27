/*
 * My First Project.c
 *
 * Write high on pin 0 on PORTA
 
 
 * Created: 19-Oct-23 10:59:31 AM
 * Author : mostafa
 */ 

//#include <avr/io.h>
//#include "MCAL/DIO Driver/dio.h"
#include "Application/app.h"



int main(void)
{
    /* Replace with your application code */
	/* initialization */
	/*Declaring and Initialization of variables*/	
	app_init();
	
	while(1)
	{
		app_start();
	}
	
	return 0;
}




	


