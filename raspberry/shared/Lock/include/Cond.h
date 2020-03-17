#ifndef COND_H
#define COND_H

#include <string>
#include <stddef.h>
#include <pthread.h>
#include <Lock.h>

class Cond : public Lock
{
  public:
    Cond(const char* name);
    ~Cond();
    void sleep();
    void wake();
    void wakeAll();

  private:  
    Cond();
    pthread_cond_t cond_;
};

#endif