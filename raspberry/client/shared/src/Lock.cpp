#include <Lock.h>
#include <sched.h>

Lock::Lock(const char* name) :
  lock_(0),
  name_(name)
{

}

Lock::~Lock()
{

}

void Lock::lock()
{
  size_t value = 1;
  do
  {
    value = __atomic_exchange_n(&lock_, value, __ATOMIC_RELAXED);
  } while (value && sched_yield());
}

void Lock::unlock()
{
  size_t value = 0;
  __atomic_exchange_n(&lock_, value, __ATOMIC_RELAXED);
}

int Lock::trylock()
{
  size_t value = 1;
  value = __atomic_exchange_n(&lock_, value, __ATOMIC_RELAXED);
  return value;
}
