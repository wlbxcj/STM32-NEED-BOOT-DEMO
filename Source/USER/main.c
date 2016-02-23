/*******************************************************************************
 *
 * 文件名称: main.c
 *
 * 文件描述: 主文件
 * 作    者: WLB
 * 创建时间: 2015-1-30
 * 文件版本: 
 * 修改历史: 
 *           1. 2015-1-30  WLB  Created
 *******************************************************************************/

/*******************************************************************************
 *                                  头文件包含                                 *
 *******************************************************************************/
#include "config.h"

/*******************************************************************************
 *                          本文件定义的全局变量和函数声明                     *
 *******************************************************************************/
__align(8) static OS_STK Startup_Task_Stk[STARTUP_TASK_STK_SIZE];
__align(8) static OS_STK Led_Task_Stk[LCD_TASK_STK_SIZE];
__align(8) static OS_STK Lcd_Task_Stk[LCD_TASK_STK_SIZE];
__align(8) static OS_STK Sdcard_Task_Stk[SDCARD_TASK_STK_SIZE];



__align(8) uint8 g_aucSmall64Mem[SMALL64_MEM_SIZE]  = {0};
__align(8) uint8 g_aucSmallMem[SMALL_MEM_SIZE]      = {0};
__align(8) uint8 g_aucMediumMem[MEDIUM_MEM_SIZE]    = {0};
__align(8) uint8 g_aucLargeMem[LARGE_MEM_SIZE]      = {0};

uint8 const g_aucAppVersion[VERSION_MAX_LEN] __attribute__ ((at(VERSION_STR_ADDR))) = {APP_VERSION};


/*****************************************************************
 *函数名称: AppMemCreate()
 *函数功能: 创建内存块
 *作    者: wlb
 *输入参数: void
 *输出参数: void
 *返 回 值: void
 *
 *修改历史:
 *        1. 2014-10-20 wlb     Created
*****************************************************************/
static void AppMemCreate(void)
{
    INT8U err;
    /* 分配内存块，必须保证申请成功，创建的内存要按照大小创建 */
    do
    {
        ptrSmall64MEM= OSMemCreate((void*)g_aucSmall64Mem, SMALL64MEMNUM, SMALL64MEMSIZE, &err);
        ptrSmallMEM  = OSMemCreate((void*)g_aucSmallMem, SMALLMEMNUM, SMALLMEMSIZE, &err);
        ptrMediumMEM = OSMemCreate((void*)g_aucMediumMem, MEDIUMMEMNUM, MEDIUMMEMSIZE, &err);
        ptrLargeMEM  = OSMemCreate((void*)g_aucLargeMem, LARGEMEMNUM, LARGEMEMSIZE, &err);
    }
    while (ptrSmallMEM == NULL || ptrMediumMEM == NULL || ptrLargeMEM == NULL);

    return;
}

static void AppEventCreate(void)
{
    INT8U err;

    g_MutexPrint        = OSMutexCreate(PIPPRINT, &err);

    g_QLcdDisplay       = OSQCreate(LCDQueue, LCD_QUEUE_SIZE);

}
/******************************************************************************* 
 * 函数名称: AppTaskCreate(*)
 * 功能描述: 任务创建
 * 作    者: WLB
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 无
 * 其它说明: 无
 * 修改历史: 
 *           1. 2015-2-1  WLB  Created
 *******************************************************************************/
static void AppTaskCreate(void)
{
    OSTaskCreateExt((void (*)(void *)) Task_Led,
                    (void           *) 0,
                    (OS_STK         *)&Led_Task_Stk[LED_TASK_STK_SIZE - 1],
                    (INT8U           ) LED_TASK_PRIO,
                    (INT16U          ) LED_TASK_PRIO,
                    (OS_STK         *)&Led_Task_Stk[0],
                    (INT32U          ) LED_TASK_STK_SIZE,
                    (void           *) 0,
                    (INT16U          )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

    OSTaskCreateExt((void (*)(void *)) Task_Lcd,
                    (void           *) 0,
                    (OS_STK         *)&Lcd_Task_Stk[LCD_TASK_STK_SIZE - 1],
                    (INT8U           ) LCD_TASK_PRIO,
                    (INT16U          ) LCD_TASK_PRIO,
                    (OS_STK         *)&Lcd_Task_Stk[0],
                    (INT32U          ) LCD_TASK_STK_SIZE,
                    (void           *) 0,
                    (INT16U          )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
    #if 1
    OSTaskCreateExt((void (*)(void *)) Task_SdCard,
                    (void           *) 0,
                    (OS_STK         *)&Sdcard_Task_Stk[SDCARD_TASK_STK_SIZE - 1],
                    (INT8U           ) SDCARD_TASK_PRIO,
                    (INT16U          ) SDCARD_TASK_PRIO,
                    (OS_STK         *)&Sdcard_Task_Stk[0],
                    (INT32U          ) SDCARD_TASK_STK_SIZE,
                    (void           *) 0,
                    (INT16U          )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
    #endif
    return;
}


/******************************************************************************* 
 * 函数名称: TASK_AppStart(*)
 * 功能描述: 创建任务
 * 作    者: WLB
 * 输入参数: void *pArg
 * 输出参数: 无
 * 返 回 值: 无
 * 其它说明: 无
 * 修改历史: 
 *           1. 2015-2-1  WLB  Created
 *******************************************************************************/
void TASK_AppStart(void *pArg)
{
    (void)pArg;
    SysTick_init();
    AppEventCreate();
    AppMemCreate();

    
    AppTaskCreate();
    while (TRUE)
    {
        TimeDlyms(10000);

    }
}



int main(void)
{
	BSP_Init();
	OSInit();
#if 0
	OSTaskCreate(Task_Led,
	            (void *)0,
	            &startup_task_stk[STARTUP_TASK_STK_SIZE - 1],
	            STARTUP_TASK_PRIO);
#else
	OSTaskCreateExt((void (*)(void *))  TASK_AppStart,
                    (void            *) 0,
                    (OS_STK          *) &Startup_Task_Stk[STARTUP_TASK_STK_SIZE - 1],
                    (INT8U            ) STARTUP_TASK_PRIO,
                    (INT16U           ) STARTUP_TASK_PRIO,
                    (OS_STK          *) &Startup_Task_Stk[0],
                    (INT32U           ) STARTUP_TASK_STK_SIZE,
                    (void            *) 0,
                    (INT16U           ) (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
#endif
	OSStart();
    return 0;
 }

/*******************************************************************************
 *                                End of File                                  *
 *******************************************************************************/
