/*******************************************************************************
 *
 * 文件名称: lcd_app.h
 *
 * 文件描述: LCD显示头文件
 * 作    者: WLB
 * 创建时间: 2015-2-11
 * 文件版本: 
 * 修改历史: 
 *           1. 2015-2-11  WLB  Created
 *******************************************************************************/
#ifndef __LCD_APP_H__
#define __LCD_APP_H__

/*******************************************************************************
 *                                宏定义                                       *
 *******************************************************************************/
#define WIDTHBYTES(bits)    (((bits)+31)/32*4)		// 对于24位真彩色 每一行的像素必须是4的倍数，否则补0
#define RGB24TORGB16(R,G,B) ((uint16)((((R)>>3)<<11) | (((G)>>2)<<5)	| ((B)>>3)	))


#define GETR_FROM_RGB16(RGB565)  ((unsigned char)(( ((unsigned short int )RGB565) >>11)<<3))		  			//·μ??8?? R
#define GETG_FROM_RGB16(RGB565)  ((unsigned char)(( ((unsigned short int )(RGB565 & 0x7ff)) >>5)<<2)) 	//·μ??8?? G
#define GETB_FROM_RGB16(RGB565)  ((unsigned char)(( ((unsigned short int )(RGB565 & 0x1f))<<3)))       	//·μ??8?? B
// #pragma diag_suppress 870 	//ê1±àò??÷?§3??à×??ú×?·?,·??ò?áóDinvalid multibyte character sequence?ˉ?? 

/*******************************************************************************
 *                               数据类型                                      *
 *******************************************************************************/
//  0--1 ×??ú?èê????tààDí
//??í????tí·D??￠?á11?¨ò?
//???D2?°üo????tààDíD??￠￡¨óéóú?á11ì?μ??ú′??á11???¨￡?òaê??óá?μ??°??2??ü?yè·?áè????tD??￠￡?
typedef struct//	tagBITMAPFILEHEADER 
{
    
    DWORD bfSize; 									//???t′óD?																				4
    WORD bfReserved1; 								//±￡á?×?￡?2?????		 															2
    WORD bfReserved2;								//±￡á?×?￡?í?é?			 															2
    DWORD bfOffBits; 								//êμ?ê??í?êy?Yμ???ò?×??úêy￡??′?°èy??2?·?3¤?è??oí	4
} BITMAP_FILE_HD;//BITMAPFILEHEADER,tagBITMAPFILEHEADER;

// 14--53 ??í?D??￠í·
typedef struct //tagBITMAPINFOHEADER
{
    DWORD biSize; 									//???¨′??á11ì?μ?3¤?è￡??a40		 												4
    LONG biWidth; 									//??í??í											 												4
    LONG biHeight; 									//??í???											 												4
    WORD biPlanes; 									//????êy￡??a1								 													2
    WORD biBitCount; 								//2éó???é???êy￡??éò?ê?1￡?2￡?4￡?8￡?16￡?24D?μ??éò?ê?32	2
    DWORD biCompression; 							//?1??·?ê?￡??éò?ê?0￡?1￡?2￡????D0±íê?2??1??						4
    DWORD biSizeImage; 								//êμ?ê??í?êy?Y??ó?μ?×??úêy														4
    LONG biXPelsPerMeter;							//X·??ò·?±??ê																					4
    LONG biYPelsPerMeter; 							//Y·??ò·?±??ê																					4
    DWORD biClrUsed; 								//ê1ó?μ???é?êy￡?è?1??a0￡??ò±íê???è??μ(2^??é???êy)			4
    DWORD biClrImportant; 							//??òa??é?êy￡?è?1??a0￡??ò±íê??ùóD??é???ê???òaμ?				4
}BITMAP_INF_HD ;//BITMAPINFOHEADER,tagBITMAPINFOHEADER;
  

typedef struct //tagRGBQUAD 
{

    BYTE rgbBlue; 													//????é?μ?à?é?·?á?
    BYTE rgbGreen; 													//????é?μ??ìé?·?á?
    BYTE rgbRed; 													//????é?μ?oìé?·?á?
    BYTE rgbReserved;											 	//±￡á??μ
}RGB_AD;//RGBQUAD,tagRGBQUAD;


typedef struct //RGB_PIXEL
{      //????μ?êy?YààDí
    unsigned char   rgbBlue;
    unsigned char   rgbGreen;
    unsigned char   rgbRed;
}RGB_PIX;//RGB_PIXEL;


/*******************************************************************************
 *                              全局变量声明                                   *
 *******************************************************************************/
extern void *LCDQueue[LCD_QUEUE_SIZE];

/*******************************************************************************
 *                              全局函数原型                                   *
 *******************************************************************************/

void LCD_Put_AC_string(u16 x, u16  y, u8 *s, u16 fColor,u16 bColor);
void Lcd_show_bmp(uint16 x, uint16 y, uint8 *pic_name);
//int write_bmp(RGB_PIXEL *pixarr, int xsize, int ysize, char *filename);
int write_bmp(RGB_PIX *pixarr, int xsize, int ysize, char *filename);
int write_bmp2(unsigned char  *pixarr, int xsize, int ysize, char *filename);
int write_bmp3(unsigned char  *pixarr, int xsize, int ysize, char *filename);
int Screen_shot(unsigned short int x, unsigned short int y, unsigned short int Width, unsigned short int Height, unsigned char *filename);

#endif

/*******************************************************************************
 *                                End of File                                  *
 *******************************************************************************/

