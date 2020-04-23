
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

  private:
    static void callbackTimer(void* arg);
    float speed_;
};

#endif