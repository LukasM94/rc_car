#ifndef WORKING_THREAD_H
#define WORKING_THREAD_H

#include <atomic>
#include <string>

class WorkingThread
{
  public:
    WorkingThread(const char* name);
    ~WorkingThread();

    inline static void* runWrapper(void* arg)
    {
      reinterpret_cast<WorkingThread*>(arg)->run();
      return 0;
    }
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