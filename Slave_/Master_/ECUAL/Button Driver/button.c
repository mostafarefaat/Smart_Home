/*
 * button.c
 *
 * Created: 19-Oct-23 8:01:52 PM
 *  Author: mosta
 */ 
//include .h
#include "button.h"




void Button_init(uint8_t button_port, uint8_t button_pin)
{
	DIO_init(button_port, button_pin, IN);	
}
void Button_read(uint8_t button_port, uint8_t button_pin, uint8_t *value)
{
	DIO_read(button_port, button_pin, value);
}

void Button_ISR(void)
{


}