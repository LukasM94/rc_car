
#include <Gpio.h>
#include <wiringPi.h>
#include <config.h>
#include <debug.h>
#include <unistd.h>


Gpio::Gpio(std::string name) : 
  name_(name),
  led_pin_(-1), 
  button_pin_(-1)
{
  debug(GPIO, "ctor\n");
  wiringPiSetupGpio();
}

Gpio::~Gpio()
{
  debug(GPIO, "dtor\n");
}

void Gpio::initLed(uint8_t led_pin)
{
  led_pin_ = led_pin;
  if (gpioTestAndSet(led_pin_))
  {
    debug(ERROR, "Gpio::init: Pin %d is already taken\n", led_pin_);
    return;
  }
  pinMode(led_pin_, OUTPUT);
  debug(GPIO, "initLed: Pin %d is OUTPUT\n", led_pin_);
}

void Gpio::initButton(uint8_t button_pin, void (*f_ptr)())
{
  button_pin_ = button_pin;
  if (gpioTestAndSet(button_pin_))
  {
    debug(ERROR, "Gpio::init: Pin %d is already taken\n", button_pin_);
    return;
  }
  pinMode(button_pin_, INPUT);
  wiringPiISR(button_pin_, INT_EDGE_FALLING, f_ptr);
  debug(GPIO, "initButton: Pin %d is INPUT\n", led_pin_);
}

void Gpio::heartBeat()
{
  digitalWrite(led_pin_, HIGH);
  sleep(1);
  digitalWrite(led_pin_, LOW);
  sleep(1);
}