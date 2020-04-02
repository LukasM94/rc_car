#include <I2cRegisterData.h>
#include <debug.h>
#include <com_config.h>
#include <GamePad.h>
#include <I2cHandler.h>
#include <I2c.h>
#include <unistd.h>

I2cRegisterData::I2cRegisterData(int8_t motor_offset_, int8_t servo_offset_) :
  start_button_prev_(false),
  select_button_prev_(false),
  y_axis_prev_(0),
  x_axis_prev_(0),
  start_button_(false),
  select_button_(false),
  y_axis_(0),
  x_axis_(0),
  motor_(0),
  servo_(0),
  motor_offset_(motor_offset_),
  servo_offset_(servo_offset_),
  status_register_(0),
  control_register_(0),
  mode_(NORMAL)
{
  debug(I2C_REG_D, "ctor: motor_offset_ <%d>, servo_offset_ <%d>\n", motor_offset_, servo_offset_);
}

I2cRegisterData::~I2cRegisterData()
{
  debug(I2C_REG_D, "dtor\n");
}

void I2cRegisterData::refreshData(GamePad* game_pad)
{
  start_button_prev_  = start_button_;
  select_button_prev_ = select_button_;

  y_axis_prev_ = y_axis_;
  x_axis_prev_ = x_axis_;

  start_button_  = game_pad->getButton(GamePad::BUTTON_START);
  select_button_ = game_pad->getButton(GamePad::BUTTON_SELECT);

  y_axis_ = game_pad->getLeftAxisY();
  x_axis_ = game_pad->getLeftAxisX();
}

void I2cRegisterData::nextState()
{
  if (start_button_prev_ != start_button_)
  {
    if (start_button_)
    {
      debug(I2C_REG_D, "nextState: StartButton is %s\n", start_button_ ? "pressed" : "released");
      control_register_ ^= I2C_CONTROL_REGISTER_RUNNING;
    }
  }

  if (select_button_prev_ != select_button_)
  {
    if (select_button_)
    {
      debug(I2C_REG_D, "nextState: SelectButton is %s\n", select_button_ ? "pressed" : "released");
      if (mode_ == NORMAL)
      {
        mode_ = OFFSET;
      }
      else if (mode_ == OFFSET)
      {
        mode_ = NORMAL;
      }
    }
  }

  if (y_axis_prev_ != y_axis_)
  {
    motor_ = y_axis_;
    if (mode_ == NORMAL)
    {
      debug(I2C_REG_D, "nextState: Motor is %d\n", motor_);
    }
    else if (mode_ == OFFSET)
    {
      if (motor_ > THRESHOLD_FOR_JOYSTICK && motor_offset_ < MAX_OFFSET)
      {
        motor_offset_++;
      }
      else if (motor_ < (-1 * THRESHOLD_FOR_JOYSTICK) && motor_offset_ > (-1 * MAX_OFFSET))
      {
        motor_offset_--;
      }
      debug(I2C_REG_D, "nextState: MotorOffset is %d\n", motor_offset_);
      usleep(I2C_SLEEP_TIME);
    }
  }

  if (x_axis_prev_ != x_axis_)
  {
    servo_ = x_axis_;
    if (mode_ == NORMAL)
    {
      debug(I2C_REG_D, "nextState: Servo is %d\n", servo_);
    }
    else if (mode_ == OFFSET)
    {
      if (servo_ > THRESHOLD_FOR_JOYSTICK && servo_offset_ < MAX_OFFSET)
      {
        servo_offset_++;
      }
      else if (servo_ < (-1 * THRESHOLD_FOR_JOYSTICK) && servo_offset_ > (-1 * MAX_OFFSET))
      {
        servo_offset_--;
      }
      debug(I2C_REG_D, "nextState: ServoOffset is %d\n", servo_offset_);
      usleep(I2C_SLEEP_TIME);
    }
  }
}
