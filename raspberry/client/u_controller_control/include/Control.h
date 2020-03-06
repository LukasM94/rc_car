#ifndef CONTROL_H
#define CONTROL_H

int control(int argv, char* argc[]);

#include <string>
#include <atomic>
#include <map>
#include <ControlHandler.h>
// #include <pthread.h>
#include <Lock.h>

class GamePad;
class UController;

class Control
{
  public:
    Control(UController* u_controller);
    Control(UController* u_controller, GamePad* game_pad);
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
    inline void initLock()
    {
      pthread_mutex_init(&lock_, 0);
    }
    inline void lock()
    {
      pthread_mutex_lock(&lock_);
      // lock_.lock();
    }
    inline void unlock()
    {
      pthread_mutex_unlock(&lock_);
      // lock_.unlock();
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
    pthread_mutex_t lock_;
    // Lock lock_;

    std::atomic_bool running_;

    static const int LED_PIN = 0;
    static const char I2C[];
    static const char GPIO[];
};

#endif