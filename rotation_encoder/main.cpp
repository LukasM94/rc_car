
#include <config.h>
#include <Encoder.h>

//---------------------------------------------------------------------
void initPeripherial();
void initEncoder();

//---------------------------------------------------------------------
Encoder encoder;

//---------------------------------------------------------------------
int main()
{
  cli();
  initPeripherial();
  initEncoder();
  sei();

  encoder.run();
  
  while (1)
  {
    _delay_ms(500);
    LED_TOOGLE;
  }
}

//---------------------------------------------------------------------
void initPeripherial()
{
  LED_DDR           |= (1 << LED_PIN);
  LIGHT_BARRIER_DDR &= ~(1 << LIGHT_BARRIER0_PIN);
  LIGHT_BARRIER_DDR &= ~(1 << LIGHT_BARRIER1_PIN);
}

//---------------------------------------------------------------------
void initEncoder()
{
  encoder.init();
  encoder.startTimer();
}