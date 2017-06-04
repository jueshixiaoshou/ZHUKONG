#include "SYSTEM.h"
#ifdef USE_UCOSII_OS
#include "os_includes.h"
#endif
int8_t SYSTEM_SetClock(uint8_t freq)
{
	ErrorStatus HSEStartUpStatus;
	uint32_t pllMul;

	/* ѡ��Ƶϵ�� */
	switch (freq)
	{
	case(32) :
		pllMul = RCC_PLLMul_4;
		break;
	case(40) :
		pllMul = RCC_PLLMul_5;
		break;
	case(48) :
		pllMul = RCC_PLLMul_6;
		break;
	case(56) :
		pllMul = RCC_PLLMul_7;
		break;
	case(64) :
		pllMul = RCC_PLLMul_8;
		break;
	case(72) :
		pllMul = RCC_PLLMul_9;
		break;
	default:
		RCC_DeInit();
		return -1;
	}

	/*��λRCC */
	RCC_DeInit();

	/*ʹ�ܴ�HSE�ⲿ����ʱ�� */
	RCC_HSEConfig(RCC_HSE_ON);

	/* �ȴ�HSEʱ��׼������*/
	HSEStartUpStatus = RCC_WaitForHSEStartUp();

	/* ��HSEʱ��׼������ */
	if (HSEStartUpStatus == SUCCESS)
	{
		/* ʹ�ܿ���FLASH ,�������ȥ����FLASH��������ݣ�Ҫ�ǲ����ó������� */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

		/* FLASH����������ʱ���� */
		FLASH_SetLatency(FLASH_Latency_2);

		/* ����AHB���ߵ�ʱ�ӷ�Ƶ */
		RCC_HCLKConfig(RCC_SYSCLK_Div1);        //����Ƶ

												/* ���ø���ʱ�ӵ�ʱ�ӷ�Ƶ */
		RCC_PCLK2Config(RCC_HCLK_Div1);         //����Ƶ

												/* ���õ���ʱ�ӵ�ʱ�ӷ�Ƶ */
		RCC_PCLK1Config(RCC_HCLK_Div2);         //����Ƶ

												/* ����PLLʱ�ӵ�����ͱ�Ƶ�� */
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, pllMul);//ѡ��HSE����Ƶ���룬��ƵPLLMUL��

													  /* ���� PLL */
		RCC_PLLCmd(ENABLE);

		/* �ȴ�PLLʱ�Ӿ��� */
		while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
		{
		}

		/*ѡ��PLLʱ����Ϊ���� */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

		/* �ȴ�ϵͳ�л���� */
		while (RCC_GetSYSCLKSource() != 0x08)
		{
		}
	}
	else              //��HSEϵͳ��ʼʧ�ܣ���������ʧ��
	{
		return -1;
	}

	return 0;         //�������óɹ�
}

/**************************************************************************** /

void NVIC_Config(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
}
