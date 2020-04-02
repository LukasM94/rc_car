#include <AtmegaI2cHandler.h>
#include <debug.h>
#include <Atmega.h>
#include <com_config.h>
#include <I2cHandler.h>
#include <Peripherial.h>
#include <I2c.h>
#include <Atmega.h>
#include <debug.h>
#include <unistd.h>
#include <GamePad.h>
#include <GamePadInstance.h>
#include <ControlHandler.h>

AtmegaI2cHandler::AtmegaI2cHandler(ControlHandler* control_handler) :
  I2cHandler(control_handler)
{
  debug(A_I2C_HANDL, "ctor: %p\n", control_handler);
}

AtmegaI2cHandler::~AtmegaI2cHandler()
{
  debug(A_I2C_HANDL, "dtor\n");
}

void AtmegaI2cHandler::run()
{
  debug(A_I2C_HANDL, "run: Start\n");
  bool prev_start_button = false;
  bool prev_select_button = false;

  GamePad* game_pad = GamePadInstance::instance()->getGamePad();

  enum I2C_MODE mode = NORMAL;
  
  int8_t speed;
  int8_t angle;
  
  uint8_t single_register;
  debug(A_I2C_HANDL, "run: Reset u controller\n");
  Peripherial::instance()->resetUcontroller();

  sleep(ATMEGA_RECOVER_AFTER_RESET);

  i2c_error_ = 0;
  running_   = 1;

  bool prev_connected = 1;

  debug(A_I2C_HANDL, "run: Start with communcation\n");
  while (running_)
  {
    debug(A_I2C_HANDL, "run: Get data of game_pad\n");

    game_pad->lock();

    game_pad->waitTillNewData();

    if (!game_pad->isConnected())
    {
      debug(WARNING, "I2cHandler::run: GamePad not connected\n",
        I2C_HANDLER_NOT_CONNECTED_TRY_AGAIN_SLEEP_TIME);
      Peripherial::instance()->resetResetPin();
      prev_connected = game_pad->isConnected();
      game_pad->unlock();
      sleep(I2C_HANDLER_NOT_CONNECTED_TRY_AGAIN_SLEEP_TIME);
      continue;
    } 
    else if (!prev_connected)
    {
      debug(A_I2C_HANDL, "run: Set u controller\n");
      Peripherial::instance()->setResetPin();
      sleep(ATMEGA_RECOVER_AFTER_RESET);
      debug(I2C_HANDLER, "run: Recovered from reset\n");
    }

    prev_connected = game_pad->isConnected();

    bool start_button  = game_pad->getButton(GamePad::BUTTON_START);
    bool select_button = game_pad->getButton(GamePad::BUTTON_SELECT);
    
    speed = game_pad->getLeftAxisY();
    angle = game_pad->getLeftAxisX();
    game_pad->unlock();

    debug(I2C_HANDL_D, "run: Check button action\n");
    if (start_button && !prev_start_button)
    {
      single_register = I2C_CONTROL_REGISTER_CHANGE_PWM_RUNNING;
      writeI2c(I2C_CONTROL_REGISTER, (const uint8_t*)&single_register, 1); 
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

    debug(I2C_HANDL_D, "run: Current mode %d\n", mode);

    single_register = 0;
    switch (mode)
    {
      case NORMAL:
        writeI2c(I2C_MOTOR, (const uint8_t*)&speed, 1); 
        writeI2c(I2C_SERVO, (const uint8_t*)&angle, 1); 
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
        writeI2c(I2C_CHANGE_OFFSET, (const uint8_t*)&single_register, 1);
        single_register = 0;
        if (angle > THRESHOLD_FOR_JOYSTICK)
        {
          single_register = I2C_SERVO_OFFSET_INCREMENT;
        } 
        else if (angle < (-1 * THRESHOLD_FOR_JOYSTICK))
        {
          single_register = I2C_SERVO_OFFSET_DECREMENT;
        }
        writeI2c(I2C_CHANGE_OFFSET, (const uint8_t*)&single_register, 1);
        usleep(I2C_SLEEP_TIME);
        break;
      default:
        debug(WARNING, "I2cHandler::run: Not knowing mode %d\n", mode);
    }
    // usleep(I2C_SLEEP_TIME);
  }

  debug(A_I2C_HANDL, "run: Exit\n");
}