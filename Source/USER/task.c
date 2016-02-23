/*******************************************************************************
 *
 * 文件名称: task.c
 *
 * 文件描述: 任务文件
 * 作    者: WLB
 * 创建时间: 2015-1-31
 * 文件版本: 
 * 修改历史: 
 *           1. 2015-1-31  WLB  Created
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
OS_EVENT *g_MutexPrint;

OS_EVENT *g_QLcdDisplay;



/******************************************************************************* 
 * 函数名称: Task_Led(*)
 * 功能描述: 流水灯任务
 * 作    者: WLB
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 * 其它说明: 无
 * 修改历史: 
 *           1. 2015-2-1  WLB  Created
 *******************************************************************************/
void Task_Led(void *p_arg)
{
    (void)p_arg;                		// 'p_arg' 并没有用到，防止编译器提示警告
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
 * 函数名称: Task_Lcd(*)
 * 功能描述: 显示任务
 * 作    者: WLB
 * 输入参数: void *p_arg
 * 输出参数: 无
 * 返 回 值: 无
 * 其它说明: 无
 * 修改历史: 
 *           1. 2015-2-1  WLB  Created
 *******************************************************************************/
void Task_Lcd(void *p_arg)
{
    uint16 i = 0;
    uint16 j = 320;
    INT8U err;
    uint8 *pucData = NULL;
    (void)p_arg;                		// 'p_arg' 并没有用到，防止编译器提示警告
    
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
 * 函数名称: Task_SdCard(*)
 * 功能描述: SD卡任务
 * 作    者: WLB
 * 输入参数: void *p_arg
 * 输出参数: 无
 * 返 回 值: 无
 * 其它说明: 无
 * 修改历史: 
 *           1. 2015-2-5  WLB  Created
 *******************************************************************************/
void Task_SdCard(void *p_arg)
{
    UINT bw = 0;
    uint8 *pucBuf = NULL;
    FRESULT eRes = FR_DISK_ERR;
    DIR dirs;
    FIL fsrc;
    char fname[50] = {0};                                   //长文件名最大长度
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
                        if(!stFileInfo.fname[0])				    /*为空，则表示读完 */
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
        	if (eRes == FR_OK )	// 将缓冲区的数据写到文件中 //
          	{ 
        	    eRes = f_write(&fsrc, "Just a test!!!", strlen("Just a test!!!"), &bw); 
        	  	DBG_Print(3, "Demo.TXT 文件创建成功\r\n", strlen("Demo.TXT 文件创建成功\r\n"));
        		f_close(&fsrc);	  //关闭文件 //			  
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
                    
                    f_close(&fsrc);	  //关闭文件 //	

                }
        		DBG_Print(3, "Demo.TXT 已经存在\r\n", strlen("Demo.TXT 已经存在\r\n"));
          	}
            TimeDlyms(2000);
        }
        
        TimeDlyms(2000);
    }
}

/*******************************************************************************
 *                                End of File                                  *
 *******************************************************************************/

