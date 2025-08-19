#ifndef _STEP_MOTOR_H_
#define _STEP_MOTOR_H_

#include "main.h"
extern TIM_HandleTypeDef htim2;

void step_motor1_on(void);
void step_motor1_off(void);
void step_motor2_on(void);
void step_motor2_off(void);
#endif

