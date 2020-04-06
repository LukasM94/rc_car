
#ifndef I2C_PROTOCOL
#define I2C_PROTOCOL

#define I2C_ADDRESS 0x05

#define I2C_CONTROL_REGISTER 0x00
// please do not use the software reset
#define I2C_CONTROL_REGISTER_RESET   0x01
#define I2C_CONTROL_REGISTER_STOP    0x02
#define I2C_CONTROL_REGISTER_RUNNING 0x04

#define I2C_STATUS_REGISTER 0x01
#define I2C_STATUS_REGISTER_MOTOR0_RUNNING 0x01
#define I2C_STATUS_REGISTER_MOTOR1_RUNNING 0x02
#define I2C_STATUS_REGISTER_MOTOR2_RUNNING 0x04

#define I2C_MOTOR0_REGISTER 0x10
#define I2C_MOTOR1_REGISTER 0x11
#define I2C_MOTOR2_REGISTER 0x12

#define I2C_MOTOR0_OFFSET_REGISTER 0x20
#define I2C_MOTOR1_OFFSET_REGISTER 0x21
#define I2C_MOTOR2_OFFSET_REGISTER 0x22

#define I2C_SLEEP_TIME  50000 //us
#define I2C_DEAD_TIME   500 //ms

#define ATMEGA_RECOVER_AFTER_RESET 3 //s

#define NOT_SAVED 0
#define SAVED     1

struct RegisterEntry
{
  unsigned char register_number_;
  const char*   name_;
  int           should_be_saved_;
}__attribute__((packed));


static const char I2C_CONTROL_REGISTER_NAME[] = "ControlRegister";
static const char I2C_STATUS_REGISTER_NAME[] = "StatusRegister";
static const char I2C_MOTOR0_REGISTER_NAME[] = "Motor";
static const char I2C_MOTOR1_REGISTER_NAME[] = "Servo";
static const char I2C_MOTOR2_REGISTER_NAME[] = "MotorNotUsed";
static const char I2C_MOTOR0_OFFSET_REGISTER_NAME[] = "MotorOffset";
static const char I2C_MOTOR1_OFFSET_REGISTER_NAME[] = "ServoOffset";
static const char I2C_MOTOR2_OFFSET_REGISTER_NAME[] = "MotorOffsetNotUsed";

static struct RegisterEntry registers[] = 
{
  {I2C_CONTROL_REGISTER, I2C_CONTROL_REGISTER_NAME, NOT_SAVED},
  {I2C_STATUS_REGISTER, I2C_STATUS_REGISTER_NAME, NOT_SAVED},
  {I2C_MOTOR0_REGISTER, I2C_MOTOR0_REGISTER_NAME, NOT_SAVED},
  {I2C_MOTOR1_REGISTER, I2C_MOTOR1_REGISTER_NAME, NOT_SAVED},
  {I2C_MOTOR2_REGISTER, I2C_MOTOR2_REGISTER_NAME, NOT_SAVED},
  {I2C_MOTOR0_OFFSET_REGISTER, I2C_MOTOR0_OFFSET_REGISTER_NAME, SAVED},
  {I2C_MOTOR1_OFFSET_REGISTER, I2C_MOTOR1_OFFSET_REGISTER_NAME, SAVED},
  {I2C_MOTOR2_OFFSET_REGISTER, I2C_MOTOR2_OFFSET_REGISTER_NAME, SAVED},
};

#define COUNT_REGISTER 8

__attribute__((unused))const char* getNameOfRegister(unsigned char register_number)
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

__attribute__((unused))int shouldBeSaved(unsigned char register_number)
{
  int should_ba_saved = 0;
  for (int i = 0; i < COUNT_REGISTER; ++i)
  {
    if (registers[i].register_number_ == register_number)
    {
      should_ba_saved = registers[i].should_be_saved_;
    }
  }
  return should_ba_saved;
}

#endif