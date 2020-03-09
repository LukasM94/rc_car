#ifndef CONTROL_H
#define CONTROL_H

#include <string>
#include <atomic>
#include <map>
#include <ControlHandler.h>
#include <Lock.h>

class GamePad;
class UController;

class Control
{
  public:
    Control(UController* u_controller);
    ~Control();

    inline static void* runWrapper(void* arg)
    {
      reinterpret_cast<Control*>(arg)->run();
      return 0;
    }
    void run();
    inline void cancel()
    {
      running_ = 0;
    }

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

  private:
    Control();
    Control(const Control&);

    struct start_arg
    { 
      Control*    control_;
      const char* primary_key_;
      void*       args_;
      void*       (*f_ptr_)(void*);
    };

    static void* wrapperStart(void* arg);

    void printTidEntries();

    ControlHandler control_handler_;
    std::map<const char*, int> tids_;
    Lock lock_;

    std::atomic_bool running_;

    static const int LED_PIN = 0;
    static const char I2C[];
    static const char GPIO[];
};

#endif