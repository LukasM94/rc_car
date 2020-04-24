
#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>
#include <config.h>

struct Encoder
{
  void (*init)(struct Encoder* this);
  void (*startTimer)(struct Encoder* this);
  void (*stopTimer)(struct Encoder* this);
  void (*run)(struct Encoder* this);
  void (*callbackTimer)(void* arg);
  float speed_;
  volatile unsigned long long time_;
  volatile unsigned long long last_time_;
  volatile uint8_t flag_;
  volatile uint8_t running_;
};

struct Encoder* Encoder_ctor(struct Encoder* this);
struct Encoder* Encoder_dtor(struct Encoder* this);

void Encoder_init(struct Encoder* this);
void Encoder_startTimer(struct Encoder* this);
void Encoder_stopTimer(struct Encoder* this);
void Encoder_run(struct Encoder* this);
void Encoder_callbackTimer(void* arg);

__attribute__((unused))static void Encoder_initialize(struct Encoder* encoder)
{
  encoder->init          = &Encoder_init;
  encoder->startTimer    = &Encoder_startTimer;
  encoder->stopTimer     = &Encoder_stopTimer;
  encoder->run           = &Encoder_run;
  encoder->callbackTimer = &Encoder_callbackTimer;
}


// class Encoder
// {
//   public:
//     Encoder();
//     ~Encoder();
//     void init();
//     void startTimer();
//     void stopTimer();
//     void run();

//   private:

//     float speed_;

//     volatile unsigned long long time_;
//     volatile unsigned long long last_time_;
//     volatile bool flag_;
//     volatile bool running_;
// };

#endif