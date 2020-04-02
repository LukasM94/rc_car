
#include <I2cHandler.h>
#include <Peripherial.h>
#include <I2c.h>
#include <Atmega.h>
#include <debug.h>
#include <unistd.h>
#include <GamePad.h>
#include <GamePadInstance.h>
#include <com_config.h>
#include <ControlHandler.h>

I2cHandler::I2cHandler(ControlHandler* control_handler) :
  WorkingThread("I2cHandler"),
  control_handler_(control_handler)
{
  debug(I2C_HANDLER, "ctor\n");
}

I2cHandler::~I2cHandler()
{
  debug(I2C_HANDLER, "dtor\n");
}
