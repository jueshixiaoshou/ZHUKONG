#include <stm32f1xx_hal.h>
#include "LED.h"
#include "PWM.h"
#include "UART1.h"
#include "UART2.h"
#include "PRINT.h"
#include "I2C.h"
#include "CALLBACK.h"
#include "reset.h"
#include "GTA0.h"
#include "KEY.h"
#include "DAC.h"

int i,j;
uint8_t val1[10];
uint8_t val2[10];
float val;
float current[2] = { 0,0 };
uint8_t SPI;
int8_t speed[2] = { 1,0 };
int8_t accel[4] = { 10,10,10,10 };
int8_t angle[13];
uint8_t MPU6050[13] = { ACCEL_CONFIG,ACCEL_XOUT_H,ACCEL_XOUT_L,ACCEL_YOUT_H,ACCEL_YOUT_L,ACCEL_ZOUT_H,ACCEL_ZOUT_L,GYRO_XOUT_H,GYRO_XOUT_L,GYRO_YOUT_H,GYRO_YOUT_L,GYRO_ZOUT_H	,GYRO_ZOUT_L };
extern int receive1[10];
extern int receive2[10];
extern I2C_HandleTypeDef hi2c1;
#ifdef __cplusplus
extern "C"
#endif

//void SysTick_Handler(void)
//{
//	HAL_IncTick();
//	HAL_SYSTICK_IRQHandler();
//}


void delay()
{
	int a = 10000;
	while (a--)
	{
		;
	}
}

int main(void)
{
		SystemCoreClockUpdate();
		HAL_Init();
		LED_GDB_INIT();//PC
		//PWM_init();
		key_init();//PB
		DAC_init();
		HAL_DAC_SetValue(&hdac, DACx_CHANNEL, DAC_ALIGN_12B_R, current[0]);
		KEY_GPIO_Init();

		HAL_DAC_Start(&hdac, DACx_CHANNEL);
		//while (1)
		//{
		//	if (HAL_GPIO_ReadPin(GPIOA, KEY1) == 1)//(GPIOA->IDR=0X0000DEEF)     控制加减
		//	{
		//		HAL_Delay(10);
		//		if (HAL_GPIO_ReadPin(GPIOA, KEY1) == 1)//(GPIOA->IDR == 0X0000DEEF)
		//		{

		//			val = !val;

		//		}
		//		while (!HAL_GPIO_ReadPin(GPIOA, KEY1));


		//	}
		//}

		val = 100;
		i = 0;
		current[1] = (val - 100) / 100;
		while (1)
		{

			HAL_DAC_SetValue(&hdac, DACx_CHANNEL, DAC_ALIGN_12B_R, current[0]);
			if (HAL_GPIO_ReadPin(GPIOA, KEY1) == 0)//(GPIOA->IDR=0X0000DEEF)     控制加减
			{
				HAL_Delay(10);
				if (HAL_GPIO_ReadPin(GPIOA, KEY1) == 0)//(GPIOA->IDR == 0X0000DEEF)
				{

					HAL_Delay(500);
					if (HAL_GPIO_ReadPin(GPIOA, KEY1) == 1)
					{
						if (i == 0)
						{
							val++;
							if (val > 200)
							{
								val = 200;
							}
						}
						else if (i == 1)
						{
							val--;
							if (val < 200)
							{
								val = 0;
							}
						}
						current[1] = (val - 100) / 100;


					}
					else
					{
						while (HAL_GPIO_ReadPin(GPIOA, KEY1))
						{
							if (i == 0)
							{
								val++;
								if (val > 200)
								{
									val = 200;
								}
							}
							else if (i == 1)
							{
								val--;
								if (val < 200)
								{
									val = 0;
								}
							}

							current[1] = (val - 100) / 100;
							HAL_Delay(100);

						}

					}

				}
				while (!HAL_GPIO_ReadPin(GPIOA, KEY1));


			}
		


			if (HAL_GPIO_ReadPin(GPIOA, KEY2) == 0)//切换与确定
			{
				HAL_Delay(10);
				if (HAL_GPIO_ReadPin(GPIOA, KEY2) == 0)
				{

					HAL_Delay(500);
					if (HAL_GPIO_ReadPin(GPIOA, KEY2) == 1)
					{

						i = !i;

					}
					else
					{
						current[0] = current[1];

					}

				}
				while (!HAL_GPIO_ReadPin(GPIOA, KEY2));


			}
		}
	
      		//LED模块
		/*LED_GDB_INIT();
		for (;;)




		{
			HAL_GPIO_WritePin(GPIOC, LED, GPIO_PIN_SET);
			HAL_Delay(i);
			HAL_GPIO_WritePin(GPIOC, LED, GPIO_PIN_RESET);
			HAL_Delay(i);

		}*/
		
		
	
	
	
	//PWM模块
	  
	    //PWM_init();
		//i = 2000;
		//while (1)
		//{
		//	for (;i < 10000;i++)
		//	{
		//		set_pwm_val(__PWM_PA6, i);
		//		if (i > TIM3->CNT)
		//		{
		//			j = 1;
		//		}
		//		else
		//		{
		//			j = 0;
		//		}
		//	}
		//	for (;i > 0;i--)
		//	{
		//		set_pwm_val(__PWM_PA6, i);
		//		if (i > TIM3->CNT)
		//		{
		//			j = 1;
		//		}
		//		else
		//		{
		//			j = 0;
		//		}
		//	}
		//}
	
		
		
		
		//串口

		/*uart1_init();
		uart2_init(); */  //值都存在receive里
		/*for (i = 0;i <= 9;i++)
		{
			val1[i] = receive1[i];
			val2[i] = receive2[i];
		}*/
		/*uart_cmp1(ch1);
		uart_cmp2(ch2);*/
		//while (1);
		
		//I2C通信

		/*i2c1_init();
		MPU6050_Init();*/
		//while (1)    //模拟手动
		//{
		//	if (I2C1_ReadData(SlaveAddress, CONFIG) != -1)
		//	{
		//		if (I2C1_ReadData(SlaveAddress, CONFIG) != 6)
		//		{
		//			MPU6050_Init();
		//			asm("bkpt 255");
		//		}
		//	}
		//	else
		//	{
		//		//__HAL_I2C_ENABLE(hi2c);
		//		//__HAL_RCC_I2C1_CLK_DISABLE();
		//		i2c1_init();
		//		MPU6050_Init();
		//	}
		//	if (val == 0x68)
		//	{
		//		/*for (i = 0;i <= 12;i++)
		//		{
		//			angle[i] = I2C1_ReadData(SlaveAddress, MPU6050[i]);
		//		}*/
		//		angle[1] = (int8_t)I2C1_ReadData(SlaveAddress, MPU6050[1]);
		//		angle[3] = (int8_t)I2C1_ReadData(SlaveAddress, MPU6050[3]);
		//		SPEED_A(&angle[1], &speed[0], &accel[0], &accel[1]);
		//		SPEED_A(&angle[3], &speed[1], &accel[2], &accel[3]);
		//	}		
		//		val = I2C1_ReadData(SlaveAddress, WHO_AM_I);
		//	
		//	}


	   //I2C1_WriteData(uint8_t Addr, uint8_t Reg, uint8_t Val1[9]); //写入函数示例
       
        //SPI通信
  /* spi1_init();
	while (1)
	{
		SPI = SPI1_WriteRead(speed[0]);

	}*/
	   
        
    //待机模式
     
	
		//电机驱动
	
		//OLCD
	
	
}
