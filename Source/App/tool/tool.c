/*******************************************************************************
 *
 * �ļ�����: tool.c
 *
 * �ļ�����: һЩС����
 * ��    ��: WLB
 * ����ʱ��: 2015-2-1
 * �ļ��汾: 
 * �޸���ʷ: 
 *           1. 2015-2-1  WLB  Created
 *******************************************************************************/
#include  "config.h"

#if !__HW_CRC
// CRC-CCITT checkout -- ���
// genPoly = 0x1021, X^16+X^12+X^5+1
const uint16 gm_crc_ccitt_table[256] = { 
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7, 
    0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef, 
    0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6, 
    0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de, 
    0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485, 
    0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d, 
    0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4, 
    0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc, 
    0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823, 
    0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b, 
    0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12, 
    0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a, 
    0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41, 
    0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49, 
    0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70, 
    0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78, 
    0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f, 
    0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067, 
    0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e, 
    0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256, 
    0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d, 
    0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405, 
    0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c, 
    0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634, 
    0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab, 
    0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3, 
    0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a, 
    0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92, 
    0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9, 
    0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1, 
    0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8, 
    0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0 
};
#endif

/*******************************************************************************
 *��������: Crc16Calc
 *��������: ����CRC16ֵ
 *�������: uint8 *p:Դ����
         uint16 len: Դ���ݳ���
         uint16 r:У��ĳ�ʼֵ
 *�������: ��
 *�� �� ֵ: У����ֵ
 * 
 *�޸���ʷ:
 *        1. 2010-4-08,by jcb Created
 ******************************************************************************/
uint16 Crc16Calc(uint8 *p, uint16 len, uint16 r)
{
#if __HW_CRC
    r = CRC_CalcChecksum((void *)p, len, CRC_WR_8BIT, CRC_POLY_CRCCCITT);
    return r;
#else
	while (len--)
	{
		r = (r<<8) ^ gm_crc_ccitt_table[(r>>8) ^ *p++];
	}
	return r;
#endif	
}

/*****************************************************************
 *��������: TimeDlyms()
 *��������: ��������ȵ�ms��ʱ����
 *��    ��: 
 *�������: uint32 ms: ��ʱ��msֵ
 *�������: void
 *�� �� ֵ: void
 *
 *�޸���ʷ: 
 *  
*****************************************************************/
void TimeDlyms(uint32 ms)
{
    if (OSRunning)
    {
        OSTimeDly(ms / OSCLOCKTIME);
    }
    else
    {
        uint32 i;
        while (ms--)
        {
            for(i = 0; i < 10000; i++);
        }  
    }
    return;
}

/*****************************************************************
 *��������: OS_GetCurTaskPrio()
 *��������: ��ȡ��ǰ��������ȼ���������ID
 *��    ��: WLB
 *�������: void
 *�������: ����ID�����ȼ�
 *�� �� ֵ: void
 *
 *�޸���ʷ: 
 *        1.  2015-1-19   WLB   Created
*****************************************************************/

uint8 OS_GetCurTaskPrio(void)
{
    return OSPrioCur;
}

#if OS_MEM_AUTO_EN
/*****************************************************************
 *��������: OSMemGetEx()
 *��������: ϵͳ�ڴ����룬�������
 *��    ��: 
 *�������: OS_MEM * lpMem: �ڴ��
         int size: ����󽫴�СΪsize���ڴ��ʼ��
 *�������: void
 *�� �� ֵ: void
 *
 *�޸���ʷ: 
 *
*****************************************************************/
void *OSMemGetEx(int size)
{
    extern void *OSMalloc(int size, INT8U *perr);

    INT8U err;
    void *lpBlock;

    lpBlock = OSMalloc(size, &err);

    if (OS_ERR_MEM_NO_FREE_BLKS == err)
    {
        DBG_Print(LOG_LEVEL_ERR, "Warning:memNoFree(%d),taskid:%d\r\n", size, OS_GetCurTaskPrio());
    }

    if ((void *)0 == lpBlock)
    {
        return ((void *)0);
    }
    else
    {
        memset(lpBlock, 0, size);
        return lpBlock;
    }
}

