
#include <Pwm.h>
#include <I2cRegister.h>
#include <Printf.h>

extern struct I2cRegister i2c_register;

void setOCR1A(uint16_t data)
{
  OCR1AH = (data >> 8) & 0xff;
  OCR1AL = data & 0xff;
}
void setOCR1B(uint16_t data)
{
  OCR1BH = (data >> 8) & 0xff;
  OCR1BL = data & 0xff;
}
void setOCR2(uint16_t data)
{
  OCR2A = 0xff & data;
}
void setOCR1ARunning(){ TCCR1A |= (1 << COM1A1); }
void setOCR1BRunning(){ TCCR1A |= (1 << COM1B1); }
void setOCR2Running(){ TCCR2A |= (1 << COM2A1); }
void resetOCR1ARunning(){ TCCR1A &= ~(1 << COM1A1); }
void resetOCR1BRunning(){ TCCR1A &= ~(1 << COM1B1); }
void resetOCR2Running(){ TCCR2A &= ~(1 << COM2A1); }

struct Ocr* Ocr_ctorOCR1A(struct Ocr* this, const char* name)
{
  this->set          = &setOCR1A;
  this->setRunning   = &setOCR1ARunning;
  this->resetRunning = &resetOCR1ARunning;

  this->offset_ = 0;
  this->name_   = name;
  return this;
}

struct Ocr* Ocr_ctorOCR1B(struct Ocr* this, const char* name)
{
  this->set          = &setOCR1B;
  this->setRunning   = &setOCR1BRunning;
  this->resetRunning = &resetOCR1BRunning;

  this->offset_ = 0;
  this->name_   = name;
  return this;
}

struct Ocr* OCR_ctorOCR2(struct Ocr* this, const char* name)
{
  this->set          = &setOCR2;
  this->setRunning   = &setOCR2Running;
  this->resetRunning = &resetOCR2Running;

  this->offset_ = 0;
  this->name_   = name;
  return this;
}

struct Ocr* Ocr_dtor(struct Ocr* this)
{
  return this;
}

static const char SERVOA[] = "ServoA";
static const char SERVOB[] = "servoB";
static const char MOTOR[] = "Motor";

struct Pwm* Pwm_ctor(struct Pwm* this)
{
  Pwm_init(this);

  TCCR1A = (1 << WGM11);
  TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10) | (1 << CS11);

  TCCR2A = (1 << WGM21) | (1 << WGM20);
  TCCR2B = (1 << CS21);
  
  ICR1H = (PWM_TOP >> 8) & 0xff;
  ICR1L = PWM_TOP & 0xff;
  
  Ocr_ctorOCR1A(&this->ocr1a_, SERVOA);
  Ocr_ctorOCR1B(&this->ocr1b_, SERVOB);
  OCR_ctorOCR2(&this->ocr2_, MOTOR);

  this->ocr1a_.set(PWM_MIDDLE);
  this->ocr1b_.set(PWM_MIDDLE);
  this->ocr2_.set(0x80);

  // Chip select
  DDRB |= (1 << PB0);
  // Servo a
  DDRB |= (1 << PB1);
  // Servo b
  DDRB |= (1 << PB2);
  // Motor
  DDRB |= (1 << PB3);

  this->toleranz_for_ocr2_ = 5;

  return this;
}

struct Pwm* Pwm_dtor(struct Pwm* this)
{
  return this;
}

void Pwm_update(struct Pwm* this)
{
  int8_t servoA_register = i2c_register.readServoA(&i2c_register);
  int8_t servoB_register = i2c_register.readServoB(&i2c_register);
  int8_t motor_register  = i2c_register.readMotor(&i2c_register);

  int8_t servoA_offset_register = i2c_register.readServoAOffset(&i2c_register);
  int8_t servoB_offset_register = i2c_register.readServoBOffset(&i2c_register);
  int8_t motor_offset_register  = i2c_register.readMotorOffset(&i2c_register);

  if (i2c_register.isServosRunning(&i2c_register))
  {
    this->start(this);
  }
  else
  {
    this->stop(this);
  }

  this->setServoA(this, servoA_register);
  this->setServoB(this, servoB_register);
  this->setMotor(this, motor_register);
  this->setServoAOffset(this, servoA_offset_register);
  this->setServoBOffset(this, servoB_offset_register);
  this->setMotorOffset(this, motor_offset_register);
}

void Pwm_start(struct Pwm* this)
{
  this->ocr1a_.setRunning();
  this->ocr1b_.setRunning();
  this->ocr2_.setRunning();
}

void Pwm_stop(struct Pwm* this)
{
  this->ocr1a_.resetRunning();
  this->ocr1b_.resetRunning();
  this->ocr2_.resetRunning();
}

void Pwm_setMotor(struct Pwm* this, int8_t data)
{
  // todo: improve
  data = data * -1;
  uint16_t ocr = data + 0x80;
  if (data < this->toleranz_for_ocr2_ && data > - this->toleranz_for_ocr2_)
  {
    PORTB &= ~(1 << PB0);
  }
  else
  {
    PORTB |= (1 << PB0);
  }
  
  if (ocr < 20)
  {
    ocr = 20;
  }
  else if (ocr > 236)
  {
    ocr = 236;
  }
  this->ocr2_.set(ocr);
}

void Pwm_setServoA(struct Pwm* this, int8_t data)
{
  uint16_t ocr = (uint16_t)(this->ocr1a_.offset_ + PWM_MIDDLE + (int16_t)data);
  this->ocr1a_.set(ocr);
}

void Pwm_setServoB(struct Pwm* this, int8_t data)
{
  uint16_t ocr = (uint16_t)(this->ocr1a_.offset_ + PWM_MIDDLE + (int16_t)data);
  this->ocr1b_.set(ocr);
}

void Pwm_setMotorOffset(struct Pwm* this, int8_t data)
{
  this->ocr2_.offset_ = data;
}

void Pwm_setServoAOffset(struct Pwm* this, int8_t data)
{
  this->ocr1a_.offset_ = data;
}

void Pwm_setServoBOffset(struct Pwm* this, int8_t data)
{
  this->ocr1b_.offset_ = data;
}

