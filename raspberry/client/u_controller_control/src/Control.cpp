#include <pthread.h>
#include <sched.h>
#include <debug.h>
#include <Control.h>
#include <GamePad.h>
#include <unistd.h>

const char Control::I2C[]  = "i2c";
const char Control::GPIO[] = "gpio";

//--------------------------------------------------------------------
Control::Control(UController* u_controller) :
  control_handler_(u_controller),
  tids_(),
  lock_("Control::lock_"),
  running_(1)
{
  debug(CONTROL, "ctor\n");
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
void* Control::wrapperStart(void* args)
{
  const char*     primary_key     = ((struct start_arg*)args)->primary_key_;
  Control*        control         = ((struct start_arg*)args)->control_;
  ControlHandler* control_handler = &control->control_handler_;

  debug(CONTROL, "wrapperStart: Primary key is %s\n", primary_key);
  debug(CONTROL, "wrapperStart: Go to f_ptr\n");
  void* ret = ((struct start_arg*)args)->f_ptr_(control_handler);

  control->lock();
  control->removeTid(primary_key);
  control->unlock();

  return 0;
}

//--------------------------------------------------------------------
int Control::setTid(const char* primary_key, int tid)
{
  auto it = tids_.find(primary_key);
  if (it != tids_.end())
  {
    debug(WARNING, "Control::setTid: %s is already in map\n", primary_key);
    return -1;
  }
  tids_[primary_key] = tid;
  return 0;
}

//--------------------------------------------------------------------
int Control::removeTid(const char* primary_key)
{
  auto it = tids_.find(primary_key);
  if (it == tids_.end())
  {
    debug(WARNING, "Control::removeTid: %s not found\n", primary_key);
    return -1;
  }
  tids_.erase(it);
  return 0;
}

//--------------------------------------------------------------------
void Control::run()
{
  pthread_t tid_i2c;
  pthread_t tid_gpio;

  struct start_arg  args_i2c  = {this, I2C, 0, &ControlHandler::i2cFunction};
  struct start_arg  args_gpio = {this, GPIO, 0,  &ControlHandler::gpioFunction};

  init();

  lock();
  debug(CONTROL, "run: Create threads\n");
  pthread_create(&tid_gpio, 0, Control::wrapperStart, &args_gpio);
  pthread_create(&tid_i2c, 0, Control::wrapperStart, &args_i2c);
  
  debug(CONTROL, "run: Set the tids\n");
  setTid(args_gpio.primary_key_, tid_gpio);
  setTid(args_i2c.primary_key_, tid_i2c);
  unlock();

  while (running_)
  {
    lock();
    if (tids_.size() == 0)
    {
      unlock();
      break;
    }
    printTidEntries();
    unlock();

    debug(CONTROL, "run: Nothing to do\n");
    sleep(5);
  }

  debug(CONTROL, "run: Exit\n");
}

//--------------------------------------------------------------------
void Control::printTidEntries()
{
  std::string str;
  for (auto it = tids_.begin(); it != tids_.end(); ++it)
  {
    str += "<" + std::string(it->first) + ">, ";
  }
  str.erase(str.end() - 2, str.end());
  debug(CTL_DATA, "printTidEntries: %s\n", str.c_str());
}