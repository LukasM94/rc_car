#ifndef COND_H
#define COND_H

#include <string>
#include <stddef.h>
#include <pthread.h>

class Cond
{
  public:
    Cond(const char* name);
    ~Cond();
    void lock();
    void unlock();
    void sleep();
    void wake();
    void wakeAll();

  private:  
    Cond();
    pthread_mutex_t lock_;
    pthread_cond_t  cond_;
    std::string     name_;
};

#endif