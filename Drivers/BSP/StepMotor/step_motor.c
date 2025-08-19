#include "step_motor.h"

/**
*@breif 门电机开启函数
*@para 无
*@revl	无
**/
void step_motor1_on(void)
{
		HAL_GPIO_WritePin(STR1_GPIO_Port,STR1_Pin,GPIO_PIN_SET);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 100);
		HAL_Delay(500);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 0);
		
}

/**
*@breif 门电机关闭函数
*@para 无
*@revl	无
**/
void step_motor1_off(void)
{
		HAL_GPIO_WritePin(STR1_GPIO_Port,STR1_Pin,GPIO_PIN_RESET);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 100);
			HAL_Delay(500);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 0);
		
		
}

/**
*@breif 空调电机开启函数
*@para 无
*@revl	无
**/
void step_motor2_on(void)
{
		HAL_GPIO_WritePin(STR1_GPIO_Port,STR1_Pin,GPIO_PIN_SET);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, 100);

}

/**
*@breif 空调电机关闭函数
*@para 无
*@revl	无
**/
void step_motor2_off(void)
{

		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, 0);

}

