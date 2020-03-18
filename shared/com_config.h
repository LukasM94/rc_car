
#ifndef I2C_PROTOCOL
#define I2C_PROTOCOL

#define I2C_ADDRESS 0x05

#define I2C_MOTOR 0x00
#define I2C_MOTOR_SIZE 1

#define I2C_SERVO 0x04
#define I2C_SERVO_SIZE 1

#define I2C_CONTROL_REGISTER 0x20
#define I2C_CONTROL_REGISTER_CHANGE_PWM_RUNNING 0x01
#define I2C_CONTROL_REGISTER_RESET 0x02

#define I2C_CHANGE_OFFSET 0x21
#define I2C_MOTOR_OFFSET_INCREMENT 0x01
#define I2C_MOTOR_OFFSET_DECREMENT 0x02
#define I2C_SERVO_OFFSET_INCREMENT 0x04
#define I2C_SERVO_OFFSET_DECREMENT 0x08

#define I2C_SLEEP_TIME  50000 //us
#define I2C_DEAD_TIME   500 //ms

#define ATMEGA_RECOVER_AFTER_RESET 3 //s

struct RegisterEntry
{
  unsigned char register_number_;
  const char name_[7];
}__attribute__((packed));

static struct RegisterEntry registers[] = 
{
  {I2C_MOTOR, "Motor"},
  {I2C_SERVO, "Servo"},
  {I2C_CONTROL_REGISTER, "Ctl"},
  {I2C_CHANGE_OFFSET, "Offset"},
};

#define COUNT_REGISTER 4

static const char* getNameOfRegister(unsigned char register_number)
{
  const char* result = 0;
  for (int i = 0; i < COUNT_REGISTER; ++i)
  {
    if (registers[i].register_number_ == register_number)
    {
      result = registers[i].name_;
    }
  }
  return result;
}

#endif