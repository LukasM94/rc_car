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
#include <Peripherial.h>

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
  Peripherial::instance()->initGpio();
  Peripherial::instance()->initLed(RASPBERRY_LED);
  Peripherial::instance()->initButton(RASPBERRY_BUTTON, &buttonCallback);
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
    Peripherial::instance()->heartBeat();
  }
  debug(CTL_HANDLER, "gpioFunction: Exit\n");
  return 0;
}

//--------------------------------------------------------------------
void* ControlHandler::i2cFunction(void* arg)
{
  ControlHandler* ch = (ControlHandler*)arg;

  bool old_start_button = false;

  enum I2C_MODE mode = NORMAL;

  debug(CTL_HANDLER, "i2cFunction: Start\n");
  while (1)
  {
    GamePad* game_pad = GamePadInstance::instance()->getGamePad();

    debug(CTL_HANDLER, "i2cFunction: Get data of game_pad\n");
    game_pad->lock();
    bool start_button = game_pad->getButton(GamePad::BUTTON_START);
    
    int8_t speed = game_pad->getLeftAxisY();
    int8_t angle = game_pad->getLeftAxisX();
    game_pad->unlock();

    debug(CTL_HANDLER, "i2cFunction: Check button action\n");
    if (start_button && !old_start_button)
    {
      uint8_t change_register = I2C_CONTROL_REGISTER_CHANGE_PWM_RUNNING;
      ch->u_controller_->writeI2c(I2C_CONTROL_REGISTER, (const uint8_t*)&change_register, 1); 
    }
    old_start_button = start_button;

    debug(CTL_HANDLER, "i2cFunction: Current mode %d\n", mode);
    switch (mode)
    {
      case NORMAL:
        ch->u_controller_->writeI2c(I2C_MOTOR, (const uint8_t*)&speed, 1); 
        ch->u_controller_->writeI2c(I2C_SERVO, (const uint8_t*)&angle, 1); 
        break;
      case OFFSET:
        
      default:
        debug(WARNING, "i2cFunction: Not knowing mode %d\n", mode);
    }

    usleep(I2C_SLEEP_TIME); 
  }
  debug(CTL_HANDLER, "i2cFunction: Exit\n");
  return 0;
}
