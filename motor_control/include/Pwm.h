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
  void (*update)(struct Pwm* this);

  // Private
  void (*start)(struct Pwm* this);
  void (*stop)(struct Pwm* this);
  void (*setServoA)(struct Pwm* this, int8_t data);
  void (*setServoB)(struct Pwm* this, int8_t data);
  void (*setServoAOffset)(struct Pwm* this, int8_t data);
  void (*setServoBOffset)(struct Pwm* this, int8_t data);

  // Members
  struct Ocr ocra_;
  struct Ocr ocrb_;
};

struct Pwm* Pwm_ctor(struct Pwm* this);
struct Pwm* Pwm_dtor(struct Pwm* this);

void Pwm_update(struct Pwm* this);

void Pwm_start(struct Pwm* this);
void Pwm_stop(struct Pwm* this);
void Pwm_setServoA(struct Pwm* this, int8_t data);
void Pwm_setServoB(struct Pwm* this, int8_t data);
void Pwm_setServoAOffset(struct Pwm* this, int8_t data);
void Pwm_setServoBOffset(struct Pwm* this, int8_t data);

__attribute__((unused))static void Pwm_init(struct Pwm* pwm)
{
  pwm->update = &Pwm_update;

  pwm->start    = &Pwm_start;
  pwm->stop     = &Pwm_stop;
  pwm->setServoA = &Pwm_setServoA;
  pwm->setServoB = &Pwm_setServoB;
  pwm->setServoAOffset = &Pwm_setServoAOffset;
  pwm->setServoBOffset = &Pwm_setServoBOffset;
}

#endif