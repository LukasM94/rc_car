#ifndef LOCK_H
#define LOCK_H

#include <string>
#include <stddef.h>
#include <pthread.h>

class Lock
{
  public:
    Lock(const char* name);
    ~Lock();
    void lock();
    void unlock();
    int trylock();

  private:  
    Lock();
    pthread_mutex_t lock_;
    std::string     name_;
};

#endif