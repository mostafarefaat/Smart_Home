/*
 * button.h
 *
 * Created: 19-Oct-23 8:01:42 PM
 *  Author: mosta
 */ 
//include .h
#include "../../MCAL/DIO Driver/dio.h"
#include "../../MCAL/Interrupt Library/interrupt.h"

#define Button_Port PORT_D

#define Button_1_Pin PIN2
#define Button_2_Pin PIN1

//Pull Down buttons configuration
#define Button_Pressed 1
#define Button_Not_Pressed 0

//Pull Up buttons configuration
#define Button_Pressed_Up 0
#define Button_Not_Pressed_Up 1



#ifndef BUTTON_H_
#define BUTTON_H_

void Button_init(uint8_t button_port, uint8_t button_pin);	//initialize the button to be input

void Button_read(uint8_t button_port, uint8_t button_pin, uint8_t *value); //reads the output of the button (Pressed or Not Pressed)


#endif /* BUTTON_H_ */