
#include <I2cHandler.h>
#include <Peripherial.h>
#include <I2c.h>
#include <UController.h>
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

void I2cHandler::init()
{
  debug(I2C_HANDLER, "init\n");
  control_handler_->u_controller_->initI2c();
}

void I2cHandler::deinit()
{
  debug(I2C_HANDLER, "deinit\n");

}

void I2cHandler::run()
{
  debug(I2C_HANDLER, "run: Start\n");
  bool prev_start_button = false;
  bool prev_select_button = false;

  GamePad* game_pad = GamePadInstance::instance()->getGamePad();

  enum I2C_MODE mode = NORMAL;
  
  int8_t speed;
  int8_t angle;
  
  uint8_t single_register;
  debug(I2C_HANDLER, "run: Reset u controller\n");
  Peripherial::instance()->resetUcontroller();

  sleep(3);

  game_pad_error_ = 0;

  i2c_error_ = 0;
  running_   = 1;

  debug(I2C_HANDLER, "run: Start with communcation\n");
  while (running_)
  {
    debug(I2C_HANDL_D, "run: Get data of game_pad\n");

    game_pad->lock();
    if (game_pad->isNew() == false)
    {
      game_pad_error_++;
      if (game_pad_error_ > GAME_PAD_ERROR_THRESHOLD)
      {
        debug(WARNING, "I2cHandler::run: Gamepad has not been refreshed in some time. Maybe a connection problem?\n");
        running_ = false;
        game_pad->unlock();
        continue;
      }
    }
    else
    {
      game_pad_error_ = 0;
    }

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
        break;
      default:
        debug(WARNING, "I2cHandler::run: Not knowing mode %d\n", mode);
    }
    usleep(I2C_SLEEP_TIME);
  }

  debug(I2C_HANDLER, "run: Exit\n");
}

void I2cHandler::writeI2c(uint8_t reg, const uint8_t* data, int length)
{
  debug(I2C_HANDL_D, "writeI2c: reg <%d>, data <%p>, length <%d>\n", reg, data, length);
  if (control_handler_->u_controller_->writeI2c(reg, data, length) == 0)
  {
    i2c_error_ = 0;
  }
  else 
  {
    i2c_error_++;
  }
  if (i2c_error_ > I2C_ERROR_THRESHOLD)
  {
    debug(WARNING, "I2cHandler::writeI2c: %d errors on the i2c line\n", i2c_error_.load());
    running_ = false;
  }
}
