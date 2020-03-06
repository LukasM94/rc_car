#ifndef LOCK_H
#define LOCK_H

#include <string>
#include <stddef.h>

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
    size_t      lock_;
    std::string name_;
};

#endif