/*******************************************************************************
 *
 * 文件名称: tool.h
 *
 * 文件描述: 小工具
 * 作    者: WLB
 * 创建时间: 2015-2-1
 * 文件版本: 
 * 修改历史: 
 *           1. 2015-2-1  WLB  Created
 *******************************************************************************/
#ifndef __TOOL_H__
#define __TOOL_H__

#include "config.h"

//#include "funcsincos.h"
//#include "funcusqr.h"
//#include "funcdiv.h"

#define LEFT      0
#define RIGHT     1
#define NORMAL    2

#define GET_ARR_ELEMENTS_NUM(arr)    (sizeof(arr) / sizeof(arr[0]))

extern uint16 Crc16Calc(uint8 *p, uint16 len, uint16 r);

extern void TimeDlyms(uint32 ms);

extern void * OSMemGetEx(int size);
extern INT8U  OSMemPutEx(void *pblk);
extern uint32 mypow(uint32 a ,uint32 b);

extern void IpStrToHex(char *ipstring,char *iphex);

extern void PortStrToHex(char *PortStr,uint16 *pusPort);

extern void IpAddrToStr(char *pIpAddr, char *pStr);

extern void PortToStr(char *pPort, char *pStr);

extern uint32 gpsStringNum(const char* pSrc,int nSrcLength);

extern void gpsNumString(uint32 num,char* pDst,int leng,int mode);

extern void DecToAck2(uint8 number ,char * pSrc);

extern uint8 BcdToHex(uint8 Bcd);

extern uint8 HexToBcd(uint8 Hex);

extern uint32 EndianLittleToBig_int(uint32 ulData);

extern uint16 EndianLittleToBig_short(uint16 usData);

extern uint16 ByteToINT16(uint8 D0,uint8 D1);

extern uint32 ByteToINT32(uint8 D0,uint8 D1,uint8 D2,uint8 D3);

extern void ByteTo2DecChar(uint8 Data,uint8 *p);

extern void ByteTo3DecChar(uint8 Data,uint8 *p);

extern uint8 GetChkSum(uint8 *pData, uint32 len);

extern uint8 GetXorChkSum(uint8 *pResult, uint8 *pData, uint32 len);

extern char* memstr(char* pMem, const char* pStr, uint16 usLen);

extern uint8 CheckIpAddrValidity(char aucIpAddr[]);

extern uint8 CheckPortValidity(char aucPort[]);

extern uint8 CheckApnValidity(char aucApn[]);

extern uint8 CheckIpDomainValidity(char domainName[]);

#define CheckDomainStringValidity(pData)    CheckApnValidity(pData)

uint8 ASC2HEX(uint8 asc);

extern void DataEndingToBlank(uint8 *pData, uint32 ulLen);

extern void DataBlankToEnding(uint8 *pData, uint32 ulLen);

extern uint8 CheckSimNum(char *SimNo, uint32 ulLen);

//#include "..\StringCmd\StringCmd.h"


#endif

/*********************************************************************************
**                            End of File
*********************************************************************************/

