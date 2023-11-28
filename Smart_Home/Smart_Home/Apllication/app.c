/*
 * app.c
 *
 * Created: 19-Oct-23 7:00:14 PM
 *  Author: mosta
 */ 
//include app.h
#include "app.h"
#include <util/delay.h>

uint8_t welcome_string[] = "Welcome";
uint8_t enter_pass_string[] = "Enter Password";
uint8_t access_string[] = "ACCESS GRANTED";
uint8_t reset_string[] = "Enter New Pass";
uint8_t wrong_string[] = "Wrong Pass";
uint8_t success_string[] = "Pass changed";


void app_init(void)
{	

	DIO_init(PORT_D,PIN3,IN); /*Makes PIN3 in PORT D input pin for interrupt_1*/
	DIO_init(PORT_B,PIN2,IN); /*Makes PIN2 in PORT B input pin for interrup_2t*/
	
	LCD_4_bit_init();
	KEYPAD_init();
	Spi_Master_init();
	ISR_State = ISR_Not_Called;

	/*Enable the interrupts*/
	sei();
	/*Interrupt 1*/
	SET_BIT(MCUCR,PIN2);
	SET_BIT(MCUCR,PIN3);
	/*Interrupt 2*/
	SET_BIT(MCUCSR,PIN6);
	/*Interrupt 1 and Interrupt 2*/
	GICR  |= (1<<PIN5) | (1<<PIN7);

}

void app_start(void)
{	
	if(ISR_State == ISR_Not_Called)
	{
		Spi_Master_send(Get_Temp);
		TIMER0_delay(5000,no_prescale);
	}
	
}

void password_check(void)
{
	
	LCD_4_bit_sendString(welcome_string);
	TIMER0_delay(1000,no_prescale);
	LCD_4_bit_sendCommand(0x01);
	LCD_4_bit_sendString(enter_pass_string);
	TIMER0_delay(1000,no_prescale);
	LCD_4_bit_sendCommand(0x01);
	
	while(password_correct == 0)
	{
		KEYPAD_start();
		if(x == 'c')
		{
			string_counter = 0;
			if(new_pass == 1)
			{
			   EEPROM_write(0,pass_string[0]);
			   EEPROM_write(1,pass_string[1]);
			   EEPROM_write(2,pass_string[2]);
			   EEPROM_write(3,pass_string[3]);
			   LCD_4_bit_sendString(success_string);
			   TIMER0_delay(2000,no_prescale);
			   LCD_4_bit_sendCommand(0x01);
			   new_pass = 0;				
			}
			
			 first_number = EEPROM_read(0);
			 second_number = EEPROM_read(1);
			 third_number = EEPROM_read(2);
			 fourth_number = EEPROM_read(3);
			 
			if(pass_string[0] == first_number && pass_string[1] == second_number && pass_string[2] == third_number && pass_string[3] == fourth_number)
			{
				LCD_4_bit_sendString(access_string);
				TIMER0_delay(2000,no_prescale);
				LCD_4_bit_sendCommand(0x01);
				password_correct = 1;	
			}
			else if(pass_string[0] == '0' && pass_string[1] == '0' && pass_string[2] == '0' && pass_string[3] == '0')
			{
				LCD_4_bit_sendString(reset_string);
				new_pass = 1;
				TIMER0_delay(5000,no_prescale);
				LCD_4_bit_sendCommand(0x01);
			}
			else
			{
				LCD_4_bit_sendString(wrong_string);
				TIMER0_delay(2000,no_prescale);
				LCD_4_bit_sendCommand(0x01);
			}
			
		}
	}	
}
