/*******************************************************************************
 *
 * �ļ�����: global.c
 *
 * �ļ�����: ȫ�ֱ�������
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
volatile uint32 g_ulBootSecTime = 0;

/*******************************************************************************
 *                             �ⲿ�����ͺ�������                              *
 *******************************************************************************/
OS_MEM *ptrPlatctlMEM;
OS_MEM *ptrGpsMEM;
OS_MEM *ptrSmall64MEM;
OS_MEM *ptrSmallMEM;
OS_MEM *ptrMediumMEM;
OS_MEM *ptrLargeMEM;





FATFS fs[2] = {0};            // Work area (file system object) for logical drive


/*******************************************************************************
 *                                End of File                                  *
 *******************************************************************************/
