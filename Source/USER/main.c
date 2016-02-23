/*******************************************************************************
 *
 * �ļ�����: main.c
 *
 * �ļ�����: ���ļ�
 * ��    ��: WLB
 * ����ʱ��: 2015-2-30
 * �ļ��汾: 
 * �޸���ʷ: 
 *           1. 2015-3-30  WLB  Created
 *******************************************************************************/

/*******************************************************************************
 *                                  ͷ�ļ�����                                 *
 *******************************************************************************/
#include "config.h"

/*******************************************************************************
 *                          ���ļ������ȫ�ֱ����ͺ�������                     *
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
 *��������: AppMemCreate()
 *��������: �����ڴ��
 *��    ��: wlb
 *�������: void
 *�������: void
 *�� �� ֵ: void
 *
 *�޸���ʷ:
 *        1. 2014-10-20 wlb     Created
*****************************************************************/
static void AppMemCreate(void)
{
    INT8U err;
    /* �����ڴ�飬���뱣֤����ɹ����������ڴ�Ҫ���մ�С���� */
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
 * ��������: AppTaskCreate(*)
 * ��������: ���񴴽�
 * ��    ��: WLB
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 * ����˵��: ��
 * �޸���ʷ: 
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
 * ��������: TASK_AppStart(*)
 * ��������: ��������
 * ��    ��: WLB
 * �������: void *pArg
 * �������: ��
 * �� �� ֵ: ��
 * ����˵��: ��
 * �޸���ʷ: 
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
