
#ifndef I2C_PROTOCOL
#define I2C_PROTOCOL

#define I2C_ADDRESS 0x05

#define I2C_MOTOR 0x00
#define I2C_MOTOR_SIZE 1

#define I2C_SERVO 0x04
#define I2C_SERVO_SIZE 1

#define I2C_CONTROL_REGISTER 0x20
#define I2C_CONTROL_REGISTER_CHANGE_PWM_RUNNING 0x01

#define I2C_MOTOR_OFFSET_INCREMENT 0x21
#define I2C_MOTOR_OFFSET_DECREMENT 0x22
#define I2C_SERVO_OFFSET_INCREMENT 0x23
#define I2C_SERVO_OFFSET_DECREMENT 0x24

#define I2C_SLEEP_TIME  50000 //us
#define I2C_DEAD_TIME   500 //ms

struct RegisterEntry
{
  unsigned char register_number_;
  const char name_[7];
}__attribute__((packed));

static struct RegisterEntry registers[] = 
{
  {I2C_MOTOR, "Motor"},
  {I2C_SERVO, "Servo"},
};

static const char* getNameOfRegister(unsigned char register_number)
{
  const char* result = 0;
  for (int i = 0; i < 2; ++i)
  {
    if (registers[i].register_number_ == register_number)
    {
      result = registers[i].name_;
    }
  }
  return result;
}

#endif