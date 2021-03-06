
#include <Pwm.h>
#include <I2cRegister.h>

extern struct I2cRegister i2c_register;

void setOCRA(uint16_t data)
{
  OCR1AH = (data >> 8) & 0xff;
  OCR1AL = data & 0xff;
}
void setOCRB(uint16_t data)
{
  OCR1BH = (data >> 8) & 0xff;
  OCR1BL = data & 0xff;
}
void setOCRARunning(){ TCCR1A |= (1 << COM1A1); }
void setOCRBRunning(){ TCCR1A |= (1 << COM1B1); }
void resetOCRARunning(){ TCCR1A &= ~(1 << COM1A1); }
void resetOCRBRunning(){ TCCR1A &= ~(1 << COM1B1); }

struct Ocr* Ocr_ctorOCRA(struct Ocr* this, const char* name)
{
  this->set          = &setOCRA;
  this->setRunning   = &setOCRARunning;
  this->resetRunning = &resetOCRARunning;

  this->offset_ = 0;
  this->name_   = name;
  return this;
}

struct Ocr* Ocr_ctorOCRB(struct Ocr* this, const char* name)
{
  this->set          = &setOCRB;
  this->setRunning   = &setOCRBRunning;
  this->resetRunning = &resetOCRBRunning;

  this->offset_ = 0;
  this->name_   = name;
  return this;
}

struct Ocr* Ocr_dtor(struct Ocr* this)
{
  return this;
}

static const char MOTOR[] = "motor";
static const char SERVO[] = "servo";

struct Pwm* Pwm_ctor(struct Pwm* this)
{
  Pwm_init(this);

  TCCR1A = (1 << WGM11);
  TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10) | (1 << CS11);
  
  ICR1H = (PWM_TOP >> 8) & 0xff;
  ICR1L = PWM_TOP & 0xff;
  
  Ocr_ctorOCRA(&this->ocra_, MOTOR);
  Ocr_ctorOCRB(&this->ocrb_, SERVO);

  this->ocra_.set(PWM_MIDDLE);
  this->ocrb_.set(PWM_MIDDLE);

  DDRB |= (1 << PB1);
  DDRB |= (1 << PB2);

  return this;
}

struct Pwm* Pwm_dtor(struct Pwm* this)
{
  return this;
}

void Pwm_update(struct Pwm* this)
{
  int8_t motor_register = i2c_register.readMotor(&i2c_register);
  int8_t servo_register = i2c_register.readServo(&i2c_register);

  int8_t motor_offset_register = i2c_register.readMotorOffset(&i2c_register);
  int8_t servo_offset_register = i2c_register.readServoOffset(&i2c_register);

  if (i2c_register.isMotorsRunning(&i2c_register))
  {
    this->start(this);
  }
  else
  {
    this->stop(this);
  }

  this->setMotor(this, motor_register);
  this->setServo(this, servo_register);
  this->setMotorOffset(this, motor_offset_register);
  this->setServoOffset(this, servo_offset_register);
}

void Pwm_start(struct Pwm* this)
{
  this->ocra_.setRunning();
  this->ocrb_.setRunning();
}

void Pwm_stop(struct Pwm* this)
{
  this->ocra_.resetRunning();
  this->ocrb_.resetRunning();
}

void Pwm_setMotor(struct Pwm* this, int8_t data)
{
  uint16_t ocr = (uint16_t)this->ocra_.offset_ + PWM_MIDDLE + (int16_t)data;
  this->ocra_.set(ocr);
}

void Pwm_setServo(struct Pwm* this, int8_t data)
{
  uint16_t ocr = (uint16_t)this->ocra_.offset_ + PWM_MIDDLE + (int16_t)data;
  this->ocrb_.set(ocr);
}

void Pwm_setMotorOffset(struct Pwm* this, int8_t data)
{
  this->ocra_.offset_ = data;
}

void Pwm_setServoOffset(struct Pwm* this, int8_t data)
{
  this->ocrb_.offset_ = data;
}

