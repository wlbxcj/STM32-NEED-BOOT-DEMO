/*******************************************************************************
 *
 * �ļ�����: lcd_app.c
 *
 * �ļ�����: LCD��ʾ�ļ�
 * ��    ��: WLB
 * ����ʱ��: 2015-2-11
 * �ļ��汾: 
 * �޸���ʷ: 
 *           1. 2015-2-11  WLB  Created
 *******************************************************************************/




/*******************************************************************************
 *                                  ͷ�ļ�����                                 *
 *******************************************************************************/
#include    "config.h"

/*******************************************************************************
 *                          ���ļ������ȫ�ֱ����ͺ�������                     *
 *******************************************************************************/
void *LCDQueue[LCD_QUEUE_SIZE];


/*******************************************************************************
 *                             �ⲿ�����ͺ�������                              *
 *******************************************************************************/
extern uint8 char_or_word;

/*******************************************************************************
* Function Name  : GetGBKCode_from_sd
* Description    : �䨮SD?����??a?D?����?��??t��y?Y��????����??o3??? 
* Input          : pBuffer---��y?Y�����?��??��  
*				   					c--oo��?��?��?�̨���??��?? 
* Output         : None
* Return         : 0(success)  -1(fail)
* Attention		 	 : None
*******************************************************************************/ 
int GetGBKCode_from_sd(unsigned char* pBuffer,unsigned char * c)
{ 
    unsigned char High8bit,Low8bit;
    unsigned int pos;
    uint8 myres = 0;
    uint32 mybr = 0;
    FIL fp;
        
    High8bit=*c;     /* ��???8??��y?Y */
    Low8bit=*(c+1);  /* ��?�̨�8??��y?Y */
    //myres = f_mount(1, &fs[1]);
    pos = ((High8bit - 0xb0) * 94 + Low8bit - 0xa1) * 2 * 16 ;	
    myres = f_open(&fp, "0:/HZLIB.bin", FA_OPEN_EXISTING | FA_READ);
    if (myres == FR_OK) 
    {
        f_lseek (&fp, pos);								//??????��?
        myres = f_read(&fp, pBuffer, 32, &mybr );		 //16*16�䨮D?��?oo��? ??��??�� ??��?16*2??��??��
        f_close(&fp);
        return 0;  
    }
    else
    {
        DBG_Print(LOG_LEVEL_INFO, "my res = %d!\r\n", myres);
        return -1; 
    }   
}

/******************************************************************************
* Function Name  : PutChinese22
* Description    : ??Lcd?����?��?��a??????��?��????D??��?
* Input          : - Xpos: ????��?���� 
*                  - Ypos: ��1?����?����  
*				   - str: ??��?��??D??��?
*				   - Color: ��?��???��?   
*				   - mode: ?�꨺?????		0--��3?�㨦??a�����?   1--??��?D��??
* Output         : None
* Return         : None
* example		 : PutChinese2(200,100,"??",0,1);
* Attention		 : ?��2?�̡¨�?
*******************************************************************************/
void PutChinese22(u16 x,u16 y,u8 *str,u16 fColor,u16 bColor) //����?��
{
    
    
    u8 i,j;
    u8 buffer[32];
    unsigned short m;
    //Set_direction(1);																		
    GetGBKCode_from_sd(buffer,str); /* ��?��??�꨺y?Y */
    char_or_word=1;		//����???a??��?oo��?��??a0?��?a??��?��?��?
	LCD_SetPos(x,y);
    for(i=0;i<32;i++) 
	{											
	  	m=buffer[i];
		for(j=0;j<8;j++) 
	  	{
			if((m&0x80)==0x80) 
				LCD_WR_DATA(fColor);		 //?a��?D�䨨?oo��???��?
			else 
				LCD_WR_DATA(bColor);		 //?a��?D�䨨?��3?��??��?
			m<<=1;
		} 
	}    
}

/*************************************************************
*	o����y??3?:LCD_Put_AC_string(u16 x, u16  y, u8 *s, u16 fColor,u16 bColor)
*	1|    ?��:??��?��?��?
*	2?    ��y:
*				x:  ��㨬??DX��?����?D??D???
*	 		 	y:  ��㨬??DY��?����?D??D???
*				s��o��y??��?��?��?��?
*				fColor:��?��???��?
*				bColor:��3?��??��? 
*	���� ?? ?��:?T
*	?��	  ?�¡�oASCII?����??��?���䨮C???t?����?��?oo��??����?�䨮SD��??����??��
*************************************************************/
void LCD_Put_AC_string(u16 x, u16  y, u8 *s, u16 fColor,u16 bColor)
{
	u16 Tmp_x, Tmp_y;
    u8 *tmp_str=s;

    Tmp_x = x;
    Tmp_y = y;
	while(*tmp_str!='\0')
	{
		if( *tmp_str< 0x80) 								 //?D??��?��??a��?��?
		{
			LCD_PutChar(Tmp_x,Tmp_y,*tmp_str,fColor,bColor);
			tmp_str++;
			Tmp_x+=8;
		}
		else
		{
			PutChinese22(Tmp_x,Tmp_y,tmp_str,fColor,bColor);
			tmp_str+=2;
			Tmp_x+=16;
		}
	}
}


