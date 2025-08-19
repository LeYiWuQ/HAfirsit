/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart1.h"
#include "oled.h"
#include "delay.h"
#include "dht11.h"
#include "mq2.h"
#include "string.h"
#include "RC522.h"
#include "step_motor.h"
#include "Fire.h"
#include "key.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
void USART_ParseCommand(void);
uint8_t RFID_GetCardID(uint8_t *card_id_buf);
void Process_RFID(void);
void Fire_police(void);
void USART_Test_Send(void);
void USART_SendString(const char *str);
void UART_BLE(void);
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
volatile uint8_t flag_beep = 255;
//volatile uint16_t beep_timer = 0;
volatile uint8_t flag_led = 255;
volatile uint8_t flag_motor = 255;
volatile uint8_t flag_speed = 255;
volatile uint8_t flag_bee = 255;
// 目标卡号（可根据你的卡替换实际UID）
uint8_t valid_card_ids[2][4] = {
    {0xB4, 0xB0, 0x7A, 0x05},  // 卡1
    {0xF4, 0xA7, 0x89, 0x3F}   // 卡2
};
//uint8_t Card_Type1[2];  
//uint8_t Card_ID[4]; 
//uint8_t Card_KEY[6] = {0xff,0xff,0xff,0xff,0xff,0xff};    //{0x11,0x11,0x11,0x11,0x11,0x11};   //?ü??
//uint8_t Card_Data[16];
//uint8_t status;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
		delay_init(72);

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_ADC1_Init();
  MX_SPI1_Init();
  MX_ADC2_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	
		/*启动定时器通道2，通道3*/
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
		PcdReset();		//复位天线
		PcdAntennaOff(); //关闭天线
		delay_ms(100);
		PcdAntennaOn();//打开天线

//		tx_buff = ["adcf"];
		OLED_Init();
		OLED_Clear();
		char buf_tem[10];
		char buf_hum[10];
		char buf_mq2[10];
//		char buf_fire[10];
    float hum = 0;
		uint8_t key = 0;
		static uint8_t key_state = 255;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		//////////////////////////////////////////
		//ID卡调整
		HAL_Delay(10);
		Process_RFID();
		//////////////////////////////////////////
//		printf("HHH\r\n");
//			USART_Test_Send();
		/*语音模块调整,蓝牙函数，跳转函数进入即可*/
		USART_ParseCommand();
		UART_BLE();
		
		/*串口接收后置标志位后执行*/
		if(flag_led  == 1)
		{
			LED_on();
//			HAL_Delay(3000);
			flag_led = 255;
		}else if(flag_led == 0 )LED_off();
		
		
		if(flag_motor == 1)
		{
				step_motor1_on();
				flag_motor = 255;
		}else if(flag_motor == 0) 
		step_motor1_off();
		flag_motor = 255;
					
		if(flag_bee == 1)
		{
				beep_on();
			
		}else if(flag_bee == 0) 
		beep_off();
		//开关门标志位记得重置，不然会出现一直转的现象
		
		if(flag_speed == 1)
		{
			step_motor2_on();
		}else if(flag_speed == 0)step_motor2_off();
		/*  end  */
		
		
		
		/*按键检测调整*/
		key = key_scan(0);
		switch(key)
		{
			case KEY1_PRES:
				LED_on();
				delay_ms(1000);
				break;
			case KEY2_PRES:
				step_motor1_on();
				delay_ms(500);
				step_motor1_off();
				break;
			case KEY3_PRES:
					step_motor2_on();
			break;
			case KEY4_PRES:
				LED_off();
				step_motor2_off();
				break;
			default:
				break;
		}
			
			
		/*显示部分*/
			
		
		/*温湿度调整*/
				
		DHT11_Read_Data();
    hum = Get_humidity();
    if(hum > 80.0)
    {
      beep_on();
    }
		else beep_off();
		
		
		/*OLED显示入口*/
		
//		sprintf(buf_fire,"%d",Get_Fire_Percentage_value());
		sprintf(buf_tem,"%.2f",Get_temperature());
		sprintf(buf_hum,"%.2f",hum);
		sprintf(buf_mq2,"%d",Get_MQ2_Percentage_value());
		OLED_ShowString(0,8,(uint8_t*)"Tem:",12,1);//6*12 “ABC”
		OLED_ShowString(0,20,(uint8_t*)"Hum:",12,1);//6*12 “ABC”
		OLED_ShowString(0,32,(uint8_t*)"mq:",12,1);//6*12 “ABC”
//		OLED_ShowString(0,44,(uint8_t*)"fire:",12,1);//6*12 “ABC
//		
		OLED_ShowString(32,8,(uint8_t*)buf_tem,12,1);//温度数据
		OLED_ShowString(32,20,(uint8_t*)buf_hum,12,1);//湿度数据
		OLED_ShowString(32,32,(uint8_t*)buf_mq2,12,1);//气体数据
//		OLED_ShowString(32,44,(uint8_t*)buf_fire,12,1);//adc数据
		OLED_Refresh();
		
		
		/*  end  */
		
		/*火灾显示函数入口*/
		Fire_police();
		/**/
		
		
		/*  蓝牙发送程序入口 */
		char msg[64];
		sprintf(msg, "Temp:%.1fC    Hum:%.1f%%    MQ2:%d   Fire:%d     \r\n",
				Get_temperature(), Get_humidity(), Get_MQ2_Percentage_value(), Fire_get());
		HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), 100);

		/*     end         */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void USART_Test_Send(void)
{
    char test_msg[] = "USART\r\n";

    // 调用 HAL 库的发送函数，阻塞模式
    if (HAL_UART_Transmit(&huart2, (uint8_t *)test_msg, strlen(test_msg), 1000) == HAL_OK)
    {
        // 成功发送
    }
    else
    {
        // 发送失败
        // 你可以点亮LED、重试或做错误处理
    }
}
/**
*@brief 语音控制函数
*@para  无
*@retval 无
**/
void USART_ParseCommand(void)
{
		char *cmd = (char *)g_usart_rx_buf;
	
	
			if(strncmp(cmd,"ledon",5) == 0)
		{
				flag_led = 1;
				
		}
		
		else if(strncmp(cmd,"ledoff",6) == 0)
		{
				
				flag_led = 0;
		}
		
		
		else if(strncmp(cmd,"motoron",7) == 0)
		{
				flag_motor = 1;
		}
		
		else if(strncmp(cmd,"motoroff",8) == 0)
		{
				flag_motor = 0;
		}
		
		
		else if(strncmp(cmd,"speedon",7) == 0)
		{
				flag_speed = 1;
		}
		else if(strncmp(cmd,"speedoff",8) == 0)
		{
				flag_speed = 0;
		}
		
		g_usart_rx_sta = 0;
		memset(g_usart_rx_buf, 0, sizeof(g_usart_rx_buf));
		HAL_UART_Receive_IT(&huart1, g_rx_buffer, 1);
}

/**
*@brief  蓝牙获取函数
*@para
*@revtal
*/
void UART_BLE(void)
{
char *cmd = (char *)g_usart2_rx_buf;
	
		static uint8_t state_1 = 0;
		static uint8_t state_2 = 0;
		static uint8_t state_3 = 0;
		static uint8_t state_4 = 0;
	
			if(strncmp(cmd,"lighton",7) == 0)
		{
				flag_led = 1;
				state_1++; 
				if(state_1 == 2)
				{
						flag_led = 0;
						state_1 = 0;
				}
		}
		
		else if(strncmp(cmd,"airon",5) == 0)
		{
				flag_motor = 1;
				state_2++; 
				if(state_2 == 2)
				{
						flag_motor = 0;
						state_2 = 0;
				}
		}
		
		
		else if(strncmp(cmd,"fengon",6) == 0)
		{
				flag_speed = 1;
				state_3++;
				if(state_3 == 2)
				{
						flag_speed = 0;
						state_3 = 0;
				}
		}
		
		else if(strncmp(cmd,"beeon",5) == 0)
		{
				flag_bee = 1;
				state_4++;
				if(state_4 == 2)
				{
						flag_bee = 0;
						state_4 = 0;
				}
		}

		
		g_usart2_rx_sta = 0;
		memset(g_usart2_rx_buf, 0, sizeof(g_usart2_rx_buf));
		HAL_UART_Receive_IT(&huart2, g_rx2_buffer, 1);

}

/**
*@brief ID卡获取函数
*@para  无
*@retval 无
**/
uint8_t RFID_GetCardID(uint8_t *card_id_buf)
{
    uint8_t status;
    uint8_t Card_Type1[2];
    uint8_t Card_ID[4];
    uint8_t Card_KEY[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};  // 默认KEY A
		Card_Type1[0]=0x04;
		Card_Type1[1]=0x00;
    // 寻卡
    if (PcdRequest(0x52, Card_Type1) != MI_OK)
        return 0;

    // 防冲突
    status = PcdAnticoll(Card_ID);
    if (status != MI_OK)
        return 0;

    // 选卡
    status = PcdSelect(Card_ID);
    if (status != MI_OK)
        return 0;

    // 验证密码（两次看似多余，你可留一次，部分代码重复了）
    status = PcdAuthState(PICC_AUTHENT1A, 5, Card_KEY, Card_ID);
    if (status != MI_OK)
        return 0;

    // 成功，复制卡号
    memcpy(card_id_buf, Card_ID, 4);

    // 休眠卡片
    PcdHalt();

    return 1;
}

uint8_t Is_Valid_Card(uint8_t *card_uid)
{
    for (int i = 0; i < 2; i++)
    {
        if (memcmp(card_uid, valid_card_ids[i], 4) == 0)
            return 1;  // 匹配
    }
    return 0;  // 未匹配
}

/**
*@brief ID卡判定函数
*@para  无
*@rel 无
**/
void Process_RFID(void)
{
    static uint8_t last_card[4] = {0};
    static uint32_t last_detect_time = 0;
    uint8_t card_uid[4];

    if (RFID_GetCardID(card_uid))
    {
        // 简单防抖：3秒内不重复识别同一张卡
        if (memcmp(card_uid, last_card, 4) == 0 &&
            HAL_GetTick() - last_detect_time < 1000)
        {
            return;  // 忽略重复刷卡
        }

				//        memcpy(last_card, card_uid, 4);  //恢复可防止重复刷卡
        last_detect_time = HAL_GetTick();

//        printf("Card ID: %02X%02X%02X%02X\r\n", card_uid[0], card_uid[1], card_uid[2], card_uid[3]);

        if (Is_Valid_Card(card_uid))
        {
//            printf(">>> Valid card detected! Starting motor...\r\n");
					step_motor1_on();  // 电机1启动函数
//						HAL_Delay(100);
						beep_on();
						delay_ms(100);
						beep_off();
					USART_SendString("come");
					delay_ms(1000);
					step_motor1_off();
					
        }
        else
        {
//            printf("Unrecognized card.\r\n");
        }
    }
}

void Fire_police(void)
{
		if(Fire_get() == 0)
		{
			beep_on();
		}else beep_off();
		
}

/**
 * @brief 通用 USART1 字符串发送函数（阻塞方式）
 * @param str 要发送的字符串
 * @retval None
 */
void USART_SendString(const char *str)
{
    if (str == NULL) return;  // 防止空指针

    // 使用 HAL 库发送字符串，阻塞直到发送完成
    if (HAL_UART_Transmit(&huart1, (uint8_t *)str, strlen(str), 1000) != HAL_OK)
    {
        // 发送失败处理（可加 LED 提示或记录错误）
    }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
