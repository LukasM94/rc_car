#include <Lock.h>
#include <sched.h>

Lock::Lock(const char* name) :
  name_(name)
{
  pthread_mutex_init(&lock_, 0);
}

Lock::~Lock()
{

}

void Lock::lock()
{
  pthread_mutex_lock(&lock_);
}

void Lock::unlock()
{
  pthread_mutex_unlock(&lock_);
}
