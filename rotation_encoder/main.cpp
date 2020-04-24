
#include <config.h>
#include <Encoder.h>

//---------------------------------------------------------------------
void initLed();
void initEncoder();

//---------------------------------------------------------------------
Encoder encoder;

//---------------------------------------------------------------------
int main()
{
  cli();
  initLed();
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
void initLed()
{
  LED_DDR |= (1 << LED_PIN);
}

//---------------------------------------------------------------------
void initEncoder()
{
  encoder.init();
  encoder.startTimer();
}