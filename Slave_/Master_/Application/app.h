/*
 * app.h
 *
 * Created: 19-Oct-23 7:00:23 PM
 *  Author: mosta
 */ 
//include .h

#include "../MCAL/SPI/spi.h"
#include "../MCAL/KeyPad/keypad.h"
#include "../MCAL/ADC/adc.h"
#include "../MCAL/Interrupt Library/interrupt.h"
#include "../ECUAL/LED Driver/led.h"
#include "../ECUAL/Button Driver/button.h"
#include "../ECUAL/Servo Motor/servo.h"
#include "../MCAL/TIMER0/timer0.h"



#ifndef APP_H_
#define APP_H_

#define Close_Door 0
#define Open_Door 1
#define Turn_On 2
#define Turn_Off 3
#define Open_Temp_LCD 4
#define Get_Temp 5

uint8_t button_1_state;
uint8_t button_2_state;



void app_init(void);
void app_start(void);

void Temp_sensor_read(void);
void clear_temp_string(uint8_t *str);
void display_Temp_on_LCD(void);

#endif /* APP_H_ */