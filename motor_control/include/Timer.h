

#ifndef TIMER_H_
#define TIMER_H_

#include <avr/interrupt.h>

#define PRESCALE 1024

void timerInit();
void timerStart();
void timerStop();
void timerSetCallbacks(void (*recv)());

ISR(TIMER0_OVF_vect);

#endif