#ifndef PWM_H_
#define PWM_H_

#include <stdint.h>
#include <avr/io.h>
#include <stdio.h>

struct Ocr
{
  void (*set)(uint16_t data);
  void (*setRunning)();
  void (*resetRunning)();

  const char* name_;
  int8_t     offset_;
};

struct Ocr* OCR_ctorOCRA(struct Ocr* this, const char* name);
struct Ocr* OCR_ctorOCRB(struct Ocr* this, const char* name);
struct Ocr* OCR_dtor(struct Ocr* this);

#define PWM_TOP    4999
#define PWM_MIDDLE (PWM_TOP * 3) / 40

struct Pwm
{
  // Public
  void (*run)(struct Pwm* this);

  // Private
  void (*start)(struct Pwm* this);
  void (*stop)(struct Pwm* this);
  void (*setMotor)(struct Pwm* this, int8_t data);
  void (*setServo)(struct Pwm* this, int8_t data);
  void (*setMotorOffset)(struct Pwm* this, int8_t data);
  void (*setServoOffset)(struct Pwm* this, int8_t data);

  // Members
  struct Ocr ocra_;
  struct Ocr ocrb_;
};

struct Pwm* Pwm_ctor(struct Pwm* this);
struct Pwm* Pwm_dtor(struct Pwm* this);

void Pwm_run(struct Pwm* this);

void Pwm_start(struct Pwm* this);
void Pwm_stop(struct Pwm* this);
void Pwm_setMotor(struct Pwm* this, int8_t data);
void Pwm_setServo(struct Pwm* this, int8_t data);
void Pwm_setMotorOffset(struct Pwm* this, int8_t data);
void Pwm_setServoOffset(struct Pwm* this, int8_t data);

__attribute__((unused))static void Pwm_init(struct Pwm* pwm)
{
  pwm->run = &Pwm_run;

  pwm->start    = &Pwm_start;
  pwm->stop     = &Pwm_stop;
  pwm->setMotor = &Pwm_setMotor;
  pwm->setServo = &Pwm_setServo;
  pwm->setMotorOffset = &Pwm_setMotorOffset;
  pwm->setServoOffset = &Pwm_setServoOffset;
}









void pwmInit();
uint8_t getPwmRunning();
void pwmStart();
void pwmStop();
void pwmChangePulseOfOCRA(int8_t pulse);
void pwmChangePulseOfOCRB(int8_t pulse);

#endif