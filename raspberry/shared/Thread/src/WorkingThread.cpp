
#include <WorkingThread.h>
#include <debug.h>
#include <pthread.h>

int (*WorkingThread::callback_function)(WorkingThread*) = 0;

WorkingThread::WorkingThread(const char* name) :
  running_(true),
  name_(name),
  tid_(-1)
{
  debug(WORKING_TH, "ctor: name <%s>\n", name_.c_str());
}

WorkingThread::~WorkingThread()
{
  debug(WORKING_TH, "dtor\n");
}

void* WorkingThread::runWrapper(void* arg)
{
  WorkingThread* thread = reinterpret_cast<WorkingThread*>(arg);

  thread->run();

  if (callback_function != 0)
  {
    callback_function(thread);
  }

  return 0;
}