/*******************************************************************************
 *
 * 文件名称: config.h
 *
 * 文件描述: 配置文件
 * 作    者: WLB
 * 创建时间: 2015-1-30
 * 文件版本: 
 * 修改历史: 
 *           1. 2015-1-30  WLB  Created
 *******************************************************************************/
#ifndef __CONFIG_H__
#define __CONFIG_H__

/*******************************************************************************
 *                                宏定义                                       *
 *******************************************************************************/
/* ---版本相关定义--- */
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

#define     BOOT_BASE                       (FLASH_BASE + 0x0000)    /* boot开始位置 */
#define     BOOT_END                        (FLASH_BASE + 0x5FFF)    /* boot结束位置 */
#define     BOOT_FLAG_ADDR                  (FLASH_BASE + 0x1100)    /* boot标志存放位置 */
#define     BOOT_FLAG                       "ST01-BOOT-"             /* BOOT标志 */
#define     BOOT_FLAG_MAX_LEN               (10)                     /* boot标志存放长度 */
#define     BOOT_VER_ADDR                   (FLASH_BASE + 0x110A)    /* boot版本号存放位置 */
#define     BOOT_VER_MAX_LEN                (32)                     /* boot版本存放长度 */
#define     APP_MAX_LEN                     (0x70000)
#define     VERSION_BASE                    (FLASH_BASE + 0x6000)    /* 版本开始位置，28k */
#define     VERSION_END                     (FLASH_BASE + 0x7a000)   /* 版本结束位置，256k */
#define     VERSION_STR_ADDR                (FLASH_BASE + 0x6200)    /* 版本号存放位置 */

#define     APP_VERSION                     "ST01-150130-V1.0.4"
#define     BOOT_VERSION                    "BOOT-V1.0.0"

/*******************************************************************************
 *                               数据类型                                      *
 *******************************************************************************/


/*******************************************************************************
 *                              全局变量声明                                   *
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

#define     LCD_QUEUE_SIZE                  16          // 显示队列


/*******************************************************************************
 *                              全局函数原型                                   *
 *******************************************************************************/

/********************************************************************************
 *                              typedef
 *******************************************************************************/


typedef unsigned char       bool;           // defined for boolean variable 布尔变量
typedef unsigned char       uint8;          // defined for unsigned 8-bits integer variable 无符号8位整型变量
typedef signed   char       int8;           // defined for signed 8-bits integer variable 有符号8位整型变量
typedef unsigned short      uint16;         // defined for unsigned 16-bits integer variable 无符号16位整型变量
typedef signed   short      int16;          // defined for signed 16-bits integer variable 有符号16位整型变量
typedef unsigned int        uint32;         // defined for unsigned 32-bits integer variable 无符号32位整型变量
typedef signed   int        int32;          // defined for signed 32-bits integer variable 有符号32位整型变量
typedef float               fp32;           // single precision floating point variable (32bits) 单精度浮点数（32位长度）
typedef double              fp64;           // double precision floating point variable (64bits) 双精度浮点数（64位长度）
typedef unsigned long long  ulong64;        // 64-bit unsigned integer           // 注意: 打印时使用%lld
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

