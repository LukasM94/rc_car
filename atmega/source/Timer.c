
#include "Timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

static void (*timerFunction)();

//---------------------------------------------------------------------
void timerInit()
{
  // set timer0 counter initial value to 0
  TCNT0 = 0x00;

  // start timer0 with /1024 prescaler
  TCCR0B |= (1<<CS02) | (1<<CS00);
}

//---------------------------------------------------------------------
void timerStart()
{
  // enable timer overflow interrupt for Timer0
  TIMSK0 |= (1<<TOIE0);
}

//---------------------------------------------------------------------
void timerStop()
{
  // enable timer overflow interrupt for Timer0
  TIMSK0 &= ~(1<<TOIE0);
}

//---------------------------------------------------------------------
void timerSetCallbacks(void (*f_ptr)())
{
  timerFunction = f_ptr;
}

//---------------------------------------------------------------------
ISR(TIMER0_OVF_vect)
{
  timerFunction();
}