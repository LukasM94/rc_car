
#include <Gpio.h>
#if defined(__arm__)
#include <wiringPi.h>
#endif
#include <config.h>
#include <debug.h>
#include <unistd.h>


Gpio::Gpio(std::string name) : 
  name_(name),
  led_green_pin_(-1), 
  led_red_pin_(-1), 
  button_pin_(-1)
{
  debug(GPIO, "ctor\n");
#if defined(__arm__)
  wiringPiSetupGpio();
#endif
}

Gpio::~Gpio()
{
  debug(GPIO, "dtor\n");
}

int Gpio::initLedGreen(uint8_t led_pin)
{
  if (initLed(led_pin) == 0)
  {
    led_green_pin_ = led_pin;
    return -1;
  }
  return 0;
}

int Gpio::initLedRed(uint8_t led_pin)
{
  if (initLed(led_pin) == 0)
  {
    led_red_pin_ = led_pin;
    return -1;
  }
  return 0;
}

int Gpio::initLed(uint8_t led_pin)
{
  if (gpioTestAndSet(led_pin))
  {
    debug(ERROR, "Gpio::initLed: Pin %d is already taken\n", led_pin);
    return -1;
  }
#if defined(__arm__)
  pinMode(led_pin, OUTPUT);
#endif
  debug(GPIO, "initLed: Pin %d is OUTPUT\n", led_pin);
  return 0;
}

int Gpio::initButton(uint8_t button_pin, void (*f_ptr)())
{
  button_pin_ = button_pin;
  if (gpioTestAndSet(button_pin_))
  {
    debug(ERROR, "Gpio::initButton: Pin %d is already taken\n", button_pin_);
    return -1;
  }
#if defined(__arm__)
  pinMode(button_pin_, INPUT);
  wiringPiISR(button_pin_, INT_EDGE_FALLING, f_ptr);
#endif
  debug(GPIO, "initButton: Pin %d is INPUT\n", button_pin_);
  return 0;
}

void Gpio::toggleLed(uint8_t led_pin)
{
#if defined(__arm__)
  if (digitalRead(led_pin))
  {
    digitalWrite(led_pin, LOW);
  }
  else
  {
    digitalWrite(led_pin, HIGH);
  }
#endif
}

void Gpio::onLed(uint8_t led_pin)
{
#if defined(__arm__)
  digitalWrite(led_pin, HIGH);
#endif
}

void Gpio::offLed(uint8_t led_pin)
{
#if defined(__arm__)
  digitalWrite(led_pin, LOW);
#endif
}
