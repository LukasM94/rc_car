#ifndef I2C_REGISTER_H
#define I2C_REGISTER_H

#include <stdlib.h>
#include <stdio.h>

struct I2cRegister
{
  void (*writeToEEPROM)(struct I2cRegister* this);
  void (*readFromEEPROM)(struct I2cRegister* this);
  void (*write)(struct I2cRegister* this, uint8_t reg, uint8_t reg_number);
  uint8_t (*read)(struct I2cRegister* this, uint8_t reg_number);

  uint8_t register_[256];
};

struct I2cRegister* I2cRegister_ctor(struct I2cRegister* this);
struct I2cRegister* I2cRegister_dtor(struct I2cRegister* this);

void I2cRegister_writeToEEPROM(struct I2cRegister* this);
void I2cRegister_readFromEEPROM(struct I2cRegister* this);
void I2cRegister_write(struct I2cRegister* this, uint8_t reg, uint8_t reg_number);
uint8_t I2cRegister_read(struct I2cRegister* this, uint8_t reg_number);

__attribute__((unused))static void I2cRegister_init(struct I2cRegister* i2c_register)
{
  i2c_register->writeToEEPROM  = &I2cRegister_writeToEEPROM;
  i2c_register->readFromEEPROM = &I2cRegister_readFromEEPROM;
  i2c_register->write = &I2cRegister_write;
  i2c_register->read  = &I2cRegister_read;
}

#endif