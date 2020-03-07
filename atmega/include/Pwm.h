#ifndef PWM_H_
#define PWM_H_

#include <stdint.h>

void pwmInit();
void pwmStart();
void pwmStop();
void pwmChangePulseOfOCRA(int8_t pulse);
void pwmChangePulseOfOCRB(int8_t pulse);

#endif