/*
 * Smart_Home.c
 *
 * Created: 16-Nov-23 2:16:44 PM
 * Author : mosta
 */ 

#include "Apllication/app.h"



int main(void)
{
	app_init();
	
	password_check();
	if(password_correct)
	{
		Spi_Master_send(Open_Door);
		Spi_Master_send(Turn_On);
		while(1)
		{
			app_start();
		}		
	}
}
ISR(EXT_INT_1)
{
	Spi_Master_send(Close_Door);
}
ISR(EXT_INT_2)
{
	Spi_Master_send(Turn_Off);
}




