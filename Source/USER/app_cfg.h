#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__


/*******************设置任务优先级*******************/
#define STARTUP_TASK_PRIO           3	   
#define LED_TASK_PRIO               12	   
#define LCD_TASK_PRIO               8
#define SDCARD_TASK_PRIO            11


/************设置栈大小（单位为 OS_STK ）************/
#define STARTUP_TASK_STK_SIZE       128   
#define LED_TASK_STK_SIZE           128   
#define LCD_TASK_STK_SIZE           200
#define SDCARD_TASK_STK_SIZE        400

/*
********************************************************************************
*                               MUTUAL EXCLUSION SEMAPHORE PRIORITIES
********************************************************************************
*/

#define     PIPMODEM                5
#define     PIPIIC                  6
#define     PIPPRINT                7
#define     PIPSPI1                 8
#define     PIPAREAROUTE            9



#endif

