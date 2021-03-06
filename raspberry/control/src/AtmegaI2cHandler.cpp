#include <AtmegaI2cHandler.h>
#include <debug.h>
#include <Atmega.h>
#include <com_config.h>
#include <I2cHandler.h>
#include <Peripherial.h>
#include <I2c.h>
#include <Atmega.h>
#include <debug.h>
#include <unistd.h>
#include <GamePad.h>
#include <GamePadInstance.h>
#include <ControlHandler.h>
#include <I2cRegisterData.h>

AtmegaI2cHandler::AtmegaI2cHandler(ControlHandler* control_handler) :
  I2cHandler(control_handler),
  i2c_register_data_(0)
{
  debug(A_I2C_HANDL, "ctor: %p\n", control_handler);
}

AtmegaI2cHandler::~AtmegaI2cHandler()
{
  debug(A_I2C_HANDL, "dtor\n");
}

void AtmegaI2cHandler::init()
{
  debug(A_I2C_HANDL, "init\n");
  u_controller_      = new Atmega();
  i2c_register_data_ = new I2cRegisterData(0, 0);
  u_controller_->initI2c();
}

void AtmegaI2cHandler::deinit()
{
  debug(A_I2C_HANDL, "deinit\n");

  if (i2c_register_data_ != 0)
  {
    delete i2c_register_data_;
  }
  if (u_controller_ != 0)
  {
    delete u_controller_;
  }
}

void AtmegaI2cHandler::run()
{
  debug(A_I2C_HANDL, "run: Start\n");

  GamePad* game_pad = GamePadInstance::instance()->getGamePad();
  debug(A_I2C_HANDL, "run: Reset u controller\n");
  Peripherial::instance()->resetUcontroller();

  sleep(ATMEGA_RECOVER_AFTER_RESET);

  i2c_error_ = 0;
  running_   = 1;

  bool game_pad_connected      = 1;
  bool game_pad_connected_prev = 1;

  debug(A_I2C_HANDL, "run: Start with communcation\n");

  sleep(I2C_HANDLER_WAIT_TILL_ATMEGA_RESETED);

  while (running_)
  {
    game_pad->lock();
    game_pad->timedWaitTillNewData();

    game_pad_connected_prev = game_pad_connected;
    game_pad_connected = game_pad->isConnected();

    if (!game_pad_connected)
    {
      debug(WARNING, "I2cHandler::run: GamePad not connected\n");
      Peripherial::instance()->resetResetPin();
      game_pad->unlock();
      sleep(I2C_HANDLER_NOT_CONNECTED_TRY_AGAIN_SLEEP_TIME);
      continue;
    }
    Peripherial::instance()->setResetPin();
    i2c_register_data_->refreshData(game_pad);
    game_pad->unlock();

    i2c_register_data_->nextState();

    I2cNewData* data = i2c_register_data_->getNewData();
    
    writeNewData(data);
  }

  debug(A_I2C_HANDL, "run: Exit\n");
}

void AtmegaI2cHandler::writeNewData(I2cNewData* new_data)
{
  if (new_data->size() == 0)
  {
    writeI2c(I2C_CONTROL_REGISTER, I2C_CONTROL_REGISTER_SYNC);
  }
  for (auto it = new_data->begin(); it != new_data->end(); ++it)
  {
    writeI2c(it->first, it->second);
  }
}

void AtmegaI2cHandler::writeI2c(uint8_t reg, const uint8_t* data, int length)
{
  debug(I2C_HANDL_D, "writeI2c: reg <%d>, data <%p>, length <%d>\n", reg, data, length);
  if (u_controller_->writeI2c(reg, data, length) == 0)
  {
    i2c_error_ = 0;
  }
  else 
  {
    i2c_error_++;
  }
  if (i2c_error_ > I2C_ERROR_THRESHOLD)
  {
    debug(WARNING, "I2cHandler::writeI2c: %d errors on the i2c line\n", i2c_error_.load());
    // running_ = false;
  }
}

void AtmegaI2cHandler::writeI2c(uint8_t reg, uint8_t data)
{
  debug(I2C_HANDL_D, "writeI2c: reg <%d>, data <%d>\n", reg, data);
  if (u_controller_->writeI2c(reg, &data, 1) == 0)
  {
    i2c_error_ = 0;
  }
  else 
  {
    i2c_error_++;
  }
  if (i2c_error_ > I2C_ERROR_THRESHOLD)
  {
    debug(WARNING, "I2cHandler::writeI2c: %d errors on the i2c line\n", i2c_error_.load());
    Peripherial::instance()->resetResetPin();
    usleep(100);
    Peripherial::instance()->setResetPin();
    sleep(I2C_HANDLER_NOT_CONNECTED_TRY_AGAIN_SLEEP_TIME);
  }
}