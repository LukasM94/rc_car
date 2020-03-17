#include <pthread.h>
#include <sched.h>
#include <debug.h>
#include <ControlHandler.h>
#include <GamePad.h>
#include <unistd.h>
#include <Control.h>
#include <ThreadHandler.h>
#include <I2cHandler.h>
#include <GpioHandler.h>
#include <UController.h>
#include <client_config.h>

ControlHandler::ControlHandler(UController* u_controller) :
  WorkingThread("ControlHandler"),
  i2c_handler_(0),
  gpio_handler_(0),
  u_controller_(u_controller)
{
  debug(CONTROL, "ctor\n");
}

//--------------------------------------------------------------------
ControlHandler::~ControlHandler()
{
  debug(CONTROL, "dtor\n");
}

//--------------------------------------------------------------------
void ControlHandler::run()
{
  debug(CTL_HANDLER, "run: Start\n");

  i2c_handler_  = new I2cHandler(this);
  gpio_handler_ = new GpioHandler(this);

  gpio_handler_->init();
  // i2c_handler_->init();
  u_controller_->initI2c();

  ThreadHandler::lock();
  ThreadHandler::beginThread(i2c_handler_);
  ThreadHandler::beginThread(gpio_handler_);
  ThreadHandler::unlock();

  while (running_)
  {
    sleep(CLIENT_SLEEP_TIME);

    debug(CTL_HANDLER, "run: Goes to sleep\n");
    ThreadHandler::gotoSleep();
    debug(CTL_HANDLER, "run: Got up\n");

    ThreadHandler::lock();
    if (ThreadHandler::isThreadRunning(i2c_handler_) == false)
    {
      ThreadHandler::startThread(i2c_handler_);
    }
    if (ThreadHandler::isThreadRunning(gpio_handler_) == false)
    {
      ThreadHandler::startThread(gpio_handler_);
    }
    ThreadHandler::unlock();
  }

  i2c_handler_->deinit();
  gpio_handler_->deinit();

  delete i2c_handler_;
  delete gpio_handler_;

  debug(CTL_HANDLER, "run: Exit\n");
}