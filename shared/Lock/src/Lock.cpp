#include <Lock.h>
#include <sched.h>
#include <WorkingThread.h>
#include <debug.h>
#include <assert.h>

Lock::Lock(const char* name) :
  name_(name),
  held_by_(-1)
{
  pthread_mutex_init(&lock_, 0);
}

Lock::~Lock()
{

}

void Lock::lock()
{
  if (held_by_ == pthread_self())
  {
    debug(ERROR, "Lock::lock: Deadlock of thread %s\n", name_.c_str());
    assert(0);
  }
  pthread_mutex_lock(&lock_);
  held_by_ = pthread_self();
}

void Lock::unlock()
{
  held_by_ = -1;
  pthread_mutex_unlock(&lock_);
}

bool Lock::heldByCurrentThread()
{
  return (held_by_ == pthread_self());
}
