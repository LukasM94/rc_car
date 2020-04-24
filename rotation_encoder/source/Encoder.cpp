
#include <Encoder.h>
#include <Timer.h>

Encoder::Encoder() : 
  state_(POS0),
  prev_state_(POS0),
  forward_(true),
  speed_(0.0),
  speed_index_(0),
  prev_time_(0),
  time_(0),
  running_(true)
{

}

Encoder::~Encoder()
{

}

void Encoder::init()
{
  Timer::init();
  Timer::setCallbacks(callbackTimer, this);
}

void Encoder::startTimer()
{
  Timer::start();
}

void Encoder::stopTimer()
{
  Timer::stop();
}

void Encoder::callbackTimer(void* arg)
{
  Encoder* encoder = reinterpret_cast<Encoder*>(arg);
  encoder->time_ += TIME;
}

void Encoder::run()
{
  while (running_)
  {
    prev_state_ = state_;
    state_      = nextState();
    if (isMoving(prev_state_, state_))
    {
      if (isMovingForward(prev_state_, state_))
      {
        LED_ON;
        forward_ = true;
      }
      else if (isMovingBackward(prev_state_, state_))
      {
        LED_OFF;
        forward_ = false;
      }
      float delta_distance = UMFANG / STEPS;
      float delta_time     = (float)(time_ - prev_time_);

      if (delta_time > 0.1)
      {
        speed_ = delta_distance / delta_time;
        prev_time_ = time_;
      }
      
      speeds_[speed_index_++] = speed_; 
      speed_index_ = speed_index_ % SPEED_ARRAY;
    }
  }
}

enum Encoder::State Encoder::nextState()
{
  int number = (LIGHT_BARRIER0 != 0) + (LIGHT_BARRIER1 != 0) * 2;
  return (enum State)number;
}

bool Encoder::isMoving(enum State prev_state, enum State state)
{
  return (state != prev_state);
}

bool Encoder::isMovingForward(enum Encoder::State prev_state, enum Encoder::State state)
{
  return (state == POS0 && prev_state == POS3) ||
         (state == POS1 && prev_state == POS0) ||
         (state == POS2 && prev_state == POS1) ||
         (state == POS3 && prev_state == POS2);
}

bool Encoder::isMovingBackward(enum Encoder::State prev_state, enum Encoder::State state)
{
  return (state == POS0 && prev_state == POS1) ||
         (state == POS1 && prev_state == POS2) ||
         (state == POS2 && prev_state == POS3) ||
         (state == POS3 && prev_state == POS0);
}
