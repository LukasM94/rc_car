
#include <Timer.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <config.h>

static void (*callbackFunction)(void*) = 0;
static void* callbackArgument          = 0;
static volatile uint16_t counter       = 0;

//---------------------------------------------------------------------
void Timer::init()
{
  // set timer0 counter initial value to 0
  TCNT0 = 0x00;

  // start timer0 with /8 prescaler
  TCCR0B = (1<<CS00);
}

//---------------------------------------------------------------------
void Timer::start()
{
  // enable timer overflow interrupt for Timer0
  TIMSK |= (1<<TOIE0);
}

//---------------------------------------------------------------------
void Timer::stop()
{
  // enable timer overflow interrupt for Timer0
  TIMSK &= ~(1<<TOIE0);
}

//---------------------------------------------------------------------
void Timer::setCallbacks(void (*recv)(void*), void* arg)
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
    if (callbackFunction != 0)
    {
      callbackFunction(callbackArgument);
    }
  }
}