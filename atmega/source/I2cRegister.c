
#include <com_config.h>
#include <I2cRegister.h>
#include <Eeprom.h>
#include <Printf.h>
#include <I2cSlave.h>

struct I2cRegister* I2cRegister_ctor(struct I2cRegister* this)
{
  I2cRegister_init(this);
  this->readFromEEPROM(this);
  return this;
}

struct I2cRegister* I2cRegister_dtor(struct I2cRegister* this)
{
  this->writeToEEPROM(this);
  return this;
}

void I2cRegister_initSlave(struct I2cRegister* this, void (*recv)(uint8_t*, uint8_t, uint8_t), void (*req)())
{
  i2cSlaveSetCallbacks(recv, req);
  i2cSlaveInit(I2C_ADDRESS);
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

int8_t I2cRegister_readMotorOffset(struct I2cRegister* this)
{
  return (int8_t)this->read(this, I2C_MOTOR0_OFFSET_REGISTER);
}

int8_t I2cRegister_readServoOffset(struct I2cRegister* this)
{
  return (int8_t)this->read(this, I2C_MOTOR1_OFFSET_REGISTER);
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
