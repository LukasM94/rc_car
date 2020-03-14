#include <UController.h>
#include <string.h>
#include <Gpio.h>
#include <debug.h>
#include <Control.h>
#include <GamePad.h>
#include <GamePadInstance.h>
#include <unistd.h>
#include <com_config.h>
#include <config.h>
#include <Peripherial.h>

Control* Control::instance_ = 0;

//--------------------------------------------------------------------
Control::Control() : 
  u_controller_(0),
  i2c_running_(false),
  i2c_error_(0)
{
  debug(CTL_HANDLER, "ctor\n");
}

//--------------------------------------------------------------------
Control* Control::instance()
{
  if (instance_ == 0)
  {
    instance_ = new Control();
  }
  return instance_;
}

//--------------------------------------------------------------------
void Control::setController(UController* u_controller)
{
  debug(CTL_HANDLER, "setController: u_controller <%p>\n", u_controller);
  u_controller_ = u_controller;
}

//--------------------------------------------------------------------
Control::~Control()
{
  debug(CTL_HANDLER, "dtor\n");
}

//--------------------------------------------------------------------
void Control::gpioInit()
{
  debug(CTL_HANDLER, "gpioInit\n");
  Peripherial::instance()->initGpio();
  Peripherial::instance()->initLedGreen(RASPBERRY_LED_GREEN);
  Peripherial::instance()->initLedRed(RASPBERRY_LED_RED);
  Peripherial::instance()->initButton(RASPBERRY_BUTTON, &buttonCallback);
  Peripherial::instance()->initResetButton(RASPBERRY_RESET);
}

//--------------------------------------------------------------------
void Control::gpioDeInit()
{
  debug(CTL_HANDLER, "gpioDeInit\n");
  Peripherial::instance()->resetResetPin();
  Peripherial::instance()->turnRedLedOff();
  Peripherial::instance()->turnGreenLedOff();
}

//--------------------------------------------------------------------
void Control::i2cInit()
{
  debug(CTL_HANDLER, "i2cInit\n");
  u_controller_->initI2c();
}

//--------------------------------------------------------------------
void Control::buttonCallback()
{
  debug(CTL_HANDLER, "buttonCallback: Button pressed\n");
}

//--------------------------------------------------------------------
void* Control::gpioFunction(void* arg)
{
  Control* ch = (Control*)arg;

  debug(CTL_HANDLER, "gpioFunction: Start\n");
  while (1)
  {
    Peripherial::instance()->heartBeat();
  }
  debug(CTL_HANDLER, "gpioFunction: Exit\n");
  return 0;
}

static const uint8_t seconds = 3;
//--------------------------------------------------------------------
void Control::resetUController()
{
  debug(CTL_HANDLER, "i2cFunction: Reset u controller hard\n");
  Peripherial::instance()->resetResetPin();
  usleep(10000);
  Peripherial::instance()->setResetPin();
  debug(CTL_HANDLER, "i2cFunction: Wait %d seconds\n", seconds);
  sleep(seconds);
}

//--------------------------------------------------------------------
void* Control::i2cFunction(void* arg)
{
  Control* ch = (Control*)arg;

  bool prev_start_button = false;
  bool prev_select_button = false;

  enum I2C_MODE mode = NORMAL;
  
  int8_t speed;
  int8_t angle;
  
  uint8_t single_register;
  ch->resetUController();
  // debug(CTL_HANDLER, "i2cFunction: Reset u controller soft\n");
  // single_register = I2C_CONTROL_REGISTER_RESET;
  // if (ch->u_controller_->writeI2c(I2C_CONTROL_REGISTER, (const uint8_t*)&single_register, 1))
  // {
  //   debug(WARNING, "Control::i2cFunction: Could not write data via i2c\n");
  //   return 0;
  // }

  ch->i2c_running_ = true;
  ch->i2c_error_   = 0;
  debug(CTL_HANDLER, "i2cFunction: Start\n");
  while (ch->i2c_running_)
  {
    GamePad* game_pad = GamePadInstance::instance()->getGamePad();

    debug(CTL_HAND_D, "i2cFunction: Get data of game_pad\n");
    game_pad->lock();
    bool start_button  = game_pad->getButton(GamePad::BUTTON_START);
    bool select_button = game_pad->getButton(GamePad::BUTTON_SELECT);
    
    speed = game_pad->getLeftAxisY();
    angle = game_pad->getLeftAxisX();
    game_pad->unlock();

    debug(CTL_HAND_D, "i2cFunction: Check button action\n");

    if (start_button && !prev_start_button)
    {
      single_register = I2C_CONTROL_REGISTER_CHANGE_PWM_RUNNING;
      writeI2c(ch, I2C_CONTROL_REGISTER, (const uint8_t*)&single_register, 1); 
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
        writeI2c(ch, I2C_MOTOR, (const uint8_t*)&speed, 1); 
        writeI2c(ch, I2C_SERVO, (const uint8_t*)&angle, 1); 
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
        writeI2c(ch, I2C_CHANGE_OFFSET, (const uint8_t*)&single_register, 1);
        single_register = 0;
        if (angle > THRESHOLD_FOR_JOYSTICK)
        {
          single_register = I2C_SERVO_OFFSET_INCREMENT;
        } 
        else if (angle < (-1 * THRESHOLD_FOR_JOYSTICK))
        {
          single_register = I2C_SERVO_OFFSET_DECREMENT;
        }
        writeI2c(ch, I2C_CHANGE_OFFSET, (const uint8_t*)&single_register, 1);
        break;
      default:
        debug(WARNING, "Control::i2cFunction: Not knowing mode %d\n", mode);
    }

    usleep(I2C_SLEEP_TIME); 
  }
  debug(CTL_HANDLER, "i2cFunction: Exit\n");
  return 0;
}

void Control::writeI2c(Control* ch, uint8_t reg, const uint8_t* data, int length)
{
  if (ch->u_controller_->writeI2c(reg, data, length) == 0)
  {
    ch->i2c_error_ = 0;
  }
  else 
  {
    ch->i2c_error_++;
  }
  if (ch->i2c_error_ > I2C_ERROR_THRESHOLD)
  {
    debug(WARNING, "Control::writeI2c: %d errors on the i2c line\n", ch->i2c_error_.load());
    ch->i2c_running_ = false;
  }
}
