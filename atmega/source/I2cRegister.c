
#include <com_config.h>
#include <I2cRegister.h>
#include <Eeprom.h>
#include <Printf.h>
#include <I2cSlave.h>
#include <config.h>

#define BUFFER_SIZE 8

volatile static uint8_t buffer[BUFFER_SIZE];
volatile static uint8_t recv_reg_number;
volatile static uint8_t recv_flag;
volatile static uint8_t swapped_recv_flag;

static void recv(uint8_t* data, uint8_t length, uint8_t reg_number);
static void req();

struct I2cRegister* I2cRegister_ctor(struct I2cRegister* this)
{
  I2cRegister_init(this);
  this->readFromEEPROM(this);

  i2cSlaveInit(I2C_ADDRESS);
  i2cSlaveSetCallbacks(&recv, &req);

  return this;
}

struct I2cRegister* I2cRegister_dtor(struct I2cRegister* this)
{
  this->writeToEEPROM(this);
  return this;
}

void I2cRegister_run(struct I2cRegister* this)
{
  cli();
  swapped_recv_flag = recv_flag;
  recv_flag = 0;
  sei();
  if (swapped_recv_flag)
  {
    const char* register_name = this->getNameOfRegister(recv_reg_number);
    uint8_t     single_data   = buffer[0];

    this->write(this, single_data, recv_reg_number);

    Printf_print("%s\n", register_name);
    Printf_print("data <%d>\n", single_data);
  }
}

void I2cRegister_writeToEEPROM(struct I2cRegister* this)
{
  for (int i = 0; i < REGISTER_SIZE; ++i)
  {
    if (shouldBeSaved(i))
    {
      writeEEPROM(this->register_[i], i);
    }
  }
}

void I2cRegister_readFromEEPROM(struct I2cRegister* this)
{
  for (int i = 0; i < REGISTER_SIZE; ++i)
  {
    if (shouldBeSaved(i))
    {
      this->register_[i] = readEEPROM(i);
    }
  }
}

void I2cRegister_write(struct I2cRegister* this, uint8_t reg, uint8_t reg_number)
{
  if (reg_number >= REGISTER_SIZE)
  {
    return;
  }
  if (shouldBeSaved(reg_number))
  {
    writeEEPROM(reg, reg_number);
  }
  this->register_[reg_number] = reg;
}

uint8_t I2cRegister_read(struct I2cRegister* this, uint8_t reg_number)
{
  if (reg_number >= REGISTER_SIZE)
  {
    return -1;
  }
  return this->register_[reg_number];
}

uint8_t I2cRegister_readControlRegister(struct I2cRegister* this)
{
  return (int8_t)this->read(this, I2C_CONTROL_REGISTER);
}

int8_t I2cRegister_readMotorOffset(struct I2cRegister* this)
{
  return (int8_t)this->read(this, I2C_MOTOR0_OFFSET_REGISTER);
}

int8_t I2cRegister_readServoOffset(struct I2cRegister* this)
{
  return (int8_t)this->read(this, I2C_MOTOR1_OFFSET_REGISTER);
}

int8_t I2cRegister_readMotor(struct I2cRegister* this)
{
  return (int8_t)this->read(this, I2C_MOTOR0_REGISTER);
}

int8_t I2cRegister_readServo(struct I2cRegister* this)
{
  return (int8_t)this->read(this, I2C_MOTOR1_REGISTER);
}

void I2cRegister_printEEPROMRegisters(struct I2cRegister* this)
{
  for (int i = 0; i < REGISTER_SIZE; ++i)
  {
    if (shouldBeSaved(i))
    {
      const char* name = this->getNameOfRegister(i);
      uint8_t     data = this->register_[i];
      Printf_print("%s: %d\n", name, data);
    }
  }
}

void recv(uint8_t* data, uint8_t length, uint8_t reg_number)
{
  LED_TOOGLE;
  if (length > 2)
  {
    ++data;
    --length;
  }
  recv_reg_number = reg_number;
  for (int i = 0; (i < length) && (i < BUFFER_SIZE); ++i)
  {
    buffer[i] = data[i];
  }
  recv_flag = 1;
}

void req()
{

}
