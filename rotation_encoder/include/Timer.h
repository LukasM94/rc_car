

#ifndef TIMER_H_
#define TIMER_H_

#include <avr/interrupt.h>

#define PRESCALE 8
#define ONE_TICK ((1000000 * PRESCALE) / F_CPU) // us
#define TIME     10000 // us

namespace Timer
{
  void init();
  void start();
  void stop();
  void setCallbacks(void (*recv)(void*), void* arg);
}

ISR(TIMER0_OVF_vect);

#endif