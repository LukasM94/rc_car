#ifndef THREAD_HANDLER_H
#define THREAD_HANDLER_H

#include <atomic>
#include <vector>
#include <Lock.h>

class WorkingThread;

class ThreadHandler
{
  public:
    static void init();
    static void lock();
    static void unlock();
    static int  startThread(WorkingThread* thread, bool detached = true);
    static bool isThreadRunning(WorkingThread* thread);
    static int  waitTillThreadFinished(WorkingThread* thread, void** ret = 0);

  private:
    static int addThread(WorkingThread* thread);
    static int removeThread(WorkingThread* thread);

    static std::vector<WorkingThread*> threads_;
    static Lock lock_;
};

#endif