#include "PWR.h"




void standbymode(void)
{
	
	__HAL_RCC_PWR_CLK_ENABLE();//ʹ��ʱ��

	
	HAL_PWR_EnableBkUpAccess();

	
	//__HAL_RCC_BACKUPRESET_FORCE();
	//__HAL_RCC_BACKUPRESET_RELEASE();

	
	HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN1);//ʧ������

	
	__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);//�����ѱ�־

	
	HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);//��ʹ��

	
	HAL_PWR_EnterSTANDBYMode();//�������ģʽ
}
