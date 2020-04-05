
#include <com_config.h>
#include <I2cRegister.h>
#include <Eeprom.h>

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

void I2cRegister_writeToEEPROM(struct I2cRegister* this)
{
  for (uint8_t i = 0; i < 256; ++i)
  {
    if (shouldBeSaved(i))
    {
      writeEEPROM(this->register_[i], i);
    }
  }
}

void I2cRegister_readFromEEPROM(struct I2cRegister* this)
{
  for (uint8_t i = 0; i < 256; ++i)
  {
    if (shouldBeSaved(i))
    {
      this->register_[i] = readEEPROM(i);
    }
  }
}

void I2cRegister_write(struct I2cRegister* this, uint8_t reg, uint8_t reg_number)
{
  if (reg_number >= 256)
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
  if (reg_number >= 256)
  {
    return -1;
  }
  return this->register_[reg_number];
}
