
#include <Encoder.h>
#include <Timer.h>

struct Encoder* Encoder_ctor(struct Encoder* this)
{
  Encoder_initialize(this);
  this->speed_     = 0.0;
  this->time_      = 0;
  this->last_time_ = 0;
  this->flag_      = 0;
  this->running_   = 1;
  return this;
}

struct Encoder* Encoder_dtor(struct Encoder* this)
{
  return this;
}

void Encoder_init(struct Encoder* this)
{
  timerInit();
  timerSetCallbacks(this->callbackTimer, this);
}

void Encoder_startTimer(struct Encoder* this)
{
  timerStart();
}

void Encoder_stopTimer(struct Encoder* this)
{
  timerStop();
}

void Encoder_run(struct Encoder* this)
{
  while (this->running_)
  {
    
  }
}

void Encoder_callbackTimer(void* arg)
{
  struct Encoder* encoder = (struct Encoder*)(arg);
  encoder->last_time_ = encoder->time_;
  encoder->time_ += TIME;
}

// Encoder::Encoder() : 
//   speed_(0.0),
//   time_(0),
//   last_time_(0),
//   flag_(false),
//   running_(true)
// {

// }

// Encoder::~Encoder()
// {

// }

// void Encoder::init()
// {
//   timerInit();
//   timerSetCallbacks(callbackTimer, this);
// }

// void Encoder::startTimer()
// {
//   timerStart();
// }

// void Encoder::stopTimer()
// {
//   timerStop();
// }

// void Encoder::callbackTimer(void* arg)
// {
//   Encoder* encoder = reinterpret_cast<Encoder*>(arg);
//   encoder->last_time_ = encoder->time_;
//   encoder->time_ += TIME;
// }

// void Encoder::run()
// {
//   while (running_)
//   {

//   }
// }