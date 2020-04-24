
#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>
#include <config.h>

class Encoder
{
  public:
    Encoder();
    ~Encoder();
    void init();
    void startTimer();
    void stopTimer();
    void run();

  private:
    static void callbackTimer(void* arg);

    float speed_;

    volatile unsigned long long time_;
    volatile unsigned long long last_time_;
    volatile bool flag_;
    volatile bool running_;
};

#endif