#ifndef WORKING_THREAD_H
#define WORKING_THREAD_H

#include <atomic>
#include <string>

class ThreadHandler;

class WorkingThread
{
  public:
    WorkingThread(const char* name);
    ~WorkingThread();

    static void* runWrapper(void* arg);
    
    virtual void run() = 0;
    inline void cancel()
    {
      running_ = 0;
    }
    inline const char* getName()
    {
      return name_.c_str();
    }
    inline long unsigned int getId()
    {
      return tid_;
    }
  protected:
    std::atomic_bool  running_;
    std::string       name_;
    long unsigned int tid_;
  private:
    friend ThreadHandler;
    WorkingThread();
    static int (*callback_function)(WorkingThread*);
};

#endif