#include <pthread.h>
#include <sched.h>
#include <debug.h>
#include <Control.h>
#include <GamePad.h>

//--------------------------------------------------------------------
Control::Control(GamePad* game_pad) :
  control_handler_(game_pad),
  tids_(),
  running_(1)
{

}

//--------------------------------------------------------------------
void Control::init()
{
  control_handler_.gpioInit();
  control_handler_.i2cInit();
}

//--------------------------------------------------------------------
void Control::run()
{
  pthread_t tid;
  pthread_create(&tid, 0, ControlHandler::gpioFunction, &control_handler_);
  tids_["gpio"] = tid;
  pthread_create(&tid, 0, ControlHandler::i2cFunction, &control_handler_);
  tids_["i2c"] = tid;

  for (auto it = tids_.begin(); it != tids_.end(); ++it)
  {
    pthread_join(it->second, 0);
  }
}
