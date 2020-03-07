
#include <UController.h>
#include <I2c.h>
#include <Usart.h>
#include <Spi.h>
#include <Gpio.h>
#include <debug.h>
#include <com_config.h>

UController::UController(const char* name) : 
  i2c_(0),
  usart_(0),
  spi_(0),
  name_(name),
  communication_lock_((std::string(name) + "::communication_lock_").c_str())
{
  debug(UCONTROLLER, "ctor\n");
}

UController::~UController()
{
  if (spi_)
  {
    delete spi_;
  }
  if (usart_)
  {
    delete usart_;
  }
  if (i2c_)
  {
    delete i2c_;
  }
  debug(UCONTROLLER, "dtor\n");
}

int UController::initI2c()
{
  debug(UCONTROLLER, "initI2c\n");
  if (i2c_ != 0)
  {
    debug(UCONTROLLER, "initI2c: return -1\n");
    return -1;
  }
  std::string temp = name_ + "::I2c";
  i2c_ = new I2c(temp.c_str(), I2C_ADDRESS);
  return 0;
}

int UController::initUsart()
{
  debug(UCONTROLLER, "initUsart\n");
  if (usart_ != 0)
  {
    debug(UCONTROLLER, "initUsart: return -1\n");
    return -1;
  }
  std::string temp = name_ + "::I2c";
  usart_ = new Usart(temp.c_str());
  return 0;
}

int UController::initSpi()
{
  debug(UCONTROLLER, "initSpi\n");
  if (spi_ != 0)
  {
    debug(UCONTROLLER, "initSpi: return -1\n");
    return -1;
  }
  std::string temp = name_ + "::Spi";
  spi_ = new Spi(temp.c_str());
  return 0;
}
