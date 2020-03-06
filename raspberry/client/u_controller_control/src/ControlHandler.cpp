#include <UController.h>
#include <string.h>
#include <Gpio.h>
#include <debug.h>
#include <ControlHandler.h>
#include <GamePad.h>
#include <GamePadInstance.h>
#include <unistd.h>
#include <com_config.h>
#include <config.h>

//--------------------------------------------------------------------
ControlHandler::ControlHandler(UController* u_controller) : 
  u_controller_(u_controller)
{
  debug(CTL_HANDLER, "ctor: u_controller <%p>\n", u_controller);
}

//--------------------------------------------------------------------
ControlHandler::~ControlHandler()
{
  debug(CTL_HANDLER, "dtor\n");
}

//--------------------------------------------------------------------
void ControlHandler::gpioInit()
{
  debug(CTL_HANDLER, "gpioInit\n");
  u_controller_->initGpio();
  u_controller_->initLed(RASPBERRY_LED);
  u_controller_->initButton(RASPBERRY_BUTTON, &buttonCallback);
}

//--------------------------------------------------------------------
void ControlHandler::i2cInit()
{
  debug(CTL_HANDLER, "i2cInit\n");
  u_controller_->initI2c();
}

//--------------------------------------------------------------------
void ControlHandler::buttonCallback()
{
  debug(CTL_HANDLER, "buttonCallback: Button pressed\n");
}

//--------------------------------------------------------------------
void* ControlHandler::gpioFunction(void* arg)
{
  ControlHandler* ch = (ControlHandler*)arg;

  debug(CTL_HANDLER, "gpioFunction: Start\n");
  while (1)
  {
    ch->u_controller_->heartBeat();
  }
  debug(CTL_HANDLER, "gpioFunction: Exit\n");
  return 0;
}

//--------------------------------------------------------------------
void* ControlHandler::i2cFunction(void* arg)
{
  ControlHandler* ch = (ControlHandler*)arg;

  debug(CTL_HANDLER, "i2cFunction: Start\n");
  while (1)
  {
    GamePad* game_pad = GamePadInstance::instance()->getGamePad();

    game_pad->lock();
    int8_t speed = game_pad->getLeftAxisY();
    int8_t angle = game_pad->getLeftAxisX();
    game_pad->unlock();

    ch->u_controller_->writeI2c(I2C_MOTOR, (const uint8_t*)&speed, 1); 
    ch->u_controller_->writeI2c(I2C_SERVO, (const uint8_t*)&angle, 1); 

    usleep(500000); 
  }
  debug(CTL_HANDLER, "i2cFunction: Exit\n");
  return 0;
}
