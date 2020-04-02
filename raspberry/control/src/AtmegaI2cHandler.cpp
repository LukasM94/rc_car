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
  controller_.u_controller_ = new Atmega();
  debug(A_I2C_HANDL, "ctor: %p\n", control_handler);
}

AtmegaI2cHandler::~AtmegaI2cHandler()
{
  delete controller_.u_controller_;
  debug(A_I2C_HANDL, "dtor\n");
}

void AtmegaI2cHandler::init()
{
  debug(A_I2C_HANDL, "init\n");
  UController* u_controller = controller_.u_controller_;
  u_controller->initI2c();
}

void AtmegaI2cHandler::deinit()
{
  debug(A_I2C_HANDL, "deinit\n");
}

void AtmegaI2cHandler::run()
{
  debug(A_I2C_HANDL, "run: Start\n");

  GamePad* game_pad = GamePadInstance::instance()->getGamePad();

  enum I2C_MODE mode = NORMAL;
  
  int8_t motor = 0;
  int8_t servo = 0;
  int8_t motor_offset = 0;
  int8_t servo_offset = 0;
  uint8_t status_register = 0;
  uint8_t control_register = 0;

  int8_t y_axis = 0;
  int8_t x_axis = 0;
  int8_t y_axis_prev = 0;
  int8_t x_axis_prev = 0;
  
  bool start_button = false;
  bool select_button = false;
  bool start_button_prev = false;
  bool select_button_prev = false;
  
  uint8_t single_register;
  debug(A_I2C_HANDL, "run: Reset u controller\n");
  Peripherial::instance()->resetUcontroller();

  sleep(ATMEGA_RECOVER_AFTER_RESET);

  i2c_error_ = 0;
  running_   = 1;

  bool game_pad_connected      = 1;
  bool game_pad_connected_prev = 1;

  debug(A_I2C_HANDL, "run: Start with communcation\n");
  while (running_)
  {
    game_pad->lock();
    game_pad->waitTillNewData();

    game_pad_connected_prev = game_pad_connected;
    game_pad_connected = game_pad->isConnected();

    if (!game_pad_connected)
    {
      debug(WARNING, "I2cHandler::run: GamePad not connected\n",
        I2C_HANDLER_NOT_CONNECTED_TRY_AGAIN_SLEEP_TIME);
      Peripherial::instance()->resetResetPin();
      game_pad->unlock();
      sleep(I2C_HANDLER_NOT_CONNECTED_TRY_AGAIN_SLEEP_TIME);
      continue;
    }

    start_button_prev  = start_button;
    select_button_prev = select_button;

    start_button  = game_pad->getButton(GamePad::BUTTON_START);
    select_button = game_pad->getButton(GamePad::BUTTON_SELECT);

    y_axis_prev = y_axis;
    x_axis_prev = x_axis;

    y_axis = game_pad->getLeftAxisY();
    x_axis = game_pad->getLeftAxisX();

    game_pad->unlock();

    if (start_button_prev != start_button)
    {
      debug(I2C_HANDL_D, "run: StartButton is %s\n", start_button ? "start" : "stop");
      control_register ^= I2C_CONTROL_REGISTER_RUNNING;
      writeI2c(I2C_CONTROL_REGISTER, (const uint8_t*)&control_register, 1);
    }

    if (select_button_prev != select_button)
    {
      debug(I2C_HANDL_D, "run: SelectButton is %s\n", select_button ? "start" : "stop");
      if (select_button)
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
    }

    if (y_axis_prev != y_axis)
    {
      motor = y_axis;
      if (mode == NORMAL)
      {
        debug(I2C_HANDL_D, "run: Motor is %d\n", motor);
        writeI2c(I2C_MOTOR0_REGISTER, (const uint8_t*)&motor, 1);
      }
      else if (mode == OFFSET)
      {
        if (motor > THRESHOLD_FOR_JOYSTICK && motor_offset < MAX_OFFSET)
        {
          motor_offset++;
        }
        else if (motor < (-1 * THRESHOLD_FOR_JOYSTICK) && motor_offset > (-1 * MAX_OFFSET))
        {
          motor_offset--;
        }
        debug(I2C_HANDL_D, "run: MotorOffset is %d\n", motor_offset);
        writeI2c(I2C_MOTOR0_OFFSET_REGISTER, (const uint8_t*)&motor_offset, 1);
        usleep(I2C_SLEEP_TIME);
      }
    }

    if (x_axis_prev != x_axis)
    {
      servo = x_axis;
      if (mode == NORMAL)
      {
        debug(I2C_HANDL_D, "run: Servo is %d\n", servo);
        writeI2c(I2C_MOTOR1_REGISTER, (const uint8_t*)&servo, 1);
      }
      else if (mode == OFFSET)
      {
        if (servo > THRESHOLD_FOR_JOYSTICK && servo_offset < MAX_OFFSET)
        {
          servo_offset++;
        }
        else if (servo < (-1 * THRESHOLD_FOR_JOYSTICK) && servo_offset > (-1 * MAX_OFFSET))
        {
          servo_offset--;
        }
        debug(I2C_HANDL_D, "run: ServoOffset is %d\n", servo_offset);
        writeI2c(I2C_MOTOR1_OFFSET_REGISTER, (const uint8_t*)&servo_offset, 1);
        usleep(I2C_SLEEP_TIME);
      }
    }
  }
  debug(A_I2C_HANDL, "run: Exit\n");
}

void AtmegaI2cHandler::writeI2c(uint8_t reg, const uint8_t* data, int length)
{
  debug(I2C_HANDL_D, "writeI2c: reg <%d>, data <%p>, length <%d>\n", reg, data, length);
  UController* u_controller = controller_.u_controller_;
  if (u_controller->writeI2c(reg, data, length) == 0)
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