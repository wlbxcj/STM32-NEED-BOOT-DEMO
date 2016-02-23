/*******************************************************************************
 *
 * 文件名称: rtc.c
 *
 * 文件描述: RTC配置
 * 作    者: WLB
 * 创建时间: 2015-2-1
 * 文件版本: 
 * 修改历史: 
 *           1. 2015-2-1  WLB  Created
 *******************************************************************************/




/*******************************************************************************
 *                                  头文件包含                                 *
 *******************************************************************************/
#include    "config.h"

/*******************************************************************************
 *                          本文件定义的全局变量和函数声明                     *
 *******************************************************************************/


/*******************************************************************************
 *                             外部变量和函数声明                              *
 *******************************************************************************/

/*****************************************************
//函数名称：void SetRtcTime(u8 year,u8 month,u8 day,u8 hour,u8 min,u8 sec)
//功能描述：RTC初始值设定函数.
//输入参数：unsigned char year :设定年，如2010年，则year=10；
//          unsigned char moth：设定月，如11月，  则moth=11；
//          unsigned char day ：设定日期，如24日，则day=24；
//          unsigned char hour：设定小时，如16时，则hour=16；
//			unsigned char min ：设定分钟，如4分，则min=3；
//			unsigned char sec ：设定秒，如34秒，则为sec=34；
//返回：无
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
//函数名称：Read_RTC_Time
//功能描述：读取RTC寄存器值，并转换为年月日时分秒数据，通过串口传出
//输入参数：无
//返回：无
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
 * 函数名称: RTC_Configuration(*)
 * 功能描述: RTC配置
 * 作    者: WLB
 * 输入参数: 
 * 输出参数: 
 * 返 回 值: 
 * 其它说明: 
 * 修改历史: 
 *           1. 2015-2-1  WLB  Created
 *******************************************************************************/
void RTC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
    {      
		//??oó±?óòìá1?ê±?ó
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP,ENABLE);
		PWR_BackupAccessCmd(ENABLE);				 	  //oó±?óò?a??
		BKP_DeInit();
		RCC_LSEConfig(RCC_LSE_ON);						  //′ò?aía2?μí?μ?§??
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY)==RESET); //μè′yía2?μí?μ?§??1¤×÷?y3￡
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);			  //ía2?μí?μ?§??×÷?aRTC?§???′
		RCC_RTCCLKCmd(ENABLE);							  //ê1?üRTC
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
		RTC_ITConfig(RTC_IT_SEC, ENABLE);				  // ê1?üRTC???D??
		RTC_WaitForLastTask();
		RTC_SetPrescaler(32767);						  //(32.768 KHz)/(32767+1)
		RTC_WaitForLastTask();
		
		/********óD1?NVICμ?éè??2?·?****************/
	  	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
	  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  	NVIC_Init(&NVIC_InitStructure); 
		//????íê3éoó￡??òoó±???′??÷?DD′ì?êa×?·?0xA5A5
	    SetRtcTime(10,5,3,16,3,0);
		RTC_WaitForLastTask();
		BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
		RTC_WaitForLastTask();
    }
	 else
    {
		//è?oó±???′??÷??óDμ?μ?￡??ò?TDè??D?????RTC
        //?aà??ò???éò?à?ó?RCC_GetFlagStatus()oˉêy2é?′±?′??′??ààDí
        if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)		//?aê?é?μ??′??
        {
            GPIO_ResetBits(GPIOE,GPIO_Pin_4|GPIO_Pin_5);
			GPIO_SetBits(GPIOE,GPIO_Pin_2|GPIO_Pin_3);						
        }
        else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)	//?aê?ía2?RST1ü???′??
        {
            GPIO_ResetBits(GPIOE,GPIO_Pin_2|GPIO_Pin_3);	  
			GPIO_SetBits(GPIOE,GPIO_Pin_4|GPIO_Pin_5);			
        }
        RCC_ClearFlag();//??3yRCC?D?′??±ê??
        //??è?RTC?￡?é2?Dèòa??D?????￡??òμ?μ?oóòà??oó±?μ?3?òàè???DD
        //μ?ê???′?é?μ?oó￡??1ê?òaê1?üRTCCLK???????
        //RCC_RTCCLKCmd(ENABLE);
        //μè′yRTCê±?óó?APB1ê±?óí?2?
        RTC_WaitForSynchro();
        //ê1?ü???D??
        RTC_ITConfig(RTC_IT_SEC, ENABLE);
        //μè′y2ù×÷íê3é
        RTC_WaitForLastTask();
		/********óD1?NVICμ?éè??2?·?****************/
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


