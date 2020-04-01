
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
  button_pin_(-1),
  reset_pin_(-1)
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

int Gpio::initReset(uint8_t reset_pin)
{
  reset_pin_ = reset_pin;
  if (gpioTestAndSet(reset_pin_))
  {
    debug(ERROR, "Gpio::initReset: Pin %d is already taken\n", reset_pin_);
    return -1;
  }
#if defined(__arm__)
  pinMode(reset_pin_, OUTPUT);
#endif
  debug(GPIO, "initReset: Pin %d is OUTPUT\n", reset_pin_);
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

int Gpio::togglePin(uint8_t pin)
{
  if (pin == -1)
  {
    debug(WARNING, "Gpio::togglePin: Pin %d is not initialized\n", pin);
    return -1;
  }
#if defined(__arm__)
  if (digitalRead(pin))
  {
    digitalWrite(pin, LOW);
  }
  else
  {
    digitalWrite(pin, HIGH);
  }
#endif
  return 0;
}

int Gpio::setPin(uint8_t pin)
{
  if (pin == -1)
  {
    debug(WARNING, "Gpio::setPin: Pin %d is not initialized\n", pin);
    return -1;
  }
#if defined(__arm__)
  digitalWrite(pin, HIGH);
#endif
return 0;
}

int Gpio::resetPin(uint8_t pin)
{
  if (pin == -1)
  {
    debug(WARNING, "Gpio::setPin: Pin %d is not initialized\n", pin);
    return -1;
  }
#if defined(__arm__)
  digitalWrite(pin, LOW);
#endif
  return 0;
}
