
#include <ThreadHandler.h>
#include <debug.h>
#include <WorkingThread.h>
#include <algorithm>

std::vector<WorkingThread*> ThreadHandler::threads_;
Lock ThreadHandler::lock_("ThreadHandler::lock_");

void ThreadHandler::init()
{
  WorkingThread::callback_function = &removeThread;
}

void ThreadHandler::lock()
{
  lock_.lock();
}

void ThreadHandler::unlock()
{
  lock_.unlock();
}

int ThreadHandler::startThread(WorkingThread* thread)
{
  pthread_create(&thread->tid_, 0, WorkingThread::runWrapper, thread);
  pthread_detach(thread->tid_);
  addThread(thread);
  return -1;
}

int ThreadHandler::addThread(WorkingThread* thread)
{
  if (isThreadRunning(thread) == true)
  {
    debug(WARNING, "ThreadHandler::addThread: thread <%p>, name_ <%s> already in threads_\n", thread, thread->getName());
    return -1;
  }
  debug(THREAD_LIST, "addThread: name_ <%s>\n", thread->getName());
  threads_.push_back(thread);
  return 0;
}

bool ThreadHandler::isThreadRunning(WorkingThread* thread)
{
  auto it = std::find(threads_.begin(), threads_.end(), thread);
  return it != threads_.end();
}

int ThreadHandler::removeThread(WorkingThread* thread)
{
  lock();
  if (isThreadRunning(thread) == false)
  {
    debug(WARNING, "ThreadHandler::addThread: thread <%p>, name_ <%s> not in threads_\n", thread, thread->getName());
    unlock();
    return -1;
  }
  debug(THREAD_LIST, "removeThread: name_ <%s>\n", thread->getName());
  auto it = std::find(threads_.begin(), threads_.end(), thread);
  threads_.erase(it);
  unlock();
  return 0;
}
