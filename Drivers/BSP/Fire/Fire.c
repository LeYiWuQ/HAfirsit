#include "Fire.h"


/**
*@brief	adc读取函数
*@param	无
*@rel   平均电压值
*/
uint16_t Get_ADCfire_Value(void)
{
    HAL_ADC_PollForConversion(&hadc2, HAL_MAX_DELAY); // 等待转换完成
    return HAL_ADC_GetValue(&hadc2);
}


/**
*@brief	Fire转换函数
*@param	无
*@rel   平均气体值
*/
uint8_t Get_Fire_Percentage_value(void)
{
    const uint16_t adc_max = 4095;
    uint16_t adc_val = Get_ADCfire_Value();

    float percentage = ((float)adc_val / adc_max) * 100.0f;
    return (uint8_t)percentage;
}

