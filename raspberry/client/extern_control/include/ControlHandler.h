#ifndef CONTROL_HANDLER_H
#define CONTROL_HANDLER_H

#include <map>
#include <Lock.h>
#include <WorkingThread.h>

class GamePad;

class ControlHandler : public WorkingThread
{
  public:
    ControlHandler();
    ~ControlHandler();

    inline static void* runWrapper(void* arg)
    {
      reinterpret_cast<ControlHandler*>(arg)->run();
      return 0;
    }
    virtual void run();

    void init();
    void deinit();
    inline void lock()
    {
      lock_.lock();
    }
    inline void unlock()
    {
      lock_.unlock();
    }

    int setTid(const char* primary_key, int tid);
    int removeTid(const char* primary_key);
    bool findTid(const char* primary_key);

  private:
    ControlHandler(const ControlHandler&);

    struct start_arg
    { 
      ControlHandler* control_handler_;
      const char*     primary_key_;
      void*           args_;
      void*           (*f_ptr_)(void*);
    };

    static void* wrapperStart(void* arg);

    void printTidEntries();

    std::map<const char*, int> tids_;
    Lock lock_;

    static const int LED_PIN = 0;
    static const char I2C[];
    static const char GPIO[];
};

#endif