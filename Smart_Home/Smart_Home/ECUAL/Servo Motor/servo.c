/*
 * servo.c
 *
 * Created: 16-Nov-23 2:26:18 PM
 *  Author: mosta
 */ 
//include .h
#include "../../MCAL/DIO Driver/dio.h"
#include "servo.h"
#include <util/delay.h>

void servo_move_zero_deg(void)
{
	  DIO_write(PORT_D,PIN5,HIGH);
	  _delay_ms(1);
	  DIO_write(PORT_D,PIN5,LOW);
	  _delay_ms(2000);
}
void servo_move_90_deg(void)
{
	  DIO_write(PORT_D,PIN5,HIGH);
	  _delay_ms(1.5);
	  DIO_write(PORT_D,PIN5,LOW);
	  _delay_ms(2000);	
}
void servo_move_180_deg(void)
{
	  DIO_write(PORT_D,PIN5,HIGH);
	  _delay_ms(2);
	  DIO_write(PORT_D,PIN5,LOW);
	  _delay_ms(2000);
}