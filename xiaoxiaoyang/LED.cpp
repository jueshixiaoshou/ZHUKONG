#include  <LED.h>
void LED_GDB_INIT()
{
	SystemCoreClockUpdate();
	HAL_Init();

	__GPIOC_CLK_ENABLE();  
	
	GPIO_InitTypeDef GPIO_InitStructure; 
	SystemInit();	
    
	GPIO_InitStructure.Pin = LED;      //“˝Ω≈≈‰÷√
	GPIO_InitStructure.Mode =  GPIO_MODE_OUTPUT_PP;	
	GPIO_InitStructure.Pull = GPIO_NOPULL;   
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;	  
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure); 	   
}