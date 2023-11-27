/*
 * lcd.h
 *
 * Created: 26-Oct-23 5:46:12 PM
 *  Author: mosta
 */ 

#include "../../utilities/registers.h"
#include "../TIMER0/timer0.h"

#ifndef LCD_H_
#define LCD_H_

#define LCD_Command_Port PORTD
#define LCD_Command_Port_Dir DDRD

#define LCD_Data_PORT PORTC
#define LCD_Data_PORT_Dir DDRC

#define RS PIN0
#define RW PIN1
#define EN PIN2

/*Macros for all the commands*/


void LCD_8_bit_init(void);
void LCD_8_bit_sendCommand(uint8_t command);
void LCD_8_bit_sendChar(uint8_t character);
void LCD_8_bit_sendString(uint8_t *str);

void LCD_4_bit_init(void);
void LCD_4_bit_sendCommand(uint8_t command);
void LCD_4_bit_sendChar(uint8_t character);
void LCD_4_bit_sendString(uint8_t *str);

	



#endif /* LCD_H_ */