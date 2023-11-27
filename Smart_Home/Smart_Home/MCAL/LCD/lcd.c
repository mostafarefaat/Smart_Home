/*
 * lcd.c
 *
 * Created: 26-Oct-23 5:46:03 PM
 *  Author: mosta
 */ 
#include "lcd.h"

void LCD_8_bit_init(void)
{
	LCD_Command_Port_Dir |= (1<<0) | (1<<1) | (1<<2);  //Make PIN0, PIN1, PIN2 in PORTD outputs
	LCD_Data_PORT_Dir = 0xFF; //Make all pins in PORTC outputs
	TIMER_set(Normal);
	TIMER0_delay(20, no_prescale);	//LCD power ON delay always >15ms
	LCD_8_bit_sendCommand(0x38);	//initialization of 16x2 LCD in 8 bit mode
	LCD_8_bit_sendCommand(0x0C);	//Display ON, Cursor OFF
	LCD_8_bit_sendCommand(0x06);	//Auto increment cursor
	LCD_8_bit_sendCommand(0x01);	//clear Display
	LCD_8_bit_sendCommand(0x80);	//cursor at home position
	
}
void LCD_8_bit_sendCommand(uint8_t command)
{
	LCD_Data_PORT = command;
	LCD_Command_Port &= ~(1<<RS); // RS PIN = 0 command register
	LCD_Command_Port &= ~(1<<RW); // RW PIN = 0 write operation
	LCD_Command_Port |= (1<<EN); // EN PIN = 1 Enable pulse high
	TIMER0_delay(1,no_prescale);
	LCD_Command_Port &= ~(1<<EN); // EN PIN = 0 Enable pulse low
	TIMER0_delay(1,no_prescale);
	
	
}
void LCD_8_bit_sendChar(uint8_t character)
{
	LCD_Data_PORT = character;
	LCD_Command_Port |= (1<<RS); // RS PIN = 1 data register
	LCD_Command_Port &= ~(1<<RW); // RW PIN = 0 write operation
	LCD_Command_Port |= (1<<EN); // EN PIN = 1 Enable pulse high
	TIMER0_delay(1,no_prescale);
	LCD_Command_Port &= ~(1<<EN); // EN PIN = 0 Enable pulse low
	TIMER0_delay(1,no_prescale);
	
}
void LCD_8_bit_sendString(uint8_t *str)
{
	uint8_t i;
	
	for(i=0; *(str + i) != 0; i++)	//send each character until str is null
	{
		
		LCD_8_bit_sendChar(*(str + i)); // call the LCD_sendChar function each time
	}
	
}

void LCD_4_bit_init(void)
{
	LCD_Command_Port_Dir |= (1<<0) | (1<<1) | (1<<2);  //Make PIN0, PIN1, PIN2 in PORTD outputs
	LCD_Data_PORT_Dir |= (1<<4) | (1<<5) | (1<<6) | (1<<7); //Make PIN4, PIN5, PIN6, PIN7 in PORTC outputs
	TIMER_set(Normal);
	TIMER0_delay(20, no_prescale);	//LCD power ON delay always >15ms
	LCD_4_bit_sendCommand(0x02);	//Send for 4 bit initialization of the LCD
	LCD_4_bit_sendCommand(0x28);	//initialization of 5x7 LCD in 4 bit mode
	LCD_4_bit_sendCommand(0x0C);	//Display ON, Cursor OFF
	LCD_4_bit_sendCommand(0x06);	//Auto increment cursor
	LCD_4_bit_sendCommand(0x01);	//clear Display
	LCD_4_bit_sendCommand(0x80);	//cursor at home position	
	
}
void LCD_4_bit_sendCommand(uint8_t command)
{
	LCD_Data_PORT = (LCD_Data_PORT &0x0F) | (command & 0xF0); //Sending upper nibble
	
	LCD_Command_Port &= ~(1<<RS); // RS PIN = 0 command register
	
	LCD_Command_Port &= ~(1<<RW); // RW PIN = 0 write operation
	
	LCD_Command_Port |= (1<<EN); // EN PIN = 1 Enable pulse high
	
	TIMER0_delay(1,no_prescale);
	
	LCD_Command_Port &= ~(1<<EN); // EN PIN = 0 Enable pulse low
	
	TIMER0_delay(1,no_prescale);
	
	LCD_Data_PORT = (LCD_Data_PORT &0x0F) | (command << 4); //Sending upper nibble
		
	LCD_Command_Port |= (1<<EN); // EN PIN = 1 Enable pulse high
	
	TIMER0_delay(1,no_prescale);
	
	LCD_Command_Port &= ~(1<<EN); // EN PIN = 0 Enable pulse low
	
	TIMER0_delay(1,no_prescale);
}
void LCD_4_bit_sendChar(uint8_t character)
{
	LCD_Data_PORT = (LCD_Data_PORT &0x0F) | (character & 0xF0); //Sending upper nibble
	
	LCD_Command_Port |= (1<<RS); // RS PIN = 1 data register
	
	LCD_Command_Port &= ~(1<<RW); // RW PIN = 0 write operation
	
	LCD_Command_Port |= (1<<EN); // EN PIN = 1 Enable pulse high
	
	TIMER0_delay(1,no_prescale);
	
	LCD_Command_Port &= ~(1<<EN); // EN PIN = 0 Enable pulse low
	
	TIMER0_delay(1,no_prescale);
	
	LCD_Data_PORT = (LCD_Data_PORT &0x0F) | (character << 4); //Sending upper nibble
	
	LCD_Command_Port |= (1<<EN); // EN PIN = 1 Enable pulse high
	
	TIMER0_delay(1,no_prescale);
	
	LCD_Command_Port &= ~(1<<EN); // EN PIN = 0 Enable pulse low
	
	TIMER0_delay(1,no_prescale);
}
void LCD_4_bit_sendString(uint8_t *str)
{
	uint8_t i;

	for(i=0; *(str + i) != 0; i++)	//send each character until str is null
	{
		
		LCD_4_bit_sendChar(*(str + i)); // call the LCD_sendChar function each time
	}
	
}


