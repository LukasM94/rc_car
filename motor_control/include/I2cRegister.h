#ifndef I2C_REGISTER_H
#define I2C_REGISTER_H

#include <stdlib.h>
#include <stdio.h>

#define REGISTER_SIZE 256

struct I2cRegister
{
  // Public
  void (*update)(struct I2cRegister* this);
  uint8_t (*readControlRegister)(struct I2cRegister* this);
  uint8_t (*isMotorsRunning)(struct I2cRegister* this);
  int8_t (*readServo)(struct I2cRegister* this);
  int8_t (*readMotor)(struct I2cRegister* this);
  int8_t (*readMotorOffset)(struct I2cRegister* this);
  int8_t (*readServoOffset)(struct I2cRegister* this);

  // Private
  void (*writeToEEPROM)(struct I2cRegister* this);
  void (*readFromEEPROM)(struct I2cRegister* this);
  void (*write)(struct I2cRegister* this, uint8_t reg, uint8_t reg_number);
  uint8_t (*read)(struct I2cRegister* this, uint8_t reg_number);

  // Static
  const char* (*getNameOfRegister)(uint8_t reg_number);

  // Print
  void (*printEEPROMRegisters)(struct I2cRegister* this);

  // Member variable
  uint8_t register_[REGISTER_SIZE];
};

struct I2cRegister* I2cRegister_ctor(struct I2cRegister* this);
struct I2cRegister* I2cRegister_dtor(struct I2cRegister* this);

void I2cRegister_update(struct I2cRegister* this);
uint8_t I2cRegister_readControlRegister(struct I2cRegister* this);
uint8_t I2cRegister_isMotorsRunning(struct I2cRegister* this);
int8_t I2cRegister_readMotor(struct I2cRegister* this);
int8_t I2cRegister_readServo(struct I2cRegister* this);
int8_t I2cRegister_readMotorOffset(struct I2cRegister* this);
int8_t I2cRegister_readServoOffset(struct I2cRegister* this);

void I2cRegister_writeToEEPROM(struct I2cRegister* this);
void I2cRegister_readFromEEPROM(struct I2cRegister* this);
void I2cRegister_write(struct I2cRegister* this, uint8_t reg, uint8_t reg_number);
uint8_t I2cRegister_read(struct I2cRegister* this, uint8_t reg_number);
void I2cRegister_printEEPROMRegisters(struct I2cRegister* this);

extern const char* getNameOfRegister(unsigned char register_number);

__attribute__((unused))static void I2cRegister_init(struct I2cRegister* i2c_register)
{
  i2c_register->update = &I2cRegister_update;
  i2c_register->readControlRegister = &I2cRegister_readControlRegister;
  i2c_register->isMotorsRunning     = &I2cRegister_isMotorsRunning;
  i2c_register->readMotor = &I2cRegister_readMotor;
  i2c_register->readServo = &I2cRegister_readServo;
  i2c_register->readMotorOffset = &I2cRegister_readMotorOffset;
  i2c_register->readServoOffset = &I2cRegister_readServoOffset;

  i2c_register->writeToEEPROM  = &I2cRegister_writeToEEPROM;
  i2c_register->readFromEEPROM = &I2cRegister_readFromEEPROM;
  i2c_register->write = &I2cRegister_write;
  i2c_register->read  = &I2cRegister_read;
  i2c_register->printEEPROMRegisters = &I2cRegister_printEEPROMRegisters;

  i2c_register->getNameOfRegister = &getNameOfRegister;
}

#endif