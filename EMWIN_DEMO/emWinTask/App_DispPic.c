/*
*********************************************************************************************************
*	                                  
*	ģ������ : ��ͼ����ʾͼƬ
*	�ļ����� : App_DispPic.c
*	��    �� : V1.0
*	˵    �� : ��ͼ����ʾͼƬ
*	�޸ļ�¼ :
*		�汾��    ����          ����                 ˵��
*		v1.0    2013-03-26    Eric2013            �汾emWin5.16
*       v2.0    2014-02-23    Eric2013            �汾STemWin5.22
*
*      Copyright (C), 2013-2014, ���������� www.armfly.com
*********************************************************************************************************
*/
#include "includes.h"
#include "MainTask.h"


/*
************************************************************************
*						  ����SD��
************************************************************************
*/
uint8_t data[1024];
FRESULT result;
FIL file;
FILINFO finfo;
DIR DirInf;
UINT bw;
FATFS fs;


/*
*********************************************************************************************************
*	�� �� ��: DispBMP
*	����˵��: ÿ�ζ�ȡ512�ֽڣ�Ȼ����ʾ�����ʹ���ڴ�����Ǻܺõģ�����ûʹ�á�
*	��    �Σ�S_xpos    BMPͼƬ��ʾX��
*			  S_ypos    BMPͼƬ��ʾY��
*             filename	�ļ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void GUI_DrawBMP(uint8_t S_xpos,uint16_t S_ypos,TCHAR *filename)
{	
	BITMAPINFO *pbmp;
	uint16_t  COLOR=0,tmp_color=0,countpix=0;
	uint8_t   color_byte,rgb=0;
	uint16_t  uiTemp,Xpos,Ypos;
	uint32_t  pointpos=0,count,DataSize;
	
	bsp_LedOff(0);
	/* �����ļ�ϵͳ */
	result = f_mount(0, &fs);
	if (result != FR_OK)
	{
		return;
	}
	bsp_LedOn(1);
	/* ���ļ� */		
	result = f_open(&file,filename, FA_OPEN_EXISTING | FA_READ|FA_OPEN_ALWAYS);
	if (result != FR_OK)
	{	bsp_LedOn(2);
		return;
	}

	/* ������ */
	result = f_read(&file, data, 512, &bw);
	if (result != FR_OK)
	{
		return;
	}
	 bsp_LedOn(3);
	pbmp=(BITMAPINFO*)data;												  
	count=pbmp->bmfHeader.bfOffBits;        							 
	color_byte=pbmp->bmiHeader.biBitCount/8;							  
	DataSize=pbmp->bmiHeader.biWidth*pbmp->bmiHeader.biHeight*color_byte;
	
	if((pbmp->bmiHeader.biWidth*color_byte)%4)
		uiTemp=((pbmp->bmiHeader.biWidth*color_byte)/4+1)*4;
	else
		uiTemp=pbmp->bmiHeader.biWidth*color_byte;

 	Xpos = S_xpos;
	Ypos = pbmp->bmiHeader.biHeight-1+S_ypos; 		
    
	RA8875_SetCursor(Xpos, Ypos);
	RA8875_REG = 0x02;
			
	while(1)
   {
     while(count<512)
	 {
	      if(color_byte==3)   
			{
				switch (rgb) 
				{
					case 0:
						tmp_color = data[count]>>3 ;
						COLOR |= tmp_color;
						break ;	   
					case 1: 
						tmp_color = data[count]>>2 ;
						tmp_color <<= 5 ;
						COLOR |= tmp_color ;
						break;	  
					case 2 : 
						tmp_color = data[count]>>3 ;
						tmp_color <<= 11 ;
						COLOR |= tmp_color ;
						break ;			
				}   
			}
          	if(color_byte==2)  
				{
					switch(rgb)
					{
						case 0 : 
							COLOR=data[count]&0x1f;
						    tmp_color=data[count]>>5;
							tmp_color<<=6;
							COLOR|=tmp_color;
							break ;   
						case 1 : 			  
							tmp_color=data[count];
							tmp_color<<=9 ;
							COLOR |= tmp_color ;
							break ;	 
					}		     
				}
			if(color_byte==4)
				{
					switch (rgb)
						{
							case 0 :  
								tmp_color=data[count];
								COLOR|=tmp_color>>3;
								break ;     
							case 1 :  
								tmp_color=data[count];
								tmp_color>>=2;
								COLOR|=tmp_color<<5;
								break ;	  
							case 2 :  
								tmp_color=data[count];
								tmp_color>>=3;
								COLOR|=tmp_color<<11;
								break ;	 
							case 3 :break ;   
						}		  	 
					}     
		    rgb++;	  
			count++;		  
			if(rgb==color_byte) 
			{							 				 	  	       		 
				RA8875_RAM = COLOR;    									    
			    COLOR=0x00; 
			    rgb=0;  		  
			}
			countpix++;
			pointpos++;
			
			if(pointpos>=DataSize)
			{
				f_close(&file);
				f_mount(0, NULL);
				return;
			}
			if(countpix>=uiTemp)
			{		 
				RA8875_SetCursor(S_xpos, --Ypos);
				RA8875_REG = 0x02;
				countpix=0; 
			}
		 }
		  result = f_read(&file, data, 512, &bw);
		  if (result != FR_OK)
		 {
			return;
	     }
		  count=0;
	   }

}

