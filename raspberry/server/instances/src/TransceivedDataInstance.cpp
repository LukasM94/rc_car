
#include <TransceivedDataInstance.h>
#include <debug.h>

TransceivedDataInstance* TransceivedDataInstance::instance_ = 0;

TransceivedDataInstance::TransceivedDataInstance() :
  received_images_(0),
  transmitted_bytes_(0),
  received_bytes_(0)
{
  debug(TRANS_DATA, "ctor\n");
}

TransceivedDataInstance::~TransceivedDataInstance()
{
  debug(TRANS_DATA, "dtor\n");
}

TransceivedDataInstance* TransceivedDataInstance::instance()
{
  if (instance_ == 0)
  {
    instance_ = new TransceivedDataInstance();
  }
  return instance_;
}