/******************************************************************************* 
 * ��������: bmp(*)
 * ��������: ����ͼƬҪ��ʾ��λ�ü���С
 * ��    ��: WLB
 * �������: u16 x, u16 y, u16 width, u16 height
 * �������: ��
 * �� �� ֵ: ��
 * ����˵��: ��
 * �޸���ʷ: 
 *           1. 2015-2-12  WLB  Created
 *******************************************************************************/
void bmp(u16 x, u16 y, u16 width, u16 height)
{    
    LCD_Set_Ver(0);
	///////////////////////////////////////////////
	LCD_WR_CMD(0x0044,((width+x-1)<<8)+x); 
	LCD_WR_CMD(0x004e,x);        //����??X��??��3?��??��
		
	/*R45?��R46   ��1?����??����??e?��?1��?*/
	LCD_WR_CMD(0x0045,y);	  
	LCD_WR_CMD(0x0046,height+y-1);
	LCD_WR_CMD(0x004f,y);        //����??y��??��3?��??�� 
	
	LCD_WR_ADD(0X22);     
}

/******************************************************************************* 
 * ��������: showBmpHead(*)
 * ��������: ��ʾͼƬ��Ϣ
 * ��    ��: WLB
 * �������: BITMAP_FILE_HD* pBmpHead
 * �������: ��
 * �� �� ֵ: ��
 * ����˵��: ��
 * �޸���ʷ: 
 *           1. 2015-2-12  WLB  Created
 *******************************************************************************/
void showBmpHead(BITMAP_FILE_HD* pBmpHead)
{
    DBG_Print(LOG_LEVEL_INFO, "λͼ�ļ�ͷ   :\r\n");
    DBG_Print(LOG_LEVEL_INFO, "�ļ���С     :%d\r\n", (*pBmpHead).bfSize);
    DBG_Print(LOG_LEVEL_INFO, "������       :%d\r\n", (*pBmpHead).bfReserved1);
    DBG_Print(LOG_LEVEL_INFO, "������       :%d\r\n", (*pBmpHead).bfReserved2);
    DBG_Print(LOG_LEVEL_INFO, "ʵ��λͼ���ݵ�ƫ���ֽ���:%d\r\n", (*pBmpHead).bfOffBits);    
}

/******************************************************************************* 
 * ��������: showBmpInforHead(*)
 * ��������: ��ӡBMPͼƬͷ��Ϣ
 * ��    ��: WLB
 * �������: BITMAP_INF_HD* pBmpInforHead
 * �������: ��
 * �� �� ֵ: ��
 * ����˵��: ��
 * �޸���ʷ: 
 *           1. 2015-2-12  WLB  Created
 *******************************************************************************/
void showBmpInforHead(BITMAP_INF_HD* pBmpInforHead)
{
    DBG_Print(LOG_LEVEL_INFO, "λͼ��Ϣͷ               :\r\n");
    DBG_Print(LOG_LEVEL_INFO, "�ṹ��ĳ���             :%d\r\n", (*pBmpInforHead).biSize);
    DBG_Print(LOG_LEVEL_INFO, "λͼ��                   :%d\r\n", (*pBmpInforHead).biWidth);
    DBG_Print(LOG_LEVEL_INFO, "λͼ��                   :%d\r\n", (*pBmpInforHead).biHeight);
    DBG_Print(LOG_LEVEL_INFO, "biPlanesƽ����           :%d\r\n", (*pBmpInforHead).biPlanes);
    DBG_Print(LOG_LEVEL_INFO, "biBitCount������ɫλ��   :%d\r\n", (*pBmpInforHead).biBitCount);
    DBG_Print(LOG_LEVEL_INFO, "ѹ����ʽ                 :%d\r\n", (*pBmpInforHead).biCompression);
    DBG_Print(LOG_LEVEL_INFO, "biSizeImageʵ��λͼ����սʤ���ֽ���:%d\r\n", (*pBmpInforHead).biSizeImage);
    DBG_Print(LOG_LEVEL_INFO, "X����ֱ���              :%d\r\n", (*pBmpInforHead).biXPelsPerMeter);
    DBG_Print(LOG_LEVEL_INFO, "Y����ֱ���              :%d\r\n", (*pBmpInforHead).biYPelsPerMeter);
    DBG_Print(LOG_LEVEL_INFO, "ʹ�õ���ɫ��             :%d\r\n", (*pBmpInforHead).biClrUsed);
    DBG_Print(LOG_LEVEL_INFO, "��Ҫ��ɫ��               :%d\r\n", (*pBmpInforHead).biClrImportant);
}
/******************************************************************************* 
 * ��������: Lcd_show_bmp(*)
 * ��������: LCD��ʾRGB888ͼƬ
 * ��    ��: WLB
 * �������: 
 * �������: 
 * �� �� ֵ: 
 * ����˵��: ͼƬΪ24���ɫɫλͼƬ
 * �޸���ʷ: 
 *           1. 2015-2-12  WLB  Created
 *******************************************************************************/