/*
*********************************************************************************************************
*	�� �� ��: GUI_Copy_ScreenRect()
*	����˵��: ��Ļ��ͼ��Ȼ����bmpͼƬ��ʽ(Ϊ24λ�����λͼ)���浽ָ����·����
*	��    �Σ�x:X����   y:y����   sizex:����   sizey:���
*             *Save_Path:����·��,�����ļ�����׺����Ϊbmp
*             ����:"0:/Picture/abcd.bmp" ע��!!:·��"0:/0:/Picture"�������
*             ����ú���������Ч��            	
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void GUI_SaveBMP(uint16_t startx,uint16_t starty,uint16_t sizex,uint16_t sizey,void *Save_Path)
{
	uint32_t	size = (sizex*sizey)*3;//-- ������24ΪBMPλͼ��һ������ռ3���ֽ�,����Ҫ����3
	uint16_t	Header_num = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
	int16_t 	i = 0,j = 0,temp = 0,count = 0;
	uint16_t 	Buffer_num = 510;


	BITMAPFILEHEADER 	 BmpFileHeader;
	BITMAPINFOHEADER	 BmpInfoHeader;
	
//	/* �����ļ�ϵͳ */
	result = f_mount(0, &fs);
	if (result != FR_OK)
	{
		return;
	}

	/*------------------------------- �����ļ�ͷ���� -----------------------------------------*/
	BmpFileHeader.bfType      = 0x4D42;//--�ļ���־.ֻ��'BM',����ʶ��BMPλͼ����
	BmpFileHeader.bfSize 	  = size + Header_num;//--�ļ���С,ռ�ĸ��ֽ�
	BmpFileHeader.bfReserved1 = 0;				  //--�����ֶ�1
	BmpFileHeader.bfReserved2 = 0;				  //--�����ֶ�2
	BmpFileHeader.bfOffBits   = Header_num;//--���ļ���ʼ��λͼ����(bitmap data)��ʼ֮��ĵ�ƫ����
	/*------------------------------- �����ļ���Ϣ���� ---------------------------------------*/
	BmpInfoHeader.biSize   = sizeof(BITMAPINFOHEADER);//--˵��BITMAPINFOHEADER�ṹ����Ҫ������
	BmpInfoHeader.biWidth  = sizex;   //--˵��ͼ��Ŀ�ȣ�������Ϊ��λ
	BmpInfoHeader.biHeight = sizey;   //--˵��ͼ��ĸ߶ȣ�������Ϊ��λ 
	BmpInfoHeader.biPlanes = 1;	      //--ΪĿ���豸˵��λ��������ֵ�����Ǳ���Ϊ1
	BmpInfoHeader.biBitCount = 24;    //--˵��������/���أ���ֵΪ1��4��8��16��24����32
	BmpInfoHeader.biCompression = 0;  //--˵��ͼ������ѹ��������,��ѹ��
	BmpInfoHeader.biSizeImage = size; //--˵��ͼ��Ĵ�С(������4�ı���)�����ֽ�Ϊ��λ��
										//--����BI_RGB��ʽʱ��������Ϊ0 
	BmpInfoHeader.biXPelsPerMeter = 0;//--˵��ˮƽ�ֱ��ʣ�������/�ױ�ʾ
	BmpInfoHeader.biYPelsPerMeter = 0;//--˵����ֱ�ֱ��ʣ�������/�ױ�ʾ
	BmpInfoHeader.biClrUsed		  = 0;//--˵��λͼʵ��ʹ�õĲ�ɫ���е���ɫ������
	BmpInfoHeader.biClrImportant  = 0;//--˵����ͼ����ʾ����ҪӰ�����ɫ��������Ŀ,�����0,��ʾ����Ҫ
	/*-------------------------- ���������ͼ���ݵ��ļ�  ------------------------------------*/
	if (f_open(&file,Save_Path, FA_WRITE|FA_CREATE_ALWAYS) == FR_OK ) 
	{	
			//--��дͼ��ͷ���ݺ�ͼ����Ϣ����
			result = f_write (&file,&BmpFileHeader,sizeof(BmpFileHeader),&bw);
			if (result != FR_OK)
			{
				return;
			}
			
			result = f_write (&file,&BmpInfoHeader,sizeof(BmpInfoHeader),&bw);
			if (result != FR_OK)
			{
				return;
			}
			for(j = sizey-1; j >= 0; j--)
			{		 	
					 for(i = 0; i < sizex; i++)
					 {
							temp = LCD_GetPixel(startx+i,starty+j);
							data[count+2] = (u8)((temp&0xf800)>>8);
							data[count+1] = (u8)((temp&0x7e0)>>3);
							data[count]   = (u8)((temp&0x1f)<<3);
							count += 3;
							if(count == Buffer_num)
							{
									count = 0;
									result = f_write (&file,data,Buffer_num,&bw);
									if (result != FR_OK)
									{
										return;
									}		
							}
					 }
			}
		if(count > 0)	f_write (&file,data,count,&bw);
		f_close(&file);
		f_mount(0, NULL);			
     }
}
/***************************** ���������� www.armfly.com (END OF FILE) *********************************/

