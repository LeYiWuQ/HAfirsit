/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2025-07-31 21:59:53
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2025-08-01 00:04:40
 * @FilePath: \MDK-ARMc:\Users\le\Desktop\blue_6\Drivers\BSP\DHT11\dht11.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef  _DHT11_H_
#define  _DHT11_H_

#include "main.h"
#include "delay.h"

#define DATA_GPIO_OUT(x)    HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, x ? GPIO_PIN_SET : GPIO_PIN_RESET)
#define DATA_GPIO_IN        HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin)

extern float temperature;
extern float humidity;

unsigned int DHT11_Read_Data(void);//��ȡģ������
float Get_temperature(void);//���ض�ȡģ�����¶�����
float Get_humidity(void);//���ض�ȡģ����ʪ������
#endif

