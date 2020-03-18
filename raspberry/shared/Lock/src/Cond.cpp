#include <Cond.h>
#include <sched.h>
#include <sys/time.h>

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

void Cond::sleep(unsigned int timed)
{
  struct timespec ts;
  struct timeval now;
  gettimeofday(&now,NULL);
  ts.tv_sec = now.tv_sec + timed;
  pthread_cond_timedwait(&cond_, &lock_, &ts);
}

void Cond::wake()
{
  pthread_cond_signal(&cond_);
}

void Cond::wakeAll()
{
  pthread_cond_broadcast(&cond_);
}