/******************************************************************************* 
 * ��������: OSMemPutEx(*)
 * ��������: �Զ��ͷ��ڴ�
 * ��    ��: WLB
 * �������: void    *pblk������ʱ��ָ��
 * �������: �ɹ��ͷ� OS_ERR_NONE
 * �� �� ֵ: ��
 * ����˵��: ��
 * �޸���ʷ: 
 *           1. 2015-2-7  WLB  Created
 *******************************************************************************/
INT8U  OSMemPutEx(void *pblk)
{
    OS_MEM  *pmem = NULL;
#if OS_CRITICAL_METHOD == 3u                     /* Allocate storage for CPU status register           */
    OS_CPU_SR  cpu_sr = 0u;
#endif

#if (OS_MEM_AUTO_EN)
    INT16U i;
#endif

#if OS_ARG_CHK_EN > 0u
    if (pblk == (void *)0) {                     /* Must release a valid block                         */
        return (OS_ERR_MEM_INVALID_PBLK);
    }
#endif

#if (OS_MEM_AUTO_EN)
    OS_ENTER_CRITICAL();
    for (i = 0; i < OS_MAX_MEM_PART; i++)
    {
        if (OSMemTbl[i].OSMemAddr == (void *)0)
            continue;
        if ((pblk >= OSMemTbl[i].OSMemAddr)
             && (pblk < OSMemTbl[i].OSMemLast))
        {
            pmem = &OSMemTbl[i];
            break;
        }
    }
    OS_EXIT_CRITICAL();
    if (i == OS_MAX_MEM_PART)
    {
        return (OS_ERR_MEM_INVALID_PART);
    }
#endif

#if OS_ARG_CHK_EN > 0u
    if (pmem == (OS_MEM *)0) {                   /* Must point to a valid memory partition             */
        return (OS_ERR_MEM_INVALID_PMEM);
    }
    if (pblk == (void *)0) {                     /* Must release a valid block                         */
        return (OS_ERR_MEM_INVALID_PBLK);
    }
#endif
    OS_ENTER_CRITICAL();
    if (pmem->OSMemNFree >= pmem->OSMemNBlks) {  /* Make sure all blocks not already returned          */
        OS_EXIT_CRITICAL();
        return (OS_ERR_MEM_FULL);
    }
    *(void **)pblk      = pmem->OSMemFreeList;   /* Insert released block into free block list         */
    pmem->OSMemFreeList = pblk;
    pmem->OSMemNFree++;                          /* One more memory block in this partition            */
    OS_EXIT_CRITICAL();
    return (OS_ERR_NONE);                        /* Notify caller that memory block was released       */
}

#endif
/*******************************************************************************
 *��������: mypow
 *��������: ����a��b�η� 
 *�������: 
 *�������: 
 *�� �� ֵ: res = a^b
 * 
 *�޸���ʷ:
 *        1. 2010-4-08,by zhj Created
 ******************************************************************************/
uint32 mypow(uint32 a ,uint32 b)
{
    int i;
    uint32 res = 1;
    for(i = 0; i < b; i++)
    {
        res *= a;
    }
    return res;
}

/*****************************************************************
 *��������: IpStrToHex()
 *��������: ��ip�ַ���ַת��Ϊʮ�����Ƹ�ʽFF.FF.FF.FF
 *��    ��: JCB
 *�������: char *ipstring: ip��ַ,��ʽΪ220.231.142.91
 *�������: char *iphex: ת�����ip��ַ����ʽΪDC E7 8E 5B
 *�� �� ֵ: void
 *
 *�޸���ʷ: 
 *        1.  2010-6-12   JCB   Created
*****************************************************************/
void IpStrToHex(char *ipstring,char *iphex)
{
    uint32 tmp[4] = {0};
    sscanf(ipstring,"%d.%d.%d.%d", &tmp[0], &tmp[1], &tmp[2], &tmp[3]);
    iphex[0] = (uint8)tmp[0];
    iphex[1] = (uint8)tmp[1];
    iphex[2] = (uint8)tmp[2];
    iphex[3] = (uint8)tmp[3];
    return;
}

/*****************************************************************
 *��������: PortStrToHex()
 *��������: ���˿ں��ַ���ַת��Ϊʮ�����Ƹ�ʽ
 *��    ��: JCB
 *�������: char *PortStr: �˿ڣ��ַ���ʽ
 *�������: usPort: ת����Ķ˿�
 *�� �� ֵ: void
 *
 *�޸���ʷ: 
 *        1.  2010-6-12   JCB   Created
*****************************************************************/
void PortStrToHex(char *PortStr,uint16 *pusPort)
{
    uint32 tmp = 0;
    sscanf(PortStr,"%d", &tmp);
    *pusPort = (uint16)tmp;
    return;
}

