#ifndef WORKING_THREAD_H
#define WORKING_THREAD_H

#include <atomic>
#include <string>

class WorkingThread
{
  public:
    WorkingThread(const char* name);
    ~WorkingThread();
    virtual void run() = 0;
    inline void cancel()
    {
      running_ = 0;
    }
  protected:
    std::atomic_bool running_;
    std::string      name_;
  private:
    WorkingThread();
};

#endif