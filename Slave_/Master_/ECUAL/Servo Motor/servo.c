/*
 * servo.c
 *
 * Created: 16-Nov-23 2:26:18 PM
 *  Author: mosta
 */ 
//include .h

#include "servo.h"


void servo_move_90_deg(void)
{
	  DIO_write(PORT_D,PIN5,HIGH);
	  Servo_T0Delay_90();
	  DIO_write(PORT_D,PIN5,LOW);
	  TIMER0_delay(2000,no_prescale);	
}
void servo_move_negative_90_deg(void)
{
	  PORTD |= (1<<5);
	  Servo_T0Delay_negative_90();
	  PORTD &= ~(1<<5);
	  TIMER0_delay(2000,no_prescale);
}


void Servo_T0Delay_90()
{
	unsigned int i = 0;
	
	while(i<10)  /*value of i by testing*/
	{
		TCNT0 = 0x00;
		TCCR0 = 0x01;
		while((TIFR & (1<<PIN0)) == 0);
		TCCR0 = 0x00;
		TIFR |= (1<<0);
		i++;
	}

}

void Servo_T0Delay_negative_90()
{
	unsigned int i = 0;
	
	while(i<2)  /*value of i by testing*/
	{
		TCNT0 = 0x00;
		TCCR0 = 0x01;
		while((TIFR & (1<<PIN0)) == 0);
		TCCR0 = 0x00;
		TIFR |= (1<<0);
		i++;
	}
}
