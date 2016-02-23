/*******************************************************************************
 *
 * �ļ�����: rtc.c
 *
 * �ļ�����: RTC����
 * ��    ��: WLB
 * ����ʱ��: 2015-2-1
 * �ļ��汾: 
 * �޸���ʷ: 
 *           1. 2015-2-1  WLB  Created
 *******************************************************************************/




/*******************************************************************************
 *                                  ͷ�ļ�����                                 *
 *******************************************************************************/
#include    "config.h"

/*******************************************************************************
 *                          ���ļ������ȫ�ֱ����ͺ�������                     *
 *******************************************************************************/


/*******************************************************************************
 *                             �ⲿ�����ͺ�������                              *
 *******************************************************************************/

/*****************************************************
//�������ƣ�void SetRtcTime(u8 year,u8 month,u8 day,u8 hour,u8 min,u8 sec)
//����������RTC��ʼֵ�趨����.
//���������unsigned char year :�趨�꣬��2010�꣬��year=10��
//          unsigned char moth���趨�£���11�£�  ��moth=11��
//          unsigned char day ���趨���ڣ���24�գ���day=24��
//          unsigned char hour���趨Сʱ����16ʱ����hour=16��
//			unsigned char min ���趨���ӣ���4�֣���min=3��
//			unsigned char sec ���趨�룬��34�룬��Ϊsec=34��
//���أ���
*****************************************************/
void SetRtcTime(u8 year,u8 month,u8 day,u8 hour,u8 min,u8 sec)
{
	unsigned long temp;
	temp=year*360*24*3600+(month-1)*30*24*3600+(day-1)*24*3600+hour*3600+min*60+sec;
	RTC_WaitForLastTask();
	RTC_SetCounter(temp);
	RTC_WaitForLastTask();
}
/*****************************************************
//�������ƣ�Read_RTC_Time
//������������ȡRTC�Ĵ���ֵ����ת��Ϊ������ʱ�������ݣ�ͨ�����ڴ���
//�����������
//���أ���
*****************************************************/
void Read_RTC_Time(void)
{
    #if 0
	unsigned long Time_Value;
	unsigned long Day_Value;
	//Time_Struct TimeStruct1;
	Time_Value=RTC_GetCounter();
	Day_Value=Time_Value/(86400);	//24*3600
	
	Year=Day_Value/360;
	Month=(Day_Value-Year*360)/30;
	Day=(Day_Value-Year*360)%30;
	Month+=1;
	Day+=1;
	Hour=(Time_Value-Day_Value*24*3600)/3600;
	Min=(Time_Value-Day_Value*24*3600-Hour*3600)/60;
	Sec=Time_Value-Day_Value*24*3600-Hour*3600-Min*60;

	Uart1_PutChar(0x32);                      
	Uart1_PutChar(0x30);
	Uart1_PutChar(Year/10+0x30);
	Uart1_PutChar(Year%10+0x30);
	Uart1_PutChar('-');
	Uart1_PutChar('-');
	Uart1_PutChar(Month/10+0x30);
	Uart1_PutChar(Month%10+0x30);
	Uart1_PutChar('-');
	Uart1_PutChar('-');
	Uart1_PutChar(Day/10+0x30);
	Uart1_PutChar(Day%10+0x30);
	Uart1_PutChar('-');
	Uart1_PutChar('-');
	Uart1_PutChar(Hour/10+0x30);
	Uart1_PutChar(Hour%10+0x30);
	Uart1_PutChar('-');
	Uart1_PutChar('-');
	Uart1_PutChar(Min/10+0x30);
	Uart1_PutChar(Min%10+0x30);
	Uart1_PutChar('-');
	Uart1_PutChar('-');
	Uart1_PutChar(Sec/10+0x30);
	Uart1_PutChar(Sec%10+0x30);
	Uart1_PutChar(0xd);
	Uart1_PutChar(0xa);
    #endif 
}

/******************************************************************************* 
 * ��������: RTC_Configuration(*)
 * ��������: RTC����
 * ��    ��: WLB
 * �������: 
 * �������: 
 * �� �� ֵ: 
 * ����˵��: 
 * �޸���ʷ: 
 *           1. 2015-2-1  WLB  Created
 *******************************************************************************/
void RTC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
    {      
		//??o����?��������1?����?��
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP,ENABLE);
		PWR_BackupAccessCmd(ENABLE);				 	  //o����?����?a??
		BKP_DeInit();
		RCC_LSEConfig(RCC_LSE_ON);						  //�䨰?a��a2?�̨�?��?��??
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY)==RESET); //�̨���y��a2?�̨�?��?��??1�����?y3��
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);			  //��a2?�̨�?��?��??����?aRTC?��???��
		RCC_RTCCLKCmd(ENABLE);							  //��1?��RTC
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
		RTC_ITConfig(RTC_IT_SEC, ENABLE);				  // ��1?��RTC???D??
		RTC_WaitForLastTask();
		RTC_SetPrescaler(32767);						  //(32.768 KHz)/(32767+1)
		RTC_WaitForLastTask();
		
		/********��D1?NVIC��?����??2?��?****************/
	  	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
	  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  	NVIC_Init(&NVIC_InitStructure); 
		//????����3��o����??��o����???��??��?DD�䨬?��a��?��?0xA5A5
	    SetRtcTime(10,5,3,16,3,0);
		RTC_WaitForLastTask();
		BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
		RTC_WaitForLastTask();
    }
	 else
    {
		//��?o����???��??��??��D��?��?��??��?TD��??D?????RTC
        //?a��??��???����?��?��?RCC_GetFlagStatus()o����y2��?���?��??��??����D��
        if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)		//?a��?��?��??��??
        {
            GPIO_ResetBits(GPIOE,GPIO_Pin_4|GPIO_Pin_5);
			GPIO_SetBits(GPIOE,GPIO_Pin_2|GPIO_Pin_3);						
        }
        else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)	//?a��?��a2?RST1��???��??
        {
            GPIO_ResetBits(GPIOE,GPIO_Pin_2|GPIO_Pin_3);	  
			GPIO_SetBits(GPIOE,GPIO_Pin_4|GPIO_Pin_5);			
        }
        RCC_ClearFlag();//??3yRCC?D?��??����??
        //??��?RTC?��?��2?D����a??D?????��??����?��?o������??o����?��?3?������???DD
        //��?��???��?��?��?o����??1��?��a��1?��RTCCLK???????
        //RCC_RTCCLKCmd(ENABLE);
        //�̨���yRTC����?����?APB1����?����?2?
        RTC_WaitForSynchro();
        //��1?��???D??
        RTC_ITConfig(RTC_IT_SEC, ENABLE);
        //�̨���y2�����¨���3��
        RTC_WaitForLastTask();
		/********��D1?NVIC��?����??2?��?****************/
	  	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
	  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  	NVIC_Init(&NVIC_InitStructure);
    }

}

/*******************************************************************************
 *                                End of File                                  *
 *******************************************************************************/


