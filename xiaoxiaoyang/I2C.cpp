#include "I2C.h"


I2C_HandleTypeDef hi2c1;

void delay()
{
	int a = 10000;
	while (a--)
	{
		;
	}
}

void i2c1_deinit(void)
{
	//__HAL_RCC_AFIO_CLK_DISABLE();		//开启AFIO时钟
	//__HAL_AFIO_REMAP_I2C1_DISABLE();		//重映射I2C1的IO口
	//__HAL_RCC_GPIOB_CLK_DISABLE();		//开启GPIOB时钟
	//__HAL_RCC_I2C1_CLK_DISABLE();		//开启I2C1时钟

	HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8 | GPIO_PIN_9);


	hi2c1.Instance = I2C1;

	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.ClockSpeed = 100000;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	hi2c1.Init.OwnAddress1 = I2C_ADDRESS;
	hi2c1.Init.OwnAddress2 = 0xFE;

	I2C1->CCR = 0;
	I2C1->CR1 = 0;
	I2C1->CR2 = 0;
	I2C1->OAR1 = 0;
	I2C1->OAR2 = 0;
	I2C1->TRISE = 0;
	I2C1->SR1 = 0;
	I2C1->SR2 = 0;
	HAL_I2C_DeInit(&hi2c1);

	delay();
	delay();

}

void i2c1_init(void)
{
	GPIO_InitTypeDef gpio_init;
	


	i2c1_deinit();

    __HAL_RCC_AFIO_CLK_ENABLE();		//开启AFIO时钟
	__HAL_AFIO_REMAP_I2C1_ENABLE();		//重映射I2C1的IO口
	__HAL_RCC_GPIOB_CLK_ENABLE();		//开启GPIOB时钟
	__HAL_RCC_I2C1_CLK_ENABLE();		//开启I2C1时钟


	gpio_init.Pin = GPIO_PIN_8 | GPIO_PIN_9;

	gpio_init.Mode = GPIO_MODE_OUTPUT_OD;
	gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
	gpio_init.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOB, &gpio_init);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	HAL_Delay(100);
	for (char i = 0;i < 9;i++)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
		delay();
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
		delay();
	}
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	HAL_Delay(100);

	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);

	gpio_init.Pin = GPIO_PIN_8 | GPIO_PIN_9;

	gpio_init.Mode = GPIO_MODE_AF_OD;
	gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
	gpio_init.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOB, &gpio_init);


	hi2c1.Instance = I2C1;

	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.ClockSpeed = 100000;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	hi2c1.Init.OwnAddress1 = I2C_ADDRESS;
	hi2c1.Init.OwnAddress2 = 0xFE;

	if (HAL_I2C_Init(&hi2c1) != HAL_OK)
	{
		asm("bkpt 255");
	}


}

uint8_t I2C1_ReadData(uint8_t Addr, uint8_t Reg)
{
	HAL_StatusTypeDef status = HAL_OK;
	uint8_t value = -1;

	status = HAL_I2C_Mem_Read(&hi2c1, Addr, Reg, I2C_MEMADD_SIZE_8BIT, &value, 1, 2);

	/* Check the communication status */
	if (status != HAL_OK)
	{
		/* Re-Initialize the BUS */

	}
	return value;
}

void I2C1_ReadMultData(uint8_t Addr, uint8_t Reg, uint8_t *value, uint8_t len)
{
	HAL_StatusTypeDef status = HAL_OK;

	status = HAL_I2C_Mem_Read(&hi2c1, Addr, Reg, I2C_MEMADD_SIZE_8BIT, value, len, 2 * len);

	/* Check the communication status */
	if (status != HAL_OK)
	{
		/* Re-Initialize the BUS */

	}
}

void I2C1_WriteData(uint8_t Addr, uint8_t Reg, uint8_t Value)
{
	HAL_StatusTypeDef status = HAL_OK;

	status = HAL_I2C_Mem_Write(&hi2c1, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, &Value, 1, 2);

	/* Check the communication status */
	if (status != HAL_OK)
	{
		/* Re-Initialize the BUS */

	}
}

void MPU6050_Init(void)
{
	I2C1_WriteData(SlaveAddress, PWR_MGMT_1, 0x00);

	I2C1_WriteData(SlaveAddress, SMPLRT_DIV, 0x07);

	I2C1_WriteData(SlaveAddress, CONFIG, 0x06);

	I2C1_WriteData(SlaveAddress, GYRO_CONFIG, 0x18);

	I2C1_WriteData(SlaveAddress, ACCEL_CONFIG, 0x01);
}


void MPU6050_key(void)
{
	/*gpio_init.Pin = GPIO_PIN_8 | GPIO_PIN_9;

	gpio_init.Mode = GPIO_MODE_OUTPUT_OD;
	gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
	gpio_init.Pull = GPIO_PULLUP;*/
	/*HAL_GPIO_Init(GPIOB, &gpio_init);*/
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	HAL_Delay(100);
	for (char i = 0;i < 9;i++)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
		delay();
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
		delay();
	}
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	HAL_Delay(100);
}

