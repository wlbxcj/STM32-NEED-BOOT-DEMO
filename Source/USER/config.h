/*******************************************************************************
 *
 * �ļ�����: config.h
 *
 * �ļ�����: �����ļ�
 * ��    ��: WLB
 * ����ʱ��: 2015-1-30
 * �ļ��汾: 
 * �޸���ʷ: 
 *           1. 2015-1-30  WLB  Created
 *******************************************************************************/
#ifndef __CONFIG_H__
#define __CONFIG_H__

/*******************************************************************************
 *                                �궨��                                       *
 *******************************************************************************/
/* ---�汾��ض���--- */
#ifndef TRUE
#define TRUE    1
#endif

#ifndef FALSE
#define FALSE   0
#endif

#ifndef NULL
#define NULL    (void *)0
#endif

#define     OSCLOCKTIME                     10                      // 1s = 100 system ticks




#define     VERSION_MAX_LEN                 (32)

#define     BOOT_BASE                       (FLASH_BASE + 0x0000)    /* boot��ʼλ�� */
#define     BOOT_END                        (FLASH_BASE + 0x5FFF)    /* boot����λ�� */
#define     BOOT_FLAG_ADDR                  (FLASH_BASE + 0x1100)    /* boot��־���λ�� */
#define     BOOT_FLAG                       "ST01-BOOT-"             /* BOOT��־ */
#define     BOOT_FLAG_MAX_LEN               (10)                     /* boot��־��ų��� */
#define     BOOT_VER_ADDR                   (FLASH_BASE + 0x110A)    /* boot�汾�Ŵ��λ�� */
#define     BOOT_VER_MAX_LEN                (32)                     /* boot�汾��ų��� */
#define     APP_MAX_LEN                     (0x70000)
#define     VERSION_BASE                    (FLASH_BASE + 0x6000)    /* �汾��ʼλ�ã�28k */
#define     VERSION_END                     (FLASH_BASE + 0x7a000)   /* �汾����λ�ã�256k */
#define     VERSION_STR_ADDR                (FLASH_BASE + 0x6200)    /* �汾�Ŵ��λ�� */

#define     APP_VERSION                     "ST01-150130-V1.0.4"
#define     BOOT_VERSION                    "BOOT-V1.0.0"

/*******************************************************************************
 *                               ��������                                      *
 *******************************************************************************/


/*******************************************************************************
 *                              ȫ�ֱ�������                                   *
 *******************************************************************************/
// OS Memory
#define     SMALL64MEMNUM                   16
#define     SMALLMEMNUM                     8
#define     MEDIUMMEMNUM                    8
#define     LARGEMEMNUM                     7

#define     SMALL64MEMSIZE                  64
#define     SMALLMEMSIZE                    256
#define     MEDIUMMEMSIZE                   512
#define     LARGEMEMSIZE                    1152

#define     SMALL64_MEM_SIZE                (SMALL64MEMNUM * SMALL64MEMSIZE)
#define     SMALL_MEM_SIZE                  (SMALLMEMNUM * SMALLMEMSIZE)
#define     MEDIUM_MEM_SIZE                 (MEDIUMMEMNUM * MEDIUMMEMSIZE)
#define     LARGE_MEM_SIZE                  (LARGEMEMNUM * LARGEMEMSIZE)

#define     LCD_QUEUE_SIZE                  16          // ��ʾ����


/*******************************************************************************
 *                              ȫ�ֺ���ԭ��                                   *
 *******************************************************************************/

/********************************************************************************
 *                              typedef
 *******************************************************************************/


typedef unsigned char       bool;           // defined for boolean variable ��������
typedef unsigned char       uint8;          // defined for unsigned 8-bits integer variable �޷���8λ���ͱ���
typedef signed   char       int8;           // defined for signed 8-bits integer variable �з���8λ���ͱ���
typedef unsigned short      uint16;         // defined for unsigned 16-bits integer variable �޷���16λ���ͱ���
typedef signed   short      int16;          // defined for signed 16-bits integer variable �з���16λ���ͱ���
typedef unsigned int        uint32;         // defined for unsigned 32-bits integer variable �޷���32λ���ͱ���
typedef signed   int        int32;          // defined for signed 32-bits integer variable �з���32λ���ͱ���
typedef float               fp32;           // single precision floating point variable (32bits) �����ȸ�������32λ���ȣ�
typedef double              fp64;           // double precision floating point variable (64bits) ˫���ȸ�������64λ���ȣ�
typedef unsigned long long  ulong64;        // 64-bit unsigned integer           // ע��: ��ӡʱʹ��%lld
typedef signed   long long  long64;         // 64-bit signed integer

typedef volatile unsigned char  VU08;   /*unsigned 8 bit definition */
typedef volatile unsigned int   VU16;   /*unsigned 16 bit definition*/
typedef volatile unsigned long  VU32;   /*unsigned 32 bit definition*/
typedef volatile signed char    VS08;   /*signed 8 bit definition */
typedef volatile signed int     VS16;   /*signed 16 bit definition*/
typedef volatile signed long    VS32;   /*signed 32 bit definition*/

/* These types must be 16-bit, 32-bit or larger integer */
typedef int				INT;
typedef unsigned int	UINT;

/* These types must be 8-bit integer */
typedef char			CHAR;
typedef unsigned char	UCHAR;
typedef unsigned char	BYTE;

/* These types must be 16-bit integer */
typedef short			SHORT;
typedef unsigned short	USHORT;
typedef unsigned short	WORD;
typedef unsigned short	WCHAR;

/* These types must be 32-bit integer */
typedef long			LONG;
typedef unsigned long	ULONG;
typedef unsigned long	DWORD;

#include    "includes.h"
#endif
/*******************************************************************************
 *                                End of File                                  *
 *******************************************************************************/

