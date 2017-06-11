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

int i,j;
uint8_t val1[10];
uint8_t val2[10];
uint8_t val;
uint8_t SPI;
int8_t speed[2] = { 1,0 };
int8_t accel[4] = { 10,10,10,10 };
uint8_t KEY;
int8_t angle[13];
uint8_t MPU6050[13] = { ACCEL_CONFIG,ACCEL_XOUT_H,ACCEL_XOUT_L,ACCEL_YOUT_H,ACCEL_YOUT_L,ACCEL_ZOUT_H,ACCEL_ZOUT_L,GYRO_XOUT_H,GYRO_XOUT_L,GYRO_YOUT_H,GYRO_YOUT_L,GYRO_ZOUT_H	,GYRO_ZOUT_L };
extern int receive1[10];
extern int receive2[10];
extern I2C_HandleTypeDef hi2c1;
#ifdef __cplusplus
extern "C"
#endif


#if defined(STM32F102x6) || defined(STM32F102xB) || defined(STM32F103x6) || defined(STM32F103xB) || defined(STM32F103xG) || defined(STM32F103xE)

void SystemClock_Config(void)
{
	RCC_ClkInitTypeDef clkinitstruct = { 0 };
	RCC_OscInitTypeDef oscinitstruct = { 0 };
	RCC_PeriphCLKInitTypeDef rccperiphclkinit = { 0 };

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	oscinitstruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	oscinitstruct.HSEState = RCC_HSE_ON;
	oscinitstruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	oscinitstruct.PLL.PLLMUL = RCC_PLL_MUL9;

	oscinitstruct.PLL.PLLState = RCC_PLL_ON;
	oscinitstruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;

	if (HAL_RCC_OscConfig(&oscinitstruct) != HAL_OK)
	{
		asm("bkpt 255");
	}

	/* USB clock selection */
	rccperiphclkinit.PeriphClockSelection = RCC_PERIPHCLK_USB;
	rccperiphclkinit.UsbClockSelection = RCC_USBPLLCLK_DIV1_5;
	HAL_RCCEx_PeriphCLKConfig(&rccperiphclkinit);

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
	clocks dividers */
	clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;
	clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
	if (HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_2) != HAL_OK)
	{
		asm("bkpt 255");
	}
}

#else

void SystemClock_Config(void)
{
	RCC_ClkInitTypeDef clkinitstruct = { 0 };
	RCC_OscInitTypeDef oscinitstruct = { 0 };
	RCC_PeriphCLKInitTypeDef rccperiphclkinit = { 0 };

	/* Configure PLLs ------------------------------------------------------*/
	/* PLL2 configuration: PLL2CLK = (HSE / HSEPrediv2Value) * PLL2MUL = (25 / 5) * 8 = 40 MHz */
	/* PREDIV1 configuration: PREDIV1CLK = PLL2CLK / HSEPredivValue = 40 / 5 = 8 MHz */
	/* PLL configuration: PLLCLK = PREDIV1CLK * PLLMUL = 8 * 9 = 72 MHz */
	/* Enable HSE Oscillator and activate PLL with HSE as source */
	oscinitstruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	oscinitstruct.HSEState = RCC_HSE_ON;
	oscinitstruct.HSEPredivValue = RCC_HSE_PREDIV_DIV5;
	oscinitstruct.PLL.PLLMUL = RCC_PLL_MUL9;
	oscinitstruct.Prediv1Source = RCC_PREDIV1_SOURCE_PLL2;

	oscinitstruct.PLL.PLLState = RCC_PLL_ON;
	oscinitstruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	oscinitstruct.PLL2.PLL2State = RCC_PLL2_ON;
	oscinitstruct.PLL2.HSEPrediv2Value = RCC_HSE_PREDIV2_DIV5;
	oscinitstruct.PLL2.PLL2MUL = RCC_PLL2_MUL8;
	HAL_RCC_OscConfig(&oscinitstruct);

	/* USB clock selection */
	rccperiphclkinit.PeriphClockSelection = RCC_PERIPHCLK_USB;
	rccperiphclkinit.UsbClockSelection = RCC_USBPLLCLK_DIV3;
	HAL_RCCEx_PeriphCLKConfig(&rccperiphclkinit);

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
	clocks dividers */
	clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;
	clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
	HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_2);
}
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
		SystemClock_Config();
		SystemCoreClockUpdate();
		HAL_Init();
	
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
   spi1_init();
    while (1)
	{
		SPI = SPI1_WriteRead(speed[0]);

	}
	   

	
		//电机驱动
	
		//OLCD
	
	
}
