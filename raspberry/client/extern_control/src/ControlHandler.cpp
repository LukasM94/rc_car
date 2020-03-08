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
  Peripherial::instance()->initLedGreen(RASPBERRY_LED_GREEN);
  Peripherial::instance()->initLedRed(RASPBERRY_LED_RED);
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

  bool prev_start_button = false;
  bool prev_select_button = false;

  enum I2C_MODE mode = NORMAL;
  
  int8_t speed;
  int8_t angle;
  
  uint8_t single_register;

  debug(CTL_HANDLER, "i2cFunction: Reset atmega and sleep for 1 second\n");
  single_register = I2C_CONTROL_REGISTER_RESET;
  ch->u_controller_->writeI2c(I2C_CONTROL_REGISTER, (const uint8_t*)&single_register, 1); 


  debug(CTL_HANDLER, "i2cFunction: Start\n");
  while (1)
  {
    GamePad* game_pad = GamePadInstance::instance()->getGamePad();

    debug(CTL_HAND_D, "i2cFunction: Get data of game_pad\n");
    game_pad->lock();
    bool start_button = game_pad->getButton(GamePad::BUTTON_START);
    bool select_button = game_pad->getButton(GamePad::BUTTON_SELECT);
    
    speed = game_pad->getLeftAxisY();
    angle = game_pad->getLeftAxisX();
    game_pad->unlock();

    debug(CTL_HAND_D, "i2cFunction: Check button action\n");

    if (start_button && !prev_start_button)
    {
      single_register = I2C_CONTROL_REGISTER_CHANGE_PWM_RUNNING;
      ch->u_controller_->writeI2c(I2C_CONTROL_REGISTER, (const uint8_t*)&single_register, 1); 
      Peripherial::instance()->toggleRedLed();
    }
    prev_start_button = start_button;

    if (select_button && !prev_select_button)
    {
      if (mode == NORMAL)
      {
        mode = OFFSET;
      }
      else if (mode == OFFSET)
      {
        mode = NORMAL;
      }
    }
    prev_select_button = select_button;

    debug(CTL_HAND_D, "i2cFunction: Current mode %d\n", mode);

    single_register = 0;
    switch (mode)
    {
      case NORMAL:
        ch->u_controller_->writeI2c(I2C_MOTOR, (const uint8_t*)&speed, 1); 
        ch->u_controller_->writeI2c(I2C_SERVO, (const uint8_t*)&angle, 1); 
        break;
      case OFFSET:
        if (speed > THRESHOLD_FOR_JOYSTICK)
        {
          single_register = I2C_MOTOR_OFFSET_INCREMENT;
        } 
        else if (speed < (-1 * THRESHOLD_FOR_JOYSTICK))
        {
          single_register = I2C_MOTOR_OFFSET_DECREMENT;
        }
        ch->u_controller_->writeI2c(I2C_CHANGE_OFFSET, (const uint8_t*)&single_register, 1);
        single_register = 0;
        if (angle > THRESHOLD_FOR_JOYSTICK)
        {
          single_register = I2C_SERVO_OFFSET_INCREMENT;
        } 
        else if (angle < (-1 * THRESHOLD_FOR_JOYSTICK))
        {
          single_register = I2C_SERVO_OFFSET_DECREMENT;
        }
        ch->u_controller_->writeI2c(I2C_CHANGE_OFFSET, (const uint8_t*)&single_register, 1);
        break;
      default:
        debug(WARNING, "i2cFunction: Not knowing mode %d\n", mode);
    }

    usleep(I2C_SLEEP_TIME); 
  }
  debug(CTL_HANDLER, "i2cFunction: Exit\n");
  return 0;
}
