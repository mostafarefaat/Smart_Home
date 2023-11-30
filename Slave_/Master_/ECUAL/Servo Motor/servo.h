/*
 * servo.h
 *
 * Created: 16-Nov-23 2:26:07 PM
 *  Author: mosta
 */ 
#include "../../MCAL/TIMER0/timer0.h"
#include "../../MCAL/DIO Driver/dio.h"

#ifndef SERVO_H_
#define SERVO_H_


void servo_move_90_deg(void);
void servo_move_negative_90_deg(void);
void Servo_T0Delay_90();
void Servo_T0Delay_negative_90();


#endif /* SERVO_H_ */