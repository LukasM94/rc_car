

#ifndef TIMER_H_
#define TIMER_H_

#include <avr/interrupt.h>

void timerInit();
void timerStart();
void timerStop();
void timerSetCallbacks(void (*recv)(void*), void* arg);

ISR(TIMER0_OVF_vect);

#endif