
#include <Peripherial.h>
#include <debug.h>
#include <Gpio.h>

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

void Peripherial::initLed(uint8_t led_pin)
{
  gpio_->initLed(led_pin);
}

void Peripherial::initButton(uint8_t button_pin, void (*f_ptr)())
{
  gpio_->initButton(button_pin, f_ptr);
}

void Peripherial::heartBeat()
{
  gpio_->heartBeat();
}
