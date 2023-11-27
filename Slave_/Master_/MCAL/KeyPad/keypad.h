/*
 * keypad.h
 *
 * Created: 27-Oct-23 9:29:56 AM
 *  Author: mosta
 */ 
#include "../LCD/lcd.h"
#include "../../utilities/registers.h"
#include "../../utilities/bit_manipulation.h"
#include "../TIMER0/timer0.h"

#ifndef KEYPAD_H_
#define KEYPAD_H_


void KEYPAD_init(void);
uint8_t GET_KEY(void);
void KEYPAD_start(void);
#endif /* KEYPAD_H_ */