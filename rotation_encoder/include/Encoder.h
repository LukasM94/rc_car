
#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>
#include <config.h>

#define UMFANG 0.4555 // m
#define STEPS  16.0

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
    enum State 
    {
      POS0 = 0,
      POS1 = 1,
      POS2 = 3,
      POS3 = 2
    };

    enum State nextState();
    bool isMoving(enum State prev_state, enum State state);
    bool isMovingForward(enum State prev_state, enum State state);
    bool isMovingBackward(enum State prev_state, enum State state);

    static void callbackTimer(void* arg);

    enum State state_;
    enum State prev_state_;

    bool forward_;

    static const unsigned int SPEED_ARRAY = 16;

    float speed_;
    float speeds_[SPEED_ARRAY];
    unsigned int speed_index_;

    unsigned long long prev_time_;

    volatile unsigned long long time_;
    volatile bool running_;
};

#endif