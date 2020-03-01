
#include <gpio.h>
#include <wiringPi.h>
#include <config.h>
#include <debug.h>
#include <unistd.h>

Gpio* Gpio::instance_ = 0;

Gpio::Gpio() : led_pin_(0), button_pin_(1)
{
  wiringPiSetupGpio();
}

Gpio::~Gpio()
{

}

void Gpio::initLed()
{
  if (gpioTestAndSet(led_pin_))
  {
    debug(ERROR, "Gpio::init: Pin %d is already taken\n", led_pin_);
    return;
  }
  pinMode(led_pin_, OUTPUT);
  debug(GPIO, "Gpio::init: Pin %d is OUTPUT\n", led_pin_);
}

void Gpio::initButton(void (*f_ptr)())
{
  if (gpioTestAndSet(button_pin_))
  {
    debug(ERROR, "Gpio::init: Pin %d is already taken\n", button_pin_);
    return;
  }
  pinMode(button_pin_, INPUT);
  wiringPiISR(button_pin_, INT_EDGE_FALLING, f_ptr);
  debug(GPIO, "Gpio::init: Pin %d is INPUT\n", led_pin_);
}

Gpio* Gpio::instance()
{
  if (instance_ == 0)
  {
    instance_ = new Gpio();
  }
  return instance_;
}

void Gpio::heartBeat()
{
  digitalWrite(led_pin_, HIGH);
  sleep(1);
  digitalWrite(led_pin_, LOW);
  sleep(1);
}