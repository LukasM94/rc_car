
#include <ThreadHandler.h>
#include <debug.h>
#include <WorkingThread.h>
#include <algorithm>
#include <assert.h>

std::vector<WorkingThread*> ThreadHandler::threads_;
Cond ThreadHandler::cond_("ThreadHandler::cond_");
unsigned int ThreadHandler::threads_count_ = 0;

void ThreadHandler::init()
{
  WorkingThread::callback_function = &removeThread;
}

void ThreadHandler::lock()
{
  cond_.lock();
}

void ThreadHandler::unlock()
{
  cond_.unlock();
}

bool ThreadHandler::heldByCurrentThread()
{
  return cond_.heldByCurrentThread();
}

void ThreadHandler::broadCast()
{
  cond_.wakeAll();
}

void ThreadHandler::sleep()
{
  cond_.sleep();
}

void ThreadHandler::gotoSleep()
{
  assert(heldByCurrentThread() == true);
  while (threads_count_ == threads_.size())
  {
    debug(THREAD_LIST, "gotoSleep\n");
    sleep();
  }
}

int ThreadHandler::beginThread(WorkingThread* thread, bool detached)
{
  assert(heldByCurrentThread() == true);
  debug(THREAD_LIST, "beginThread: name_ <%s>\n", thread->getName());
  threads_count_++;
  return startThread(thread, detached);
}

int ThreadHandler::exitThread(__attribute__((unused))WorkingThread* thread)
{
  assert(heldByCurrentThread() == false);
  lock();
  debug(THREAD_LIST, "exitThread: name_ <%s>\n", thread->getName());
  threads_count_--;
  broadCast();
  unlock();
}

int ThreadHandler::startThread(WorkingThread* thread, bool detached)
{
  assert(heldByCurrentThread() == true);
  debug(THREAD_LIST, "startThread: name_ <%s>, detached <%s>\n", thread->getName(), detached ? "true" : "false");
  pthread_create(&thread->tid_, 0, WorkingThread::runWrapper, thread);
  if (detached)
  {
    pthread_detach(thread->tid_);
  }
  addThread(thread);
  return 0;
}

int ThreadHandler::startExternThread(WorkingThread* thread)
{
  debug(THREAD_LIST, "startThread: name_ <%s>\n", thread->getName());
  thread->external_ = 1;
  pthread_create(&thread->tid_, 0, WorkingThread::runWrapper, thread);
  return 0;
}

int ThreadHandler::waitTillThreadFinished(WorkingThread* thread, void** return_value)
{
  assert(heldByCurrentThread() == false);
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
  assert(heldByCurrentThread() == true);
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
  assert(heldByCurrentThread() == true);
  auto it = std::find(threads_.begin(), threads_.end(), thread);
  return it != threads_.end();
}

int ThreadHandler::removeThread(WorkingThread* thread)
{
  assert(heldByCurrentThread() == false);
  lock();
  if (isThreadRunning(thread) == false)
  {
    debug(WARNING, "ThreadHandler::removeThread: thread <%p>, name_ <%s> not in threads_\n", thread, thread->getName());
    unlock();
    return -1;
  }
  debug(THREAD_LIST, "removeThread: name_ <%s>\n", thread->getName());
  auto it = std::find(threads_.begin(), threads_.end(), thread);
  threads_.erase(it);
  broadCast();
  unlock();
  return 0;
}

void ThreadHandler::printThreads()
{
  assert(heldByCurrentThread() == true);
  std::string s;
  debug(THREAD_LIST, "printThreads: Expecting threads %d\n", threads_count_);
  for (WorkingThread* t : threads_)
  {
    s += "id <" + std::to_string(t->getId()) + ">, name <" + t->getName() + ">\n";
  }
  debug(THREAD_LIST, "printThreads: Thread list: \n%s\n", s.c_str());
}
