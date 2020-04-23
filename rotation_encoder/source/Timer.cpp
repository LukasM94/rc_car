
#include <Timer.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <config.h>

static void (*callbackFunction)(void*);
static void* callbackArgument;
static volatile uint16_t counter  = 0;

//---------------------------------------------------------------------
void Timer::init()
{
  // set timer0 counter initial value to 0
  TCNT0 = 0x00;

  // start timer0 with /8 prescaler
  switch (PRESCALE)
  {
    case 1:
      TCCR0B = (1<<CS00);
      break;
    case 8:
      TCCR0B = (1<<CS01);
      break;
    case 64:
      TCCR0B = (1<<CS01) | (1<<CS00);
      break;
    case 256:
      TCCR0B = (1<<CS02);
      break;
    case 1024:
      TCCR0B = (1<<CS02) | (1<<CS00);
      break;
    default:
      TCCR0B = 0;
  }
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
  LED_TOOGLE;
  // if (counter++ > (TIME / ONE_TICK))
  // {
  //   counter = 0;
  //   callbackFunction(callbackArgument);
  // }
}