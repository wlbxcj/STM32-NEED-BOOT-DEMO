/*******************************************************************************
 *
 * �ļ�����: lcd_app.h
 *
 * �ļ�����: LCD��ʾͷ�ļ�
 * ��    ��: WLB
 * ����ʱ��: 2015-2-11
 * �ļ��汾: 
 * �޸���ʷ: 
 *           1. 2015-2-11  WLB  Created
 *******************************************************************************/
#ifndef __LCD_APP_H__
#define __LCD_APP_H__

/*******************************************************************************
 *                                �궨��                                       *
 *******************************************************************************/
#define WIDTHBYTES(bits)    (((bits)+31)/32*4)		// ����24λ���ɫ ÿһ�е����ر�����4�ı���������0
#define RGB24TORGB16(R,G,B) ((uint16)((((R)>>3)<<11) | (((G)>>2)<<5)	| ((B)>>3)	))


#define GETR_FROM_RGB16(RGB565)  ((unsigned char)(( ((unsigned short int )RGB565) >>11)<<3))		  			//����??8?? R
#define GETG_FROM_RGB16(RGB565)  ((unsigned char)(( ((unsigned short int )(RGB565 & 0x7ff)) >>5)<<2)) 	//����??8?? G
#define GETB_FROM_RGB16(RGB565)  ((unsigned char)(( ((unsigned short int )(RGB565 & 0x1f))<<3)))       	//����??8?? B
// #pragma diag_suppress 870 	//��1������??��?��3??����??����?��?,��??��?����Dinvalid multibyte character sequence?��?? 

/*******************************************************************************
 *                               ��������                                      *
 *******************************************************************************/
//  0--1 ��??��?����????t����D��
//??��????t����D??��?��11?����?
//???D2?�㨹o????t����D��D??��ꡧ��������?��11��?��??����??��11???����?��a��??����?��??��??2??��?y����?����????tD??���?
typedef struct//	tagBITMAPFILEHEADER 
{
    
    DWORD bfSize; 									//???t�䨮D?																				4
    WORD bfReserved1; 								//���ꨢ?��?��?2?????		 															2
    WORD bfReserved2;								//���ꨢ?��?��?��?��?			 															2
    DWORD bfOffBits; 								//����?��??��?��y?Y��???��?��??����y��??��?�㨨y??2?��?3��?��??o��	4
} BITMAP_FILE_HD;//BITMAPFILEHEADER,tagBITMAPFILEHEADER;

// 14--53 ??��?D??�騪��
typedef struct //tagBITMAPINFOHEADER
{
    DWORD biSize; 									//???����??��11��?��?3��?����??a40		 												4
    LONG biWidth; 									//??��??��											 												4
    LONG biHeight; 									//??��???											 												4
    WORD biPlanes; 									//????��y��??a1								 													2
    WORD biBitCount; 								//2����???��???��y��??����?��?1��?2��?4��?8��?16��?24D?��??����?��?32	2
    DWORD biCompression; 							//?1??��?��?��??����?��?0��?1��?2��????D0������?2??1??						4
    DWORD biSizeImage; 								//����?��??��?��y?Y??��?��?��??����y														4
    LONG biXPelsPerMeter;							//X��??����?��??��																					4
    LONG biYPelsPerMeter; 							//Y��??����?��??��																					4
    DWORD biClrUsed; 								//��1��?��???��?��y��?��?1??a0��??��������???��??��(2^??��???��y)			4
    DWORD biClrImportant; 							//??��a??��?��y��?��?1??a0��??��������??����D??��???��???��a��?				4
}BITMAP_INF_HD ;//BITMAPINFOHEADER,tagBITMAPINFOHEADER;
  

typedef struct //tagRGBQUAD 
{

    BYTE rgbBlue; 													//????��?��?��?��?��?��?
    BYTE rgbGreen; 													//????��?��??����?��?��?
    BYTE rgbRed; 													//????��?��?o����?��?��?
    BYTE rgbReserved;											 	//���ꨢ??��
}RGB_AD;//RGBQUAD,tagRGBQUAD;


typedef struct //RGB_PIXEL
{      //????��?��y?Y����D��
    unsigned char   rgbBlue;
    unsigned char   rgbGreen;
    unsigned char   rgbRed;
}RGB_PIX;//RGB_PIXEL;


/*******************************************************************************
 *                              ȫ�ֱ�������                                   *
 *******************************************************************************/
extern void *LCDQueue[LCD_QUEUE_SIZE];

/*******************************************************************************
 *                              ȫ�ֺ���ԭ��                                   *
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

