/*******************************************************************************
 *
 * �ļ�����: task.c
 *
 * �ļ�����: �����ļ�
 * ��    ��: WLB
 * ����ʱ��: 2015-1-31
 * �ļ��汾: 
 * �޸���ʷ: 
 *           1. 2015-1-31  WLB  Created
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
OS_EVENT *g_MutexPrint;

OS_EVENT *g_QLcdDisplay;



/******************************************************************************* 
 * ��������: Task_Led(*)
 * ��������: ��ˮ������
 * ��    ��: WLB
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 * ����˵��: ��
 * �޸���ʷ: 
 *           1. 2015-2-1  WLB  Created
 *******************************************************************************/
void Task_Led(void *p_arg)
{
    (void)p_arg;                		// 'p_arg' ��û���õ�����ֹ��������ʾ����
    while (1)
    {
        LED0( ON );
        OSTimeDlyHMSM(0, 0,0,100);
        LED0( OFF);
		
		LED1( ON );
        OSTimeDlyHMSM(0, 0,0,200);
        LED1( OFF);
        
        LED2( ON );
        OSTimeDlyHMSM(0, 0, 0,300);
        LED2( OFF);
        
        LED3( ON );
        OSTimeDlyHMSM(0, 0,0,500);
        LED3( OFF);
    }
}

/******************************************************************************* 
 * ��������: Task_Lcd(*)
 * ��������: ��ʾ����
 * ��    ��: WLB
 * �������: void *p_arg
 * �������: ��
 * �� �� ֵ: ��
 * ����˵��: ��
 * �޸���ʷ: 
 *           1. 2015-2-1  WLB  Created
 *******************************************************************************/
void Task_Lcd(void *p_arg)
{
    uint16 i = 0;
    uint16 j = 320;
    INT8U err;
    uint8 *pucData = NULL;
    (void)p_arg;                		// 'p_arg' ��û���õ�����ֹ��������ʾ����
    
    while (1)
    {
        pucData = (uint8 *)OSQPend(g_QLcdDisplay, 0, &err);
        if (OS_ERR_NONE == err)
        {
            #if 0
            if (j <= i)
            {
                i = 0;
                LCD_MyInit(0);
            }
            #endif
            if (NULL != strstr((char *)pucData, ".bmp"))
            {
                LCD_MyInit(0);
                Lcd_show_bmp(0, 0, pucData);
                TimeDlyms(200);
            }
            else
            {
                LCD_Put_AC_string(0, i, pucData, Red, Black);
            }
            
            //i += 16;
            OSMemPutEx(pucData);
        }
    }
}

/******************************************************************************* 
 * ��������: Task_SdCard(*)
 * ��������: SD������
 * ��    ��: WLB
 * �������: void *p_arg
 * �������: ��
 * �� �� ֵ: ��
 * ����˵��: ��
 * �޸���ʷ: 
 *           1. 2015-2-5  WLB  Created
 *******************************************************************************/
void Task_SdCard(void *p_arg)
{
    UINT bw = 0;
    uint8 *pucBuf = NULL;
    FRESULT eRes = FR_DISK_ERR;
    DIR dirs;
    FIL fsrc;
    char fname[50] = {0};                                   //���ļ�����󳤶�
    uint8 *pucMusicName = NULL;
    (void)p_arg;
   
    while (1)
    {
        eRes = f_mount(0, &fs[0]);
    #if 1
        DBG_Print(3, "f_mount:%d \r\n", eRes);
        if (eRes == FR_OK )
        {
            FILINFO stFileInfo;
            char path[50] = {""};
            stFileInfo.lfsize = 50;
            stFileInfo.lfname = fname;
            eRes = f_opendir(&dirs, path);
            if (eRes == FR_OK)
            {
                while (f_readdir(&dirs, &stFileInfo) == FR_OK)
                {
                    if (stFileInfo.fattrib & AM_ARC )
                    {
                        if(!stFileInfo.fname[0])				    /*Ϊ�գ����ʾ���� */
                        {
                            break;
                        }
                        while (NULL == (pucMusicName = OSMemGetEx(strlen(stFileInfo.lfname))))
                        {
                            TimeDlyms(100);
                        }
                        if (NULL != pucMusicName)
                        {
                            strcpy((char *)pucMusicName, stFileInfo.lfname);
                            OSQPost(g_QLcdDisplay, pucMusicName);
                        }

                        DBG_Print(3, "The file lfname   is: %s\r\n", stFileInfo.lfname);
                        DBG_Print(3, "The file fsize    is: %d\r\n", stFileInfo.fsize);
                        DBG_Print(3, "The file fdate    is: %d\r\n", stFileInfo.fdate);
                        DBG_Print(3, "The file ftime    is: %d\r\n", stFileInfo.ftime);
                        DBG_Print(3, "The file fattrib  is: 0x%X\r\n", stFileInfo.fattrib);
                        DBG_Print(3, "The file fname    is: %s\r\n", stFileInfo.fname);
                        TimeDlyms(300);
                        if (NULL != strstr(stFileInfo.lfname, ".BMP"))
                        {
                            TimeDlyms(1200);
                        }
                    }
                }
            }
            else
            {
                DBG_Print(3, "f_opendir err: %d \r\n", eRes);
            }
        }
    #endif       
        if (eRes == FR_OK )
        {
    	    eRes = f_open(&fsrc, "0:/Demo234.TXT" , FA_CREATE_NEW|FA_WRITE); 	
        	if (eRes == FR_OK )	// ��������������д���ļ��� //
          	{ 
        	    eRes = f_write(&fsrc, "Just a test!!!", strlen("Just a test!!!"), &bw); 
        	  	DBG_Print(3, "Demo.TXT �ļ������ɹ�\r\n", strlen("Demo.TXT �ļ������ɹ�\r\n"));
        		f_close(&fsrc);	  //�ر��ļ� //			  
            }
          	else if ( eRes == FR_EXIST )
          	{
          	    eRes = f_open(&fsrc, "0:/Demo234.TXT" , FA_READ); 
                    
                if (eRes == FR_OK)
                {
                    
                    DBG_Print(3, "file size is: %d \r\n", fsrc.fsize);
                    pucBuf = OSMemGetEx(fsrc.fsize);
                    if (NULL != pucBuf)
                    {
                        f_read(&fsrc, pucBuf, fsrc.fsize, &bw);
                        DBG_Print(3, "FILE:%s\r\n", pucBuf);
                        OSMemPutEx(pucBuf);
                        pucBuf = NULL;
                    }
                    
                    f_close(&fsrc);	  //�ر��ļ� //	

                }
        		DBG_Print(3, "Demo.TXT �Ѿ�����\r\n", strlen("Demo.TXT �Ѿ�����\r\n"));
          	}
            TimeDlyms(2000);
        }
        
        TimeDlyms(2000);
    }
}

/*******************************************************************************
 *                                End of File                                  *
 *******************************************************************************/

