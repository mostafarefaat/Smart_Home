/*
 * keypad.c
 *
 * Created: 27-Oct-23 9:29:42 AM
 *  Author: mosta
 */ 
#include "keypad.h"


uint8_t key;


void KEYPAD_init(void)
{
	DDRA = 0x0F;
	DDRB = 0xFF;
	PORTA = 0xFF;
	PORTB = 0x00;
		
}
uint8_t GET_KEY(void)
{
			/*First ROW*/
	if(READ_BIT(PINA,PIN4) == 0)
	{
		while(READ_BIT(PINA,PIN4) == 0);
		key = '7';
		return key;
	}
	else if(READ_BIT(PINA,PIN5) == 0)
	{
		while(READ_BIT(PINA,PIN5) == 0);
		key = '8';
		return key;
	}
	else if(READ_BIT(PINA,PIN6) == 0)
	{
		while(READ_BIT(PINA,PIN6) == 0);
		key = '9';
		return key;
	}
	else if(READ_BIT(PINA,PIN7) == 0)
	{
		while(READ_BIT(PINA,PIN7) == 0);
		key = 47; /* / Division */
		return key;
	}

	SET_BIT(PORTA,PIN0);
	TIMER0_delay(10,no_prescale);
	
			/*Second ROW*/
	ClEAR_BIT(PORTA,PIN1);
	if(READ_BIT(PINA,PIN4) == 0)
	{
		while(READ_BIT(PINA,PIN4) == 0);
		key = '4';
		return key;	
	}
	else if(READ_BIT(PINA,PIN5) == 0)
	{
		while(READ_BIT(PINA,PIN5) == 0);
		key = '5';
		return key;
	}
	else if(READ_BIT(PINA,PIN6) == 0)
	{
		while(READ_BIT(PINA,PIN6) == 0);
		key = '6';
		return key;
	}
	else if(READ_BIT(PINA,PIN7) == 0)
	{
		while(READ_BIT(PINA,PIN7) == 0);
		key = 42;    // * multiply
		return key;
	}
	SET_BIT(PORTA,PIN1);
	TIMER0_delay(10,no_prescale);
	
			/*Third ROW*/
	ClEAR_BIT(PORTA,PIN2);
	if(READ_BIT(PINA,PIN4) == 0)
	{
		while(READ_BIT(PINA,PIN4) == 0);
		key = '1';
		return key;
	}
	else if(READ_BIT(PINA,PIN5) == 0)
	{
		while(READ_BIT(PINA,PIN5) == 0);
		key = '2';
		return key;
	}
	else if(READ_BIT(PINA,PIN6) == 0)
	{
		while(READ_BIT(PINA,PIN6) == 0);
		key = '3';
		return key;
	}
	else if(READ_BIT(PINA,PIN7) == 0)
	{
		while(READ_BIT(PINA,PIN7) == 0);
		key = 45; // - Subtract
		return key;
	}
	SET_BIT(PORTA,PIN2);
	TIMER0_delay(10,no_prescale);
	
			/*Fourth ROW*/
	ClEAR_BIT(PORTA,PIN3);
	if(READ_BIT(PINA,PIN4) == 0)
	{
		while(READ_BIT(PINA,PIN4) == 0);
		key = 'c';
		return key;
	}
	else if(READ_BIT(PINA,PIN5) == 0)
	{
		while(READ_BIT(PINA,PIN5) == 0);
		key = '0';
		return key;
	}
	else if(READ_BIT(PINA,PIN6) == 0)
	{
		while(READ_BIT(PINA,PIN6) == 0);
		key = '=';
		return key;
	}
	else if(READ_BIT(PINA,PIN7) == 0)
	{
		while(READ_BIT(PINA,PIN7) == 0);
		key = 43;  // + Add
		return key;		
	}
	SET_BIT(PORTA,PIN3);
	TIMER0_delay(10,no_prescale);	
		
	key = '_';
	return key;	
	
}
void KEYPAD_start(void)
{
	ClEAR_BIT(PORTA,PIN0);
	if(PINA != 0xFF )
	{
		x = GET_KEY();
		if(x != '_')
		{
			if(x == 'c') 
			{
				LCD_4_bit_sendCommand(0x01);
			}
			
			else
			{
				if(string_counter <= 3)
				{
					pass_string[string_counter] = x;
					string_counter++;
				}
				
				LCD_4_bit_sendChar(x);
			}
			
		}
		TIMER0_delay(100,no_prescale);
	}	
}