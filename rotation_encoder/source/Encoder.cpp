
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
  timerInit();
  timerSetCallbacks(callbackTimer, 0);
}

void Encoder::callbackTimer(void* arg)
{
}