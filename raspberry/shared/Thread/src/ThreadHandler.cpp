
#include <ThreadHandler.h>
#include <debug.h>
#include <WorkingThread.h>
#include <algorithm>
#include <assert.h>

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

int ThreadHandler::startThread(WorkingThread* thread, bool detached)
{
  assert(lock_.heldByCurrentThread() == true);
  debug(THREAD_LIST, "startThread: name_ <%s>, detached <%s>\n", thread->getName(), detached ? "true" : "false");
  pthread_create(&thread->tid_, 0, WorkingThread::runWrapper, thread);
  if (detached)
  {
    pthread_detach(thread->tid_);
  }
  addThread(thread);
  return -1;
}

int ThreadHandler::waitTillThreadFinished(WorkingThread* thread, void** return_value)
{
  assert(lock_.heldByCurrentThread() == false);
  debug(THREAD_LIST, "waitTillThreadFinished: name_ <%s>\n", thread->getName());
  int ret;
  if ((ret = pthread_join(thread->getId(), return_value)) != 0)
  {
    debug(WARNING, "ThreadHandler::waitTillThreadFinished: name_ <%s> is not joinable\n", thread->getName());
  }
  return ret;
}

int ThreadHandler::addThread(WorkingThread* thread)
{
  assert(lock_.heldByCurrentThread() == true);
  if (isThreadRunning(thread) == true)
  {
    debug(WARNING, "ThreadHandler::addThread: thread <%p>, name_ <%s> already in threads_\n", thread, thread->getName());
    return -1;
  }
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
  assert(lock_.heldByCurrentThread() == false);
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
