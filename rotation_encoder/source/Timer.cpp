
#include "Timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define PRESCALE  8
#define ONE_TICK ((1000000 * PRESCALE) / F_CPU) // us
#define TIME     10000 // us

static void (*callbackFunction)(void*);
static void* callbackArgument;
static volatile uint16_t counter  = 0;

//---------------------------------------------------------------------
void timerInit()
{
  // set timer0 counter initial value to 0
  TCNT0 = 0x00;

  // start timer0 with /8 prescaler
  switch (PRESCALE)
  {
    case 1:
      TCCR0B |= (1<<CS00);
      break;
    case 8:
      TCCR0B |= (1<<CS01);
      break;
    case 64:
      TCCR0B |= (1<<CS01) | (1<<CS00);
      break;
    case 256:
      TCCR0B |= (1<<CS02);
      break;
    case 1024:
      TCCR0B |= (1<<CS02) | (1<<CS00);
      break;
    default:
      TCCR0B = 0;
  }
}

//---------------------------------------------------------------------
void timerStart()
{
  // enable timer overflow interrupt for Timer0
  TIMSK |= (1<<TOIE0);
}

//---------------------------------------------------------------------
void timerStop()
{
  // enable timer overflow interrupt for Timer0
  TIMSK &= ~(1<<TOIE0);
}

//---------------------------------------------------------------------
void timerSetCallbacks(void (*recv)(void*), void* arg)
{
  callbackFunction = recv;
  callbackArgument = arg;
}

//---------------------------------------------------------------------
ISR(TIMER0_OVF_vect)
{
  if (counter++ > (TIME / ONE_TICK))
  {
    counter = 0;
    callbackFunction(callbackArgument);
  }
}