
#include <Encoder.h>
#include <Timer.h>

Encoder::Encoder() : 
  speed_(0.0)
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
  encoder->last_time_ = encoder->time_;
  encoder->time_ += TIME;
}