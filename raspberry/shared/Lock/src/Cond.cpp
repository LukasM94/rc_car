#include <Cond.h>
#include <sched.h>

Cond::Cond(const char* name) :
  Lock(name)
{
  pthread_mutex_init(&lock_, 0);
  pthread_cond_init(&cond_, 0);
}

Cond::~Cond()
{

}

void Cond::sleep()
{
  pthread_cond_wait(&cond_, &lock_);
}

void Cond::wake()
{
  pthread_cond_signal(&cond_);
}

void Cond::wakeAll()
{
  pthread_cond_broadcast(&cond_);
}