/*****************************************************************
 *��������: IpAddrToStr()
 *��������: ����ַת��Ϊ�ַ���ʽ
 *��    ��: JCB
 *�������: char *pIpAddr: ip��ַ���ĸ��ֽڣ���λ��ǰ����λ�ں�
 *�������: char *pStr: ת�����ip�ַ�
 *�� �� ֵ: void
 *
 *�޸���ʷ: 
 *        1.  2010-6-12   JCB   Created
*****************************************************************/
void IpAddrToStr(char *pIpAddr, char *pStr)
{
    sprintf(pStr, "%d.%d.%d.%d", pIpAddr[0], pIpAddr[1], pIpAddr[2], pIpAddr[3]);
    return;
}

/*****************************************************************
 *��������: PortToStr()
 *��������: ���˿ں�ת��Ϊ�ַ���ʽ
 *��    ��: JCB
 *�������: char *pPort: �˿ںţ������ֽڣ���λ��ǰ����λ�ں�
 *�������: char *pStr: ת����Ķ˿��ַ�
 *�� �� ֵ: void
 *
 *�޸���ʷ: 
 *        1.  2010-6-12   JCB   Created
*****************************************************************/
void PortToStr(char *pPort, char *pStr)
{
    uint16 usPort = 0;
    usPort = ByteToINT16(pPort[0], pPort[1]);
    sprintf(pStr, "%d", usPort);
    return;
}

uint32 gpsStringNum(const char* pSrc,int nSrcLength)
{
    int    i;
    int    figNumber = 0;
    uint32    res = 0;
    
    for(i=0; (i<nSrcLength)&&(i<strlen(pSrc)); i++)
    {
        // �õ����ָ���
        if( (*(pSrc+i)>='0') && (*(pSrc+i)<='9') )
        {
            figNumber++;
        }
    }
    for(i=0;i<nSrcLength;i++)
    {
        if( (*(pSrc+i)>='0') && (*(pSrc+i)<='9') )
        {
            res += (*(pSrc+i)-'0') * mypow(10,--figNumber);   
        }
    }
    // ����ת���ɵ�10������
    return(res);
}
/*********************************************************************************
* ��������	: gpsNumString
* ��������	: ��10������ת�����ַ���
              : �磺294567 --> "294567"
* ��ڲ���	: num: 10������ 
              : pDst: ת�����ַ���
* ���ڲ���	: 
*********************************************************************************/
void gpsNumString(uint32 num,char* pDst,int leng,int mode)
{
    int    i;
	   uint32   ch;
    char   *__pDst = pDst;
    int    nSrcLength = 0;
 
    
    while(num/mypow(10,nSrcLength) > 0)
    {
        nSrcLength++;
    }
    if((mode==LEFT)&&(nSrcLength<leng))
    {
    	for(i=0;i<leng-nSrcLength;i++)
    	{
    		*__pDst = '0';
    		__pDst++;
    	}
    }
    for(i=0; i<nSrcLength; i++)
    {
        ch = (num/mypow(10,nSrcLength-1-i));
        num -= ch * mypow(10,nSrcLength-1-i);
       // ch = (char)ch + '0';
        *__pDst = (char)ch + '0';
        __pDst++;
    }
    if((mode==RIGHT)&&(nSrcLength<leng))
    {
    	for(i=0;i<leng-nSrcLength;i++)
    	{
    		*__pDst = '0';
    		__pDst++;
    	}
    }
    
}

/*******************************************************************************
 *��������: String2Bytes
 *��������: �ɴ�ӡ�ַ���ת��Ϊ�ֽ����� 
          : �磺"C8329BFD0E01" --> {0xC8, 0x32, 0x9B, 0xFD, 0x0E, 0x01}
 *�������: pSrc: Դ�ַ���ָ��,nSrcLength: Դ�ַ������� 
 *�������: pDst: Ŀ���ַ���ָ��
 *�� �� ֵ: Ŀ���ַ�������
 * 
 *�޸���ʷ:
 *        1. 2010-4-08,by zhj Created
 ******************************************************************************/
