
#include <WorkingThread.h>
#include <debug.h>

WorkingThread::WorkingThread(const char* name) :
  running_(true),
  name_(name)
{
  debug(WORKING_TH, "ctor: name <%s>\n", name_);
}

WorkingThread::~WorkingThread()
{
  debug(WORKING_TH, "dtor\n");
}