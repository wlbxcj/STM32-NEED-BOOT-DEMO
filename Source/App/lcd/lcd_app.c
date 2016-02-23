/*******************************************************************************
 *
 * 文件名称: lcd_app.c
 *
 * 文件描述: LCD显示文件
 * 作    者: WLB
 * 创建时间: 2015-2-11
 * 文件版本: 
 * 修改历史: 
 *           1. 2015-2-11  WLB  Created
 *******************************************************************************/




/*******************************************************************************
 *                                  头文件包含                                 *
 *******************************************************************************/
#include    "config.h"

/*******************************************************************************
 *                          本文件定义的全局变量和函数声明                     *
 *******************************************************************************/
void *LCDQueue[LCD_QUEUE_SIZE];


/*******************************************************************************
 *                             外部变量和函数声明                              *
 *******************************************************************************/
extern uint8 char_or_word;

/*******************************************************************************
* Function Name  : GetGBKCode_from_sd
* Description    : ′óSD?¨×??a?D?áè?×??têy?Yμ????¨μ??o3??? 
* Input          : pBuffer---êy?Y±￡′?μ??·  
*				   					c--oo×?×?·?μí×??ú?? 
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
        
    High8bit=*c;     /* è???8??êy?Y */
    Low8bit=*(c+1);  /* è?μí8??êy?Y */
    //myres = f_mount(1, &fs[1]);
    pos = ((High8bit - 0xb0) * 94 + Low8bit - 0xa1) * 2 * 16 ;	
    myres = f_open(&fp, "0:/HZLIB.bin", FA_OPEN_EXISTING | FA_READ);
    if (myres == FR_OK) 
    {
        f_lseek (&fp, pos);								//??????ò?
        myres = f_read(&fp, pBuffer, 32, &mybr );		 //16*16′óD?μ?oo×? ??×??￡ ??ó?16*2??×??ú
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
* Description    : ??Lcd?áé?è?òa??????ê?ò????D??×?
* Input          : - Xpos: ????×?±ê 
*                  - Ypos: ′1?±×?±ê  
*				   - str: ??ê?μ??D??×?
*				   - Color: ×?·???é?   
*				   - mode: ?￡ê?????		0--±3?°é??a°×é?   1--??×?Dü??
* Output         : None
* Return         : None
* example		 : PutChinese2(200,100,"??",0,1);
* Attention		 : ?ú2?μ÷ó?
*******************************************************************************/
void PutChinese22(u16 x,u16 y,u8 *str,u16 fColor,u16 bColor) //êú?á
{
    
    
    u8 i,j;
    u8 buffer[32];
    unsigned short m;
    //Set_direction(1);																		
    GetGBKCode_from_sd(buffer,str); /* è?×??￡êy?Y */
    char_or_word=1;		//éè???a??ê?oo×?￡??a0?ò?a??ê?×?·?
	LCD_SetPos(x,y);
    for(i=0;i<32;i++) 
	{											
	  	m=buffer[i];
		for(j=0;j<8;j++) 
	  	{
			if((m&0x80)==0x80) 
				LCD_WR_DATA(fColor);		 //?aê?D′è?oo×???é?
			else 
				LCD_WR_DATA(bColor);		 //?aê?D′è?±3?°??é?
			m<<=1;
		} 
	}    
}

/*************************************************************
*	oˉêy??3?:LCD_Put_AC_string(u16 x, u16  y, u8 *s, u16 fColor,u16 bColor)
*	1|    ?ü:??ê?×?·?
*	2?    êy:
*				x:  ′°ì??DX×?±ê?D??D???
*	 		 	y:  ′°ì??DY×?±ê?D??D???
*				s￡o′y??ê?μ?×?·?
*				fColor:×?ì???é?
*				bColor:±3?°??é? 
*	·μ ?? ?μ:?T
*	?μ	  ?÷￡oASCII?òê??±?ó′óC???t?áè?￡?oo×??òê?′óSDà??áè??￡
*************************************************************/
void LCD_Put_AC_string(u16 x, u16  y, u8 *s, u16 fColor,u16 bColor)
{
	u16 Tmp_x, Tmp_y;
    u8 *tmp_str=s;

    Tmp_x = x;
    Tmp_y = y;
	while(*tmp_str!='\0')
	{
		if( *tmp_str< 0x80) 								 //?D??ê?·??a×?·?
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
 * 函数名称: bmp(*)
 * 功能描述: 设置图片要显示的位置及大小
 * 作    者: WLB
 * 输入参数: u16 x, u16 y, u16 width, u16 height
 * 输出参数: 无
 * 返 回 值: 无
 * 其它说明: 无
 * 修改历史: 
 *           1. 2015-2-12  WLB  Created
 *******************************************************************************/
void bmp(u16 x, u16 y, u16 width, u16 height)
{    
    LCD_Set_Ver(0);
	///////////////////////////////////////////////
	LCD_WR_CMD(0x0044,((width+x-1)<<8)+x); 
	LCD_WR_CMD(0x004e,x);        //éè??X·??ò3?ê??μ
		
	/*R45?￠R46   ′1?±·??òμ??e?￠?1μ?*/
	LCD_WR_CMD(0x0045,y);	  
	LCD_WR_CMD(0x0046,height+y-1);
	LCD_WR_CMD(0x004f,y);        //éè??y·??ò3?ê??μ 
	
	LCD_WR_ADD(0X22);     
}

/******************************************************************************* 
 * 函数名称: showBmpHead(*)
 * 功能描述: 显示图片信息
 * 作    者: WLB
 * 输入参数: BITMAP_FILE_HD* pBmpHead
 * 输出参数: 无
 * 返 回 值: 无
 * 其它说明: 无
 * 修改历史: 
 *           1. 2015-2-12  WLB  Created
 *******************************************************************************/
void showBmpHead(BITMAP_FILE_HD* pBmpHead)
{
    DBG_Print(LOG_LEVEL_INFO, "位图文件头   :\r\n");
    DBG_Print(LOG_LEVEL_INFO, "文件大小     :%d\r\n", (*pBmpHead).bfSize);
    DBG_Print(LOG_LEVEL_INFO, "保留字       :%d\r\n", (*pBmpHead).bfReserved1);
    DBG_Print(LOG_LEVEL_INFO, "保留字       :%d\r\n", (*pBmpHead).bfReserved2);
    DBG_Print(LOG_LEVEL_INFO, "实际位图数据的偏移字节数:%d\r\n", (*pBmpHead).bfOffBits);    
}

/******************************************************************************* 
 * 函数名称: showBmpInforHead(*)
 * 功能描述: 打印BMP图片头信息
 * 作    者: WLB
 * 输入参数: BITMAP_INF_HD* pBmpInforHead
 * 输出参数: 无
 * 返 回 值: 无
 * 其它说明: 无
 * 修改历史: 
 *           1. 2015-2-12  WLB  Created
 *******************************************************************************/
void showBmpInforHead(BITMAP_INF_HD* pBmpInforHead)
{
    DBG_Print(LOG_LEVEL_INFO, "位图信息头               :\r\n");
    DBG_Print(LOG_LEVEL_INFO, "结构体的长度             :%d\r\n", (*pBmpInforHead).biSize);
    DBG_Print(LOG_LEVEL_INFO, "位图宽                   :%d\r\n", (*pBmpInforHead).biWidth);
    DBG_Print(LOG_LEVEL_INFO, "位图高                   :%d\r\n", (*pBmpInforHead).biHeight);
    DBG_Print(LOG_LEVEL_INFO, "biPlanes平面数           :%d\r\n", (*pBmpInforHead).biPlanes);
    DBG_Print(LOG_LEVEL_INFO, "biBitCount采用颜色位数   :%d\r\n", (*pBmpInforHead).biBitCount);
    DBG_Print(LOG_LEVEL_INFO, "压缩方式                 :%d\r\n", (*pBmpInforHead).biCompression);
    DBG_Print(LOG_LEVEL_INFO, "biSizeImage实际位图数据战胜的字节数:%d\r\n", (*pBmpInforHead).biSizeImage);
    DBG_Print(LOG_LEVEL_INFO, "X方向分辨率              :%d\r\n", (*pBmpInforHead).biXPelsPerMeter);
    DBG_Print(LOG_LEVEL_INFO, "Y方向分辨率              :%d\r\n", (*pBmpInforHead).biYPelsPerMeter);
    DBG_Print(LOG_LEVEL_INFO, "使用的颜色数             :%d\r\n", (*pBmpInforHead).biClrUsed);
    DBG_Print(LOG_LEVEL_INFO, "重要颜色数               :%d\r\n", (*pBmpInforHead).biClrImportant);
}
/******************************************************************************* 
 * 函数名称: Lcd_show_bmp(*)
 * 功能描述: LCD显示RGB888图片
 * 作    者: WLB
 * 输入参数: 
 * 输出参数: 
 * 返 回 值: 
 * 其它说明: 图片为24真彩色色位图片
 * 修改历史: 
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
        
        //?áè???í????tí·D??￠        
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
        
        //?áè???í?D??￠í·D??￠
        f_read(&bmpfsrc, &bitInfoHead, sizeof(BITMAP_INF_HD), &read_num);
        ulPostion += sizeof(BITMAP_INF_HD);
        showBmpInforHead(&bitInfoHead);	//??è????t?ê??D??￠
    }    
    else
    {
        DBG_Print(LOG_LEVEL_ERR, "file open fail!\r\n");
        return;
    }    
    
    width = bitInfoHead.biWidth;
    height = bitInfoHead.biHeight;
    
    l_width = WIDTHBYTES(width* bitInfoHead.biBitCount);//??????í?μ?êμ?ê?í?è2￠è·±￡?ü?a32μ?±?êy	    
    
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
        bmp(x,y,width, height);									//LCD2?êy?à1?éè??
        
        for(i=0; i<height; i++)
        {	
            //f_read(&bmpfsrc, pucBmpBuf, l_width, &read_num);
            for(j = 0; j < l_width;)	 						//??ò?DDêy?Yè?2??áè?
            {
                f_read(&bmpfsrc ,pucBmpBuf+j, l_width / 2, &read_num);
                j += l_width / 2;
            }
            //TimeDlyms(10);
            for(j = 0; j< width; j++) 							//ò?DDóDD§D??￠
            {
                k = j*3;									//ò?DD?DμúK??????μ??eμ?
                red = pucBmpBuf[k+2];
                green = pucBmpBuf[k+1];
                blue = 	pucBmpBuf[k];
                LCD_WR_DATA(RGB24TORGB16(red,green,blue));//D′è?LCD-GRAM
            }
        }
        OSMemPutEx(pucBmpBuf);
        //LCD_Set_Ver(0);		 																							//lcdé¨?è·??ò?′?-	        
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



