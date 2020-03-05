#ifndef CONTROL_H
#define CONTROL_H

int control(int argv, char* argc[]);

#include <string>
#include <atomic>
#include <map>
#include <ControlHandler.h>

class GamePad;

class Control
{
  public:
    Control(GamePad* game_pad);
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

  private:
    Control();
    Control(const Control&);

    ControlHandler control_handler_;
    std::map<const char*, int> tids_;

    std::atomic_bool running_;

    static const int LED_PIN = 0;
    static const char I2C[];
    static const char GPIO[];
};

#endif