
#include <Peripherial.h>
#include <debug.h>
#include <Gpio.h>
#include <unistd.h>

Peripherial* Peripherial::instance_ = 0;

Peripherial::Peripherial() :
  gpio_(0)
{

}

Peripherial::~Peripherial()
{

}

Peripherial* Peripherial::instance()
{
  if (instance_ == 0)
  {
    instance_ = new Peripherial();
  }
  return instance_;
}

int Peripherial::initGpio()
{
  debug(UCONTROLLER, "initGpio\n");
  if (gpio_ != 0)
  {
    debug(UCONTROLLER, "initGpio: return -1\n");
    return -1;
  }
  gpio_ = new Gpio("Peripherial");
  return 0;
}

int Peripherial::initLedGreen(uint8_t led_pin)
{
  return (gpio_->initLedGreen(led_pin) || 
          gpio_->offGreenLed());
}

int Peripherial::initLedRed(uint8_t led_pin)
{
  return (gpio_->initLedRed(led_pin) ||
          gpio_->offRedLed());
}

int Peripherial::initResetButton(uint8_t reset_pin)
{
  return (gpio_->initReset(reset_pin) || 
          gpio_->setResetPin());
}

int Peripherial::initButton(uint8_t button_pin, void (*f_ptr)())
{
  return gpio_->initButton(button_pin, f_ptr);
}

void Peripherial::resetResetPin()
{
  gpio_->resetResetPin();
}

void Peripherial::setResetPin()
{
  gpio_->setResetPin();
}

void Peripherial::heartBeat()
{
  gpio_->onGreenLed();
  sleep(1);
  gpio_->offGreenLed();
  sleep(1);
}

void Peripherial::turnGreenLedOff()
{
  gpio_->offGreenLed();
}

void Peripherial::turnRedLedOn()
{
  gpio_->onRedLed();
}

void Peripherial::turnRedLedOff()
{
  gpio_->offRedLed();
}

void Peripherial::toggleRedLed()
{
  gpio_->toggleRedLed();
}
