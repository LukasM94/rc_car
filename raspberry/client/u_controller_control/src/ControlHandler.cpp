#include <UController.h>
#include <string.h>
#include <Gpio.h>
#include <debug.h>
#include <ControlHandler.h>
#include <GamePad.h>
#include <unistd.h>
#include <com_config.h>
#include <config.h>

//--------------------------------------------------------------------
ControlHandler::ControlHandler(UController* u_controller, GamePad* game_pad) : 
  u_controller_(u_controller),
  game_pad_(game_pad)
{
  debug(CTL_HANLER, "ctor: game_pad <%p>\n", game_pad_);
}

//--------------------------------------------------------------------
ControlHandler::~ControlHandler()
{
  debug(CTL_HANLER, "dtor\n");
}

//--------------------------------------------------------------------
void ControlHandler::gpioInit()
{
  debug(CTL_HANLER, "gpioInit\n");
  u_controller_->initGpio();
  u_controller_->initLed(RASPBERRY_LED);
  u_controller_->initButton(RASPBERRY_BUTTON, &buttonCallback);
}

//--------------------------------------------------------------------
void ControlHandler::i2cInit()
{
  debug(CTL_HANLER, "i2cInit\n");
  u_controller_->initI2c();
}

//--------------------------------------------------------------------
void ControlHandler::buttonCallback()
{
  debug(CTL_HANLER, "buttonCallback: Button pressed\n");
}

//--------------------------------------------------------------------
void* ControlHandler::gpioFunction(void* arg)
{
  ControlHandler* ch = (ControlHandler*)arg;

  debug(CTL_HANLER, "gpioFunction: Start\n");
  while (1)
  {
    ch->u_controller_->heartBeat();
  }
  debug(CTL_HANLER, "gpioFunction: Exit\n");
  return 0;
}

//--------------------------------------------------------------------
void* ControlHandler::i2cFunction(void* arg)
{
  ControlHandler* ch = (ControlHandler*)arg;

  debug(CTL_HANLER, "i2cFunction: Start\n");
  while (1)
  {
    int      reg   = I2C_MOTOR;
    uint16_t speed = 0x1234;
    ch->u_controller_->writeI2c(reg, (const uint8_t*)&speed, 2); 
    usleep(500000); 
  }
  debug(CTL_HANLER, "i2cFunction: Exit\n");
  return 0;
}