void Lcd_show_bmp(uint16 x, uint16 y, uint8 *pic_name)
{
    int i, j, k;
    int width, height, l_width;
	uint32 ulPostion = 0;	  
    BYTE red,green,blue;
    BITMAP_FILE_HD bitHead;
    BITMAP_INF_HD bitInfoHead;
    WORD fileType;
    FIL bmpfsrc;
    FRESULT bmpres = FR_DISK_ERR;
    unsigned int read_num;
    unsigned char tmp_name[20];

    
    sprintf((char*)tmp_name, "0:%s", pic_name);
    //f_mount(0, &bmpfs[0]);
    bmpres = f_open(&bmpfsrc, (char *)tmp_name, FA_OPEN_EXISTING | FA_READ);
    
    if(bmpres == FR_OK)
    {
        DBG_Print(LOG_LEVEL_INFO, "Open file success\r\n");
        
        //?����???��????t����D??��        
        f_read(&bmpfsrc, &fileType, sizeof(WORD), &read_num);     
        ulPostion += sizeof(WORD);
        if(fileType != 0x4d42)
        {
            DBG_Print(LOG_LEVEL_INFO, "file is not .bmp file!\r\n");
            return;
        }
        else
        {
            DBG_Print(LOG_LEVEL_ERR, "Ok this is .bmp file\r\n");	
        }        
        
        f_read(&bmpfsrc, &bitHead, sizeof(BITMAP_FILE_HD), &read_num);    
        ulPostion += sizeof(BITMAP_FILE_HD);
        showBmpHead(&bitHead);
        
        //?����???��?D??�騪��D??��
        f_read(&bmpfsrc, &bitInfoHead, sizeof(BITMAP_INF_HD), &read_num);
        ulPostion += sizeof(BITMAP_INF_HD);
        showBmpInforHead(&bitInfoHead);	//??��????t?��??D??��
    }    
    else
    {
        DBG_Print(LOG_LEVEL_ERR, "file open fail!\r\n");
        return;
    }    
    
    width = bitInfoHead.biWidth;
    height = bitInfoHead.biHeight;
    
    l_width = WIDTHBYTES(width* bitInfoHead.biBitCount);//??????��?��?����?��?��?��2�騨������?��?a32��?��?��y	    
    
    if(l_width>960)
    {
        DBG_Print(LOG_LEVEL_INFO, "SORRY, PIC IS TOO BIG (<=320)\r\n");
        return;
    }
    
    if(bitInfoHead.biBitCount>=24)
    {
        uint8 *pucBmpBuf = NULL;
        while (NULL == (pucBmpBuf = (uint8 *)OSMemGetEx(1000)))
        {
            TimeDlyms(100);
        }
        bmp(x,y,width, height);									//LCD2?��y?��1?����??
        
        for(i=0; i<height; i++)
        {	
            //f_read(&bmpfsrc, pucBmpBuf, l_width, &read_num);
            for(j = 0; j < l_width;)	 						//??��?DD��y?Y��?2??����?
            {
                f_read(&bmpfsrc ,pucBmpBuf+j, l_width / 2, &read_num);
                j += l_width / 2;
            }
            //TimeDlyms(10);
            for(j = 0; j< width; j++) 							//��?DD��DD��D??��
            {
                k = j*3;									//��?DD?D�̨�K??????��??e��?
                red = pucBmpBuf[k+2];
                green = pucBmpBuf[k+1];
                blue = 	pucBmpBuf[k];
                LCD_WR_DATA(RGB24TORGB16(red,green,blue));//D�䨨?LCD-GRAM
            }
        }
        OSMemPutEx(pucBmpBuf);
        //LCD_Set_Ver(0);		 																							//lcd����?����??��?��?-	        
    }    
    else 
    {        
        DBG_Print(LOG_LEVEL_ERR, "SORRY, THIS PIC IS NOT A 24BITS REAL COLOR");
        return ;
    }
    
    f_close(&bmpfsrc);    
}
/*******************************************************************************
 *                                End of File                                  *
 *******************************************************************************/



