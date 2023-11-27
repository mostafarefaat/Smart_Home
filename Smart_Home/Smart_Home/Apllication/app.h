/*
 * app.h
 *
 * Created: 19-Oct-23 7:00:23 PM
 *  Author: mosta
 */ 
//include .h
//#include "../MCAL/I2C/i2c.h"
#include "../MCAL/SPI/spi.h"
//#include "../MCAL/UART/uart.h"
#include "../MCAL/KeyPad/keypad.h"
#include "../MCAL/LCD/lcd.h"
#include "../MCAL/EEPROM/eeprom.h"
//#include "../MCAL/ADC/adc.h"
#include "../MCAL/Interrupt Library/interrupt.h"
#include "../ECUAL/LED Driver/led.h"
#include "../ECUAL/Button Driver/button.h"
#include "../ECUAL/Servo Motor/servo.h"
#include "../MCAL/TIMER0/timer0.h"

#ifndef APP_H_
#define APP_H_

#define ISR_Called 1
#define ISR_Not_Called 0

uint8_t button_1_state;
uint8_t button_2_state;

uint8_t password_correct;
uint8_t new_pass;

uint8_t first_number;
uint8_t second_number;
uint8_t third_number;
uint8_t fourth_number;

uint8_t ISR_State;



void app_init(void);
void app_start(void);
void password_check(void);



#endif /* APP_H_ */