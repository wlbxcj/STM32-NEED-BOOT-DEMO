/*******************************************************************************
 *
 * �ļ�����: debug.c
 *
 * �ļ�����: �����ļ�
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
#define MAX_DUMP_PER_LINE	16
/******************************************************
**    ���ļ������ȫ�ֱ����ͺ�������                  *
*******************************************************/
#if DJ01_CHECK_ENABLE
uint8 g_ucPrintDebugFlag = 1;
#else
uint8 g_ucPrintDebugFlag = 3;
#endif
uint32 g_ulTaskDebugFlag = 0xffffffff;


/*******************************************************************************
 *��������: DBG_Print
 *��������: ����ӡ�ȼ���������˵Ĵ�ӡ����
         ע������g_ulTaskDebugFlag�õ��������ȼ����Ʋ�����
         ��ǰ������������ȼ�С��32������޸�OS_LOWEST_PRIOҪע��������Ӱ��
 *�������: ucPrintLevel ��ӡ�ȼ�
            fmt ��ʽ����ӡ����
 *�������: void
 *�� �� ֵ: void
 * 
 *�޸���ʷ:
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
    ulLen = vsnprintf(pBuf, PRINT_BUF_LEN, fmt, ap);    // ֧�ָ����������
    va_end(ap);
    
    Usart1_Write((uint8 *)pBuf, ulLen);

    OSMutexPost(g_MutexPrint);
#endif
    return;
}

/*******************************************************************************
 *��������: DBG_PrintBuf
 *��������: ����ӡ�ȼ���������˵��ڴ��ӡ���������ڴ��ֵ��ʽ�����
         ע������g_ulTaskDebugFlag�õ��������ȼ����Ʋ�����
         ��ǰ������������ȼ�С��32������޸�OS_LOWEST_PRIOҪע��������Ӱ��
 *�������: ucPrintLevel ��ӡ�ȼ�
         char *szPrompt: �Ƿ��ӡǰ�����ʾ��
         char *pData: ��ӡ������
         uint32 ulLen: ��ӡ�����ݳ���
 *�������: void
 *�� �� ֵ: void
 * 
 *�޸���ʷ:
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

