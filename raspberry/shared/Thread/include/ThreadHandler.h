#ifndef THREAD_HANDLER_H
#define THREAD_HANDLER_H

#include <atomic>
#include <vector>
#include <Cond.h>

class WorkingThread;

class ThreadHandler
{
  public:
    static void init();
    static void lock();
    static void unlock();
    static int  beginThread(WorkingThread* thread, bool detached = true);
    static int  exitThread(WorkingThread* thread);
    static int  startThread(WorkingThread* thread, bool detached = true);
    static bool isThreadRunning(WorkingThread* thread);
    static int  waitTillThreadFinished(WorkingThread* thread, void** ret = 0);
    static void gotoSleep();
    static int  startExternThread(long unsigned int* tid, void* (*wrapperStart)(void*), void* arg);

  private:
    static bool heldByCurrentThread();
    static void broadCast();
    static void sleep();
    static int addThread(WorkingThread* thread);
    static int removeThread(WorkingThread* thread);

    static std::vector<WorkingThread*> threads_;
    static Cond cond_;
    static unsigned int threads_count_;
};

#endif