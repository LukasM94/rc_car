#include <Cond.h>
#include <sched.h>
#include <sys/time.h>
#include <debug.h>

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

void Cond::sleep(unsigned int timed) // in milliseconds
{
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  ts.tv_nsec += (long long)timed * 1000000;
  ts.tv_sec  += timed / 1000;
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
