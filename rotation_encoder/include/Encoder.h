
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

  private:
    static void callbackTimer(void* arg);

    float speed_;

    volatile unsigned long time_;
    volatile unsigned long last_time_;
};

#endif