int String2Bytes(const char *pSrc, unsigned char *pDst, int nSrcLength)
{
    int i;
    for (i = 0; i < nSrcLength; i += 2)
    {
        // �����4λ
        if (*pSrc >= '0' && *pSrc <= '9')
        {
            *pDst = (char)((*pSrc - '0') << 4);
        }
        else if (*pSrc >= 'A' && *pSrc <= 'F')
        {
            *pDst = (char)((*pSrc - 'A' + 10) << 4);
        }
        else if (*pSrc >= 'a' && *pSrc <= 'f')
        {
            *pDst = (char)((*pSrc - 'a' + 10) << 4);
        }
    
        pSrc++;
    
        // �����4λ
        if (*pSrc >= '0' && *pSrc <= '9')
        {
            *pDst |= (char)(*pSrc - '0');
        }
        else if (*pSrc >= 'A' && *pSrc <= 'F')
        {
            *pDst |= (char)(*pSrc - 'A' + 10);
        }
        else if (*pSrc >= 'a' && *pSrc <= 'f')
        {
            *pDst |= (char)(*pSrc - 'a' + 10);
        }
        pSrc++;
        pDst++;
    }
    
    // ����Ŀ�����ݳ���
    return(nSrcLength / 2);
}

/*******************************************************************************
 *��������: Bytes2String
 *��������: �ֽ�����ת��Ϊ�ɴ�ӡ�ַ���
          : �磺{0xC8, 0x32, 0x9B, 0xFD, 0x0E, 0x01} --> "C8329BFD0E01" 
 *�������: pSrc: Դ�ַ���ָ�� nSrcLength: Դ�ַ�������
 *�������: pDst: Ŀ���ַ���ָ��
 *�� �� ֵ: Ŀ���ַ�������
 * 
 *�޸���ʷ:
 *        1. 2010-4-08,by zhj Created
 ******************************************************************************/
int Bytes2String(const unsigned char* pSrc, char* pDst, int nSrcLength)
{
    int i;
    const char tab[]="0123456789ABCDEF";    // 0x0-0xf���ַ����ұ�
    
    for(i=0; i<nSrcLength; i++)
    {
        // �����4λ
        *pDst++ = tab[*pSrc >> 4];
    
        // �����4λ
        *pDst++ = tab[*pSrc & 0x0f];
    
        pSrc++;
    }
    
    *pDst = '\0';
    
    return nSrcLength * 2;
}

#if __SMS > 0
/*********************************************************************************
* ��������	: DecToAck2
* ��������	: ��10��������0��255��ת��������ASCII�룬����20--"14"
* ��ڲ���	: 
*             : 
* ���ڲ���	: 
* ���ú���    ��
*********************************************************************************/
void DecToAck2(uint8 number ,char * pSrc)
{
    uint8 i = 0;
    
    i = number / 16;
    if (i <= 9) 
    {
        *pSrc = '0' + i;
    }  
    else if ((i > 9) && (i < 16))
    {
        i -= 10;
        *pSrc = 'A' + i;
    }   
    i = number % 16;
    if (i <= 9)
    {
        *(pSrc + 1) = '0' + i;
    }
    else if((i > 9) && (i < 16))
    {
        i -= 10;
        *(pSrc + 1) = 'A' + i;
    }
}

#endif



/*****************************************************************
 *��������: HexToBcd()
 *��������: ��һ�ֽ�С��100��ʮ�����Ʊ��һ�ֽ�ѹ����BCD��
 *��    ��: JCB
 *�������: uint8 Hex: ��ת����ʮ��������
 *�������: void
 *�� �� ֵ: ѹ��BCD�룬����0xff��ʾ����
 *
 *�޸���ʷ: 
 *        1.  2010-3-19   JCB   Created
*****************************************************************/
uint8 HexToBcd(uint8 Hex)
{
    uint8 Bcd;
    if (99 < Hex)
    {
        return 0xff;
    }
    Bcd = Hex / 10;
    Bcd <<= 4;
    Bcd |= Hex % 10;
    return Bcd;
}

/*****************************************************************
 *��������: BcdToHex()
 *��������: ��һ�ֽ�С��100��һ�ֽ�ѹ����BCD����ʮ������
 *��    ��: JCB
 *�������: uint8 Bcd: ��ת����ѹ����BCD��
 *�������: void
 *�� �� ֵ: ʮ��������������0xff��ʾ����
 *
 *�޸���ʷ: 
 *        1.  2010-3-19   JCB   Created
*****************************************************************/
uint8 BcdToHex(uint8 Bcd)
{
    uint8 HH,HL;
    HH = Bcd >> 4;
    HL = Bcd & 0x0f;
    if ((9 < HH) || (9 < HL))
    {
        return 0xff;
    }
    return (HH * 10 + HL);
}
#if 0
/*****************************************************************
 *��������: EndianLittleToBig_int()
 *��������: int ��ʽ�����ݴ�С��ģʽ�ĳɴ��ģʽ
 *��    ��: JCB
 *�������: uint32 ulData: Ҫת���Ĳ���
 *�������: ���ת�����ֵ
 *�� �� ֵ: void
 *
 *�޸���ʷ: 
 *        1.  2010-3-19   JCB   Created
*****************************************************************/
uint32 EndianLittleToBig_int(uint32 ulData)
{
    DATA_UINT32_UN unData;
    DATA_UINT32_UN unData2;

    unData.ulValue=0;
    unData2.ulValue=0;

    unData.ulValue = ulData;
    unData2.szBuf[0] = unData.szBuf[3];
    unData2.szBuf[1] = unData.szBuf[2];
    unData2.szBuf[2] = unData.szBuf[1];
    unData2.szBuf[3] = unData.szBuf[0];

    return unData2.ulValue;
}

/*****************************************************************
 *��������: EndianLittleToBig_short()
 *��������: short ��ʽ�����ݴ�С��ģʽ�ĳɴ��ģʽ
 *��    ��: JCB
 *�������: uint16 usData: Ҫת���Ĳ���
 *�������: ���ת�����ֵ
 *�� �� ֵ: void
 *
 *�޸���ʷ: 
 *        1.  2010-3-19   JCB   Created
*****************************************************************/
uint16 EndianLittleToBig_short(uint16 usData)
{
	uint32 num = 0;
	num = (usData >> 8) + ((usData & 0xff) << 8); 
	return num;
}
#endif

/*****************************************************************
 *��������: ByteToINT16()
 *��������: ��2�ֽںϲ�Ϊһ��˫�ֽ�
 *��    ��: JCB
 *�������: ԭʼ2�����ֽ��������ֽ���ǰ�����ֽ��ں�
 *�������: void
 *�� �� ֵ: �ϲ����˫�ֽ�
 *
 *�޸���ʷ: 
 *        1.  2010-3-19   JCB   Created
*****************************************************************/
uint16 ByteToINT16(uint8 D0,uint8 D1)
{
    uint16 H,L;
    H = D0;
    L = D1;
    return((H << 8) | L);
}

/*****************************************************************
 *��������: ByteToINT32()
 *��������: ��4�����ֽںϲ�Ϊ���ͱ���
 *��    ��: JCB
 *�������: ԭʼ4�����ֽ��������ֽ���ǰ�����ֽ��ں�
 *�������: void
 *�� �� ֵ: �ϲ���ĳ��ͱ���
 *
 *�޸���ʷ: 
 *        1.  2010-3-19   JCB   Created
*****************************************************************/
uint32 ByteToINT32(uint8 D0,uint8 D1,uint8 D2,uint8 D3)
{
    uint32 H,M1,M2,L;
    H  = D0;
    M1 = D1;
    M2 = D2;
    L  = D3;
    return((H << 24) | (M1 << 16) | (M2 << 8) | L);
}

void CopyWord(uint8 *pBuf,uint16 word)
{
    if (pBuf == NULL)
        return;
    
    *pBuf++ = (word&0xFF00)>>8;
    *pBuf   = word&0xFF;
}


void CopyDword(uint8 *pBuf,uint32 dword)
{
    if (pBuf == NULL)
        return ;

    *pBuf++ = (dword&0xFF000000)>>24;
    *pBuf++ = (dword&0x00FF0000)>>16;
    *pBuf++ = (dword&0x0000FF00)>>8;
    *pBuf   =  dword&0x000000FF;
}

/*****************************************************************
 *��������: ByteTo2DecChar()
 *��������: ��һ�ֽ�С��100������ת���ɶ��ֽ�ʮ�����ַ�
 *��    ��: JCB
 *�������: ��ת�������ݣ��ַ�ָ��
 *�������: ת�����ֵ
 *�� �� ֵ: void
 *
 *�޸���ʷ: 
 *        1.  2010-3-19   JCB   Created
*****************************************************************/
void ByteTo2DecChar(uint8 Data,uint8 *p)
{
    *(p + 0) = Data % 100 / 10 + '0';
    *(p + 1) = Data % 10 + '0';
    return;
}

/*****************************************************************
 *��������: ByteTo3DecChar()
 *��������: ��һ�ֽ�ʮ�����Ƶ�����ת�������ֽ�ʮ�����ַ�
 *��    ��: JCB
 *�������: ��ת�������ݣ��ַ�ָ��
 *�������: ת�����ֵ
 *�� �� ֵ: void
 *
 *�޸���ʷ: 
 *        1.  2010-3-19   JCB   Created
*****************************************************************/
void ByteTo3DecChar(uint8 Data,uint8 *p)
{
	*p = Data / 100 + '0';
	*(p + 1) = Data % 100 / 10 + '0';
	*(p + 2) = Data % 10 + '0';
}

/*****************************************************************
 *��������: GetChkSum()
 *��������: ��ȡ�����ۼӺ�
 *��    ��: JCB
 *�������: uint8 *pData: �����������ָ��
         uint32 len: ���ݳ���
 *�������: ��
 *�� �� ֵ: һ���ֽڵ��ۼӺ�
 *
 *�޸���ʷ: 
 *        1.  2010-3-19   JCB   Created
*****************************************************************/
uint8 GetChkSum(uint8 *pData, uint32 len)
{
    uint8 result = 0;
    while (len--)
    {
        result += *pData++;
    }
    return result;
}

/*****************************************************************
 *��������: GetChkSum()
 *��������: ��ȡ�������У���
 *��    ��: JCB
 *�������: uint8 *pData: �����������ָ��
         uint32 len: ���ݳ���
 *�������: ��
 *�� �� ֵ: һ���ֽڵ����У���
 *
 *�޸���ʷ: 
 *        1.  2010-3-19   JCB   Created
*****************************************************************/
uint8 GetXorChkSum(uint8 *pResult, uint8 *pData, uint32 len)
{
    while (len--)
    {
        *pResult ^= *pData++;
    }
    return *pResult;
}

/*****************************************************************
 *��������: memstr()
 *��������: �Ӹ������ȵ��ڴ�������һ���ַ�����
 *          �˺�����⺯��strstr������: ����������'\0'����ֹͣ������
 *��    ��: LYP
 *�������: char* pMem:   �������ڴ��ָ��
 *          uint16 usLen: �������ڴ�����ݳ���
 *          char* pStr:   �������ַ��ܵ�ָ��
 *�������: ��
 *�� �� ֵ: ������ָ���ַ���������ָ����ַ�����ָ�룻û��������������NULL��
 *
 *�޸���ʷ: 
 *        1.  2013-2-4   LYP   Created
*****************************************************************/
char* memstr(char* pMem, const char* pStr, uint16 usLen)
{
    char*   pSrch;                  // ��ǰ�����ڴ��ָ��
    uint16  usSrchLen;              // ��ǰ�����ڴ�ĳ���
    char*   pChr;                   // ��ǰ�ڴ�����ƥ���ַ������ַ���ƥ���ָ��
    uint16  usStrLen;               // ƥ���ַ����ĳ���

    if (pMem == NULL || pStr == NULL)
    {
        return NULL;
    }
    usSrchLen = usLen;                                  // ��ʼ��������Ϊ�����������ڴ�ĳ���
    usStrLen = strlen(pStr);
    if (usSrchLen == 0 || usStrLen == 0)
    {
        return NULL;
    }
    pSrch = pMem;
    while (usSrchLen >= usStrLen)
    {
        pChr = memchr(pSrch, *pStr, usSrchLen);         // ������һ��ƥ����ַ�
        if (pChr == NULL)
        {
            return NULL;                                // û��������ƥ���ַ�
        }
        usSrchLen = pSrch + usSrchLen - pChr;
        pSrch = pChr;
        if (usSrchLen < usStrLen)
        {
            return NULL;                                // ƥ���ַ���������ݲ���ָ���ַ�������
        }
        if (memcmp(pSrch, pStr, usStrLen) == 0)         // ƥ�������ַ���
        {
            return pSrch;
        }
        pSrch += 1;
        usSrchLen -= 1;
    }
    return NULL;
}

/*****************************************************************
 *��������: CheckIpAddrValidity()
 *��������: ���˿ڵĺϷ���
 *��    ��: csm
 *�������: char aucIpAddr: ��Ҫ����IP��ַ
 *�������: void
 *�� �� ֵ: �Ϸ����� TRUE �Ƿ�����:FALSE
 *
 *�޸���ʷ: 
 *        1.  2011-12-21   csm   Created
*****************************************************************/
uint8 CheckIpAddrValidity(char aucIpAddr[])
{
    uint32  ulIpLen = 0;
    uint32  ulDotCnt = 0;
    uint32  i = 0;
    char    ucChar = 0;
    int     szIp[4] = {256,256,256,256};

    ulIpLen = strlen(aucIpAddr);
    if ((ulIpLen > 15) || (ulIpLen < 7)) /* IP��ַ��ʽ 255.255.255.255���ַ������ȴ���15��С��7 IP��ַ��ʽ���� */
    {
        return FALSE;
    }
    
    for (i = 0; i < ulIpLen; i++)        /* ɨ��IP��ַ�������ַ�����Ϊ '0'��'9' �� '.' */
    {
        ucChar = aucIpAddr[i];
        if (ucChar == '.')
        {
            ulDotCnt++;
        }
        else if ((ucChar > '9') || (ucChar < '0'))
        {
            return FALSE;
        }
    }
    
    if (3 != ulDotCnt)                   /* ɨ�赽 '.' ��С�ڲ�����3 ����FALSE */
    {
        return FALSE;
    }

    sscanf(aucIpAddr, "%d.%d.%d.%d", &szIp[0], &szIp[1], &szIp[2], &szIp[3]);
    for (i = 0; i < 4; i++)
    {
        if (szIp[i] > 255 || (szIp[i] < 0))
        {
            return FALSE;
        }
    }
    
    return TRUE;
}

/*****************************************************************
 *��������: CheckIpDomainValidity()
 *��������: ��������ĺϷ���
 *��    ��: csm
 *�������: char aucIpAddr: ��Ҫ����IP����
 *�������: 
 *�� �� ֵ: �Ϸ����� TRUE �Ƿ�����:FALSE
 *
 *�޸���ʷ: 
 *        1.  2011-12-21   csm   Created
*****************************************************************/
uint8 CheckIpDomainValidity(char domainName[])
{
    uint32 ulIpLen = 0;
    uint32 i;

    ulIpLen = strlen(domainName);
    if ((ulIpLen > 32) || (3 > ulIpLen))
    {
        return FALSE;
    }
#if 0
    if (!((domainName[0]=='h')&&(domainName[1]=='t')&&(domainName[2]=='t')&&(domainName[3]=='p')&&(domainName[4]==':')))
    {

        DEBUG_PRINT(LOG_LEVEL_ERR, "Invalid domain name\r\n");            
        return FALSE;
    }
#endif    
    for (i = 0; i < ulIpLen; i++)
    {
        if ((domainName[i] < 0x20) || (domainName[i] >= 0x7F))
        {
            return FALSE;
        }
    }
    return TRUE;
}

/*****************************************************************
 *��������: CheckPortValidity()
 *��������: ���˿ڵĺϷ���
 *��    ��: csm
 *�������: char aucPort: ��Ҫ���Ķ˿�
 *�������: void
 *�� �� ֵ: �Ϸ����� TRUE �Ƿ�����:FALSE
 *
 *�޸���ʷ: 
 *        1.  2011-12-21   csm   Created
*****************************************************************/
uint8 CheckPortValidity(char aucPort[])
{
    uint32  ulLen = 0;
    uint32  i = 0;
    char    ucChar = 0;
    uint32  Port = 0;

    /* �ж϶˿��Ƿ�Ϸ� */
    ulLen = strlen(aucPort);
    if ((ulLen > 5) || (ulLen == 0))  /* �˿���ֵ��Χ�� 0 �� 65535 */
    {
        return FALSE;
    }
    
    for (i = 0; i < ulLen; i++)
    {
        ucChar = aucPort[i];
        if ((ucChar > '9') || (ucChar < '0'))
        {
            return FALSE;
        }
    }

    Port = atoi(aucPort);
    if ((Port > 65535) || (Port == 0))
    {
        return FALSE;
    }
    return TRUE;
}

