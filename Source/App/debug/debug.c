/*******************************************************************************
 *
 * 文件名称: debug.c
 *
 * 文件描述: 调试文件
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
#define MAX_DUMP_PER_LINE	16
/******************************************************
**    本文件定义的全局变量和函数声明                  *
*******************************************************/
#if DJ01_CHECK_ENABLE
uint8 g_ucPrintDebugFlag = 1;
#else
uint8 g_ucPrintDebugFlag = 3;
#endif
uint32 g_ulTaskDebugFlag = 0xffffffff;


/*******************************************************************************
 *函数名称: DBG_Print
 *函数功能: 按打印等级和任务过滤的打印函数
         注意这里g_ulTaskDebugFlag用到任务优先级左移操作，
         其前提是任务的优先级小于32，因此修改OS_LOWEST_PRIO要注意对这里的影响
 *输入参数: ucPrintLevel 打印等级
            fmt 格式化打印参数
 *输出参数: void
 *返 回 值: void
 * 
 *修改历史:
 ******************************************************************************/
void DBG_Print(uint8 ucPrintLevel,const char *fmt,...)
{
#if (1)//(DEBUG_PRINT_EN)

    #define PRINT_BUF_LEN   1024
    static  uint32 g_szDebugPrintBuf[PRINT_BUF_LEN / 4 + 1] = {0};
    char   *pBuf = (char *)g_szDebugPrintBuf;
    uint32  ulLen;
    va_list ap;
    uint8   err;

    if (ucPrintLevel > g_ucPrintDebugFlag)
    {
        return;
    }

    //if (!(g_ulTaskDebugFlag & (1u << CPU_GetCurTaskPrio())))
    //{
    //    return;
    //
    //}

    OSMutexPend(g_MutexPrint,0,&err);

    memset(pBuf, 0, sizeof(g_szDebugPrintBuf));
    va_start(ap,fmt);
    //ulLen = _vsnprintf(pBuf, PRINT_BUF_LEN, fmt, ap);
    ulLen = vsnprintf(pBuf, PRINT_BUF_LEN, fmt, ap);    // 支持浮点数据输出
    va_end(ap);
    
    Usart1_Write((uint8 *)pBuf, ulLen);

    OSMutexPost(g_MutexPrint);
#endif
    return;
}

/*******************************************************************************
 *函数名称: DBG_PrintBuf
 *函数功能: 按打印等级和任务过滤的内存打印函数，将内存的值格式化输出
         注意这里g_ulTaskDebugFlag用到任务优先级左移操作，
         其前提是任务的优先级小于32，因此修改OS_LOWEST_PRIO要注意对这里的影响
 *输入参数: ucPrintLevel 打印等级
         char *szPrompt: 是否打印前面的提示符
         char *pData: 打印的内容
         uint32 ulLen: 打印的数据长度
 *输出参数: void
 *返 回 值: void
 * 
 *修改历史:
 ******************************************************************************/
void DBG_PrintBuf(uint8 ucPrintLevel, char *szPrompt, char *pData, uint32 ulLen)
{
#if 1
    uint32 i;
    static char szDbgBuf[64];
    char *ptr = szDbgBuf;

    if ((NULL == pData) || (0 == ulLen))
    {
        return;
    }

    if (ucPrintLevel > g_ucPrintDebugFlag)
    {
        return;
    }

    if (!(g_ulTaskDebugFlag & (1u << OS_GetCurTaskPrio())))
    {
        return;
    }

    if (NULL != szPrompt)
    {
        DBG_Print(ucPrintLevel, "\r\n%s\r\n", szPrompt);
    }

    for (i = 1; i <= ulLen; i++)
    {
        ptr += snprintf(ptr,sizeof(szDbgBuf), "%02X ", *pData);
        pData++;

        if (0 == i % MAX_DUMP_PER_LINE)
        {
            *ptr = 0;
            DBG_Print(ucPrintLevel, "%s\r\n", szDbgBuf);
            ptr = szDbgBuf;
        }
    }
    if (ulLen % MAX_DUMP_PER_LINE)
    {
        *ptr = 0;
        DBG_Print(ucPrintLevel, "%s\r\n", szDbgBuf);
    }
#endif
    return;
}


/*********************************************************************************
**                            End of File
*********************************************************************************/

