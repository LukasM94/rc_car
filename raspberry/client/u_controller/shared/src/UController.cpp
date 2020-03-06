
#include <UController.h>
#include <I2c.h>
#include <Usart.h>
#include <Spi.h>
#include <debug.h>
#include <com_config.h>

UController::UController() : 
  i2c_(0),
  usart_(0),
  spi_(0)
{
  pthread_mutex_init(&communication_lock_, 0);
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
}

int UController::initI2c()
{
  if (i2c_ != 0)
  {
    return -1;
  }
  i2c_ = new I2c("UController::i2c", I2C_ADDRESS);
  return 0;
}

int UController::initUsart()
{
  if (usart_ != 0)
  {
    return -1;
  }
  usart_ = new Usart("UController::Usart");
  return 0;
}

int UController::initSpi()
{
  if (i2c_ != 0)
  {
    return -1;
  }
  spi_ = new Spi("UController::spi");
  return 0;
}