/*****************************************************************
 *��������: CheckApnValidity()
 *��������: ���APN�ĺϷ���:1,����С��32,
            2,����Ϊ�ɴ�ӡ�ַ����������ո��DEL
 *��    ��: csm
 *�������: char *pApnStr: ��Ҫ����APN��ַ
 *�������: void
 *�� �� ֵ: �Ϸ����� TRUE �Ƿ�����:FALSE
 *
 *�޸���ʷ: 
 *        1.  2011-12-21   csm   Created
*****************************************************************/
uint8 CheckApnValidity(char aucApn[])
{
    uint32  ulApnLen = 0;
    uint32  i = 0;
    char    ucChar = 0;

    ulApnLen = strlen(aucApn);
    if ((ulApnLen < 1) || (ulApnLen >= 32))
    {
        return FALSE;
    }
    
    for (i = 0; i < ulApnLen; i++)
    {
        ucChar = aucApn[i];
        if ((ucChar < 0x20) || (ucChar >= 0x7F))
        {
            return FALSE;
        }
    }
    
    return TRUE;
}

/*****************************************************************
 *��������: DataEndingToBlank()
 *��������: �����ݽ������ֲ������ַ�ת��Ϊ�ո�
 *��    ��: jcb
 *�������: uint8 *pData:��ת��������
         uint32 ulLen:��ת�������ݳ���
 *�������: void
 *�� �� ֵ: void
 *
 *�޸���ʷ: 
 *         1. 2012-09-18,by jcb Created
*****************************************************************/
void DataEndingToBlank(uint8 *pData, uint32 ulLen)
{
    uint32 i;
    for (i = 0; i < ulLen; i++)
    {
        if (' ' > pData[i])
        {
            pData[i] = ' ';
        }
    }
    return;
}

/*****************************************************************
 *��������: DataBlankToEnding()
 *��������: �����ݽ������ֵĿո�ת��Ϊ0x00
 *��    ��: jcb
 *�������: uint8 *pData:��ת��������
         uint32 ulLen:��ת�������ݳ���
 *�������: void
 *�� �� ֵ: void
 *
 *�޸���ʷ: 
 *         1. 2012-09-18,by jcb Created
*****************************************************************/
void DataBlankToEnding(uint8 *pData, uint32 ulLen)
{
    uint32 ulPos = ulLen;
    while (ulPos--)
    {
        if (' ' == pData[ulPos])
        {
            pData[ulPos] = 0x00;
        }
        else
        {
            break;
        }
    }
    return;
}

/*****************************************************************
 *��������: ASC2HEX
 *��������: ��ASCIIת����16��������
 *��    ��: LYC
 *�������: uint8 asc:��ת��������
 *�������: void
 *�� �� ֵ: 16����ֵ��
 *
 *�޸���ʷ: 
 *         1. 2013-02-16,by LYC Created
*****************************************************************/
uint8 ASC2HEX(uint8 asc)
{
    if ((asc >= '0') && (asc <= '9'))
    {
        return asc - '0';
    }
    else if ((asc >= 'A') && (asc <= 'F'))
    {
        return asc - 'A' + 10;
    }
    else if ((asc >= 'a') && (asc <= 'f'))
    {
        return asc - 'a' + 10;
    }
    return 0;
}

/*****************************************************************
 *��������: CheckSimNum
 *��������: ����ַ����ǲ��Ǵ�����
 *��    ��: chenyue
 *�������: �ַ������ַ�������
 *�������: void
 *�� �� ֵ: true/false
 *
 *�޸���ʷ: 
 *         1. 2013-11-20,by chenyue Created
*****************************************************************/
uint8 CheckSimNum(char *SimNo, uint32 ulLen)
{
    uint32 ulNum;

    for (ulNum = 0; ulNum < ulLen; ulNum++)
    {
        if ('0' > SimNo[ulNum])
        {
            return FALSE;
        }
        else if ('9' < SimNo[ulNum])
        {
            return FALSE;
        }
    }

    return TRUE;
}

//#include "..\StringCmd\StringCmd.c"

/*********************************************************************************
**                            End of File
*********************************************************************************/

