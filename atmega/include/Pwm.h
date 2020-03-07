#ifndef PWM_H_
#define PWM_H_

#include <stdint.h>

void pwmInit();
void pwmChangePulseOfOCRA(int8_t pulse);
void pwmChangePulseOfOCRB(int8_t pulse);

#endif