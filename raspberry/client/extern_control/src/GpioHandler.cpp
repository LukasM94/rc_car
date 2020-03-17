
#include <GpioHandler.h>
#include <Peripherial.h>
#include <unistd.h>
#include <com_config.h>
#include <config.h>
#include <Gpio.h>
#include <debug.h>
#include <ControlHandler.h>

GpioHandler::GpioHandler(ControlHandler* control_handler) :
  WorkingThread("GpioHandler"),
  control_handler_(control_handler)
{
  debug(GPIO_HANDLE, "ctor\n");
}

GpioHandler::~GpioHandler()
{
  debug(GPIO_HANDLE, "dtor\n");
}

void GpioHandler::init()
{
  debug(GPIO_HANDLE, "init\n");
  Peripherial::instance()->initGpio();
  Peripherial::instance()->initLedGreen(RASPBERRY_LED_GREEN);
  Peripherial::instance()->initLedRed(RASPBERRY_LED_RED);
  Peripherial::instance()->initButton(RASPBERRY_BUTTON, &buttonCallback);
  Peripherial::instance()->initResetButton(RASPBERRY_RESET);
}

void GpioHandler::deinit()
{
  debug(GPIO_HANDLE, "deinit\n");
  Peripherial::instance()->resetResetPin();
  Peripherial::instance()->turnRedLedOff();
  Peripherial::instance()->turnGreenLedOff();
}

void GpioHandler::run()
{
  debug(GPIO_HANDLE, "run: Start\n");
  while (running_)
  {
    Peripherial::instance()->heartBeat();
  }
  debug(GPIO_HANDLE, "run: Exit\n");
}

void GpioHandler::buttonCallback()
{
  debug(GPIO_HANDLE, "buttonCallback\n");
}
