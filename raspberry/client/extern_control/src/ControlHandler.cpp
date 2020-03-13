#include <pthread.h>
#include <sched.h>
#include <debug.h>
#include <ControlHandler.h>
#include <GamePad.h>
#include <unistd.h>
#include <ControlInstance.h>

const char ControlHandler::I2C[]  = "i2c";
const char ControlHandler::GPIO[] = "gpio";

//--------------------------------------------------------------------
// ControlHandler::ControlHandler(UController* u_controller) :
//   WorkingThread("ControlHandler"),
//   control_handler_(u_controller),
//   tids_(),
//   lock_("ControlHandler::lock_")
// {
//   debug(CONTROL, "ctor\n");
// }
ControlHandler::ControlHandler() :
  WorkingThread("ControlHandler"),
  tids_(),
  lock_("ControlHandler::lock_")
{
  debug(CONTROL, "ctor\n");
}

//--------------------------------------------------------------------
ControlHandler::~ControlHandler()
{
  debug(CONTROL, "dtor\n");
}

//--------------------------------------------------------------------
void ControlHandler::init()
{
  debug(CONTROL, "init\n");
  ControlInstance::instance()->gpioInit();
  ControlInstance::instance()->i2cInit();
}

//--------------------------------------------------------------------
void ControlHandler::deinit()
{
  debug(CONTROL, "deinit\n");
  ControlInstance::instance()->gpioDeInit();
}

//--------------------------------------------------------------------
void* ControlHandler::wrapperStart(void* args)
{
  const char*      primary_key      = ((struct start_arg*)args)->primary_key_;
  ControlHandler*         control_handler          = ((struct start_arg*)args)->control_handler_;
  ControlInstance* control_instance = ControlInstance::instance();

  debug(CONTROL, "wrapperStart: Primary key is %s\n", primary_key);
  debug(CONTROL, "wrapperStart: Go to f_ptr\n");
  void* ret = ((struct start_arg*)args)->f_ptr_(control_instance);

  control_handler->lock();
  control_handler->removeTid(primary_key);
  control_handler->unlock();

  return 0;
}

//--------------------------------------------------------------------
int ControlHandler::setTid(const char* primary_key, int tid)
{
  auto it = tids_.find(primary_key);
  if (it != tids_.end())
  {
    debug(WARNING, "ControlHandler::setTid: %s is already in map\n", primary_key);
    return -1;
  }
  tids_[primary_key] = tid;
  return 0;
}

//--------------------------------------------------------------------
int ControlHandler::removeTid(const char* primary_key)
{
  auto it = tids_.find(primary_key);
  if (it == tids_.end())
  {
    debug(WARNING, "ControlHandler::removeTid: %s not found\n", primary_key);
    return -1;
  }
  tids_.erase(it);
  return 0;
}

//--------------------------------------------------------------------
bool ControlHandler::findTid(const char* primary_key)
{
  auto it = tids_.find(primary_key);
  return (it != tids_.end());
}

//--------------------------------------------------------------------
void ControlHandler::run()
{
  pthread_t tid_i2c;
  pthread_t tid_gpio;

  struct start_arg args_i2c  = {this, I2C, 0, &ControlInstance::i2cFunction};
  struct start_arg args_gpio = {this, GPIO, 0,  &ControlInstance::gpioFunction};

  init();

  lock();
  debug(CONTROL, "run: Create threads\n");
  pthread_create(&tid_gpio, 0, ControlHandler::wrapperStart, &args_gpio);
  pthread_create(&tid_i2c, 0, ControlHandler::wrapperStart, &args_i2c);
  
  debug(CONTROL, "run: Set the tids\n");
  setTid(args_gpio.primary_key_, tid_gpio);
  setTid(args_i2c.primary_key_, tid_i2c);
  unlock();

  while (running_)
  {
    lock();
    if (tids_.size() != 2)
    {
      if (findTid(args_gpio.primary_key_) == false)
      {
        pthread_create(&tid_gpio, 0, ControlHandler::wrapperStart, &args_gpio);
        setTid(args_gpio.primary_key_, tid_gpio);
        debug(CONTROL, "run: Restart gpio\n");
      }
      if (findTid(args_i2c.primary_key_) == false)
      {
        pthread_create(&tid_i2c, 0, ControlHandler::wrapperStart, &args_i2c);
        setTid(args_i2c.primary_key_, tid_i2c);
        debug(CONTROL, "run: Restart i2c\n");
      }
      unlock();
    }
    else
    {
      printTidEntries();
      unlock();
      debug(CONTROL, "run: Nothing to do\n");
      sleep(5);
    }
  }

  debug(CONTROL, "run: Exit\n");
}

//--------------------------------------------------------------------
void ControlHandler::printTidEntries()
{
  std::string str;
  for (auto it = tids_.begin(); it != tids_.end(); ++it)
  {
    str += "<" + std::string(it->first) + ">, ";
  }
  str.erase(str.end() - 2, str.end());
  debug(CTL_DATA, "printTidEntries: %s\n", str.c_str());
}