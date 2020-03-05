#include <pthread.h>
#include <sched.h>
#include <debug.h>
#include <Control.h>
#include <GamePad.h>

const char Control::I2C[]  = "i2c";
const char Control::GPIO[] = "gpio";

//--------------------------------------------------------------------
Control::Control() :
  control_handler_(0),
  tids_(),
  running_(1)
{
  debug(CONTROL, "ctor\n");
}
//--------------------------------------------------------------------
Control::Control(GamePad* game_pad) :
  control_handler_(game_pad),
  tids_(),
  running_(1)
{
  debug(CONTROL, "ctor: game_pad <%p>\n", game_pad);
}

//--------------------------------------------------------------------
Control::~Control()
{
  debug(CONTROL, "dtor\n");
}

//--------------------------------------------------------------------
void Control::init()
{
  debug(CONTROL, "init\n");
  control_handler_.gpioInit();
  control_handler_.i2cInit();
}

//--------------------------------------------------------------------
void Control::run()
{
  pthread_t tid;

  init();

  debug(CONTROL, "run: Create threads\n");
  pthread_create(&tid, 0, ControlHandler::gpioFunction, &control_handler_);
  tids_[GPIO] = tid;
  pthread_create(&tid, 0, ControlHandler::i2cFunction, &control_handler_);
  tids_[I2C] = tid;

  debug(CONTROL, "run: Go to sleep\n");
  for (auto it = tids_.begin(); it != tids_.end(); ++it)
  {
    pthread_join(it->second, 0);
  }
  debug(CONTROL, "run: Exit\n");
}
