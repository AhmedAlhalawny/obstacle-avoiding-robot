/*
 * UltraSonic_Drive.h
 *
 * Created: 3/6/2022 5:15:37 PM
 *  Author: Ahmed ALhalawany
 */ 


#ifndef ULTRASONIC_DRIVE_H_
#define ULTRASONIC_DRIVE_H_
#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL

volatile int    *TimerOverflow;     //timer 1 overflow flags
volatile double *timer0_count;
volatile uint8  *IC_count;      // input caption counts
volatile double *t1;
volatile double *t2;
volatile double *t3;
volatile float  *Ton;


void ultrsonic_update();
void ultrasonic_init_ISR(void);
uint16 ultrasonic_read();
uint16 ultrasonic_get_value(void);


#endif /* ULTRASONIC_DRIVE_H_ */