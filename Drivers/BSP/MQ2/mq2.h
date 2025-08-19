#ifndef  _MQ2_H_
#define  _MQ2_H_

#include "main.h"
#define  sample  30 //采样速率
extern ADC_HandleTypeDef hadc1;
uint16_t Get_ADC_Value(void);
uint8_t Get_MQ2_Percentage_value(void);
#endif

