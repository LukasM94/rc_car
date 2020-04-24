
#include <config.h>
#include <Encoder.h>

//---------------------------------------------------------------------
void initLed();
void initEncoder();

//---------------------------------------------------------------------
struct Encoder encoder;

//---------------------------------------------------------------------
int main()
{
  cli();
  initLed();
  initEncoder();
  sei();

  encoder.run(&encoder);
  
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
  Encoder_ctor(&encoder);
  encoder.init(&encoder);
  encoder.startTimer(&encoder);
}