#include "config.h"

/*
 * ��������BSP_Init
 * ����  ��ʱ�ӳ�ʼ����Ӳ����ʼ��
 * ����  ����
 * ���  ����
 */
void BSP_Init(void)
{
    SystemInit();		/* ����ϵͳʱ��Ϊ72M */
    RTC_Configuration();
    LED_GPIO_Config();  /* LED �˿ڳ�ʼ�� */
    Usart1_Init();
    Lcd_Init();
    Sd_InitAndTest();
}

/*
 * ��������SysTick_init
 * ����  ������SysTick��ʱ��
 * ����  ����
 * ���  ����
 */
void SysTick_init(void)
{
    SysTick_Config(SystemCoreClock/OS_TICKS_PER_SEC);//��ʼ����ʹ��SysTick��ʱ��
}
