
#include <com_config.h>
#include <I2cRegister.h>
#include <Eeprom.h>
#include <Printf.h>

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

void I2cRegister_printEEPROMRegisters(struct I2cRegister* this)
{
  char*   name;
  uint8_t data;
  for (int i = 0; i < REGISTER_SIZE; ++i)
  {
    if (shouldBeSaved(i))
    {
      name = getNameOfRegister(i);
      data = this->register_[i];
      Printf_print("%s: %d\n", name, data);
    }
  }
}
