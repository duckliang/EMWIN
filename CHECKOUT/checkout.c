#include "checkout.h"

volatile u8 x_button,y_check;
extern volatile u8 getstate[40][40];
extern volatile u8 savestate[40][40];
volatile u8 buttoncol[40];
volatile u32 checkcol[40]={
	GUI_BLUE,GUI_BLUE,GUI_BLUE,GUI_BLUE,GUI_BLUE,GUI_BLUE,GUI_BLUE,GUI_BLUE,GUI_BLUE,GUI_BLUE,
  GUI_BLUE,GUI_BLUE,GUI_BLUE,GUI_BLUE,GUI_BLUE,GUI_BLUE,GUI_BLUE,GUI_BLUE,GUI_BLUE,GUI_BLUE,
	GUI_BLUE,GUI_BLUE,GUI_BLUE,GUI_BLUE,GUI_BLUE,GUI_BLUE,GUI_BLUE,GUI_BLUE,GUI_BLUE,GUI_BLUE,
	GUI_BLUE,GUI_BLUE,GUI_BLUE,GUI_BLUE,GUI_BLUE,GUI_BLUE,GUI_BLUE,GUI_BLUE,GUI_BLUE,GUI_BLUE
};

uint8_t (*ReadInput[40]) (void);
void (*WriteOutput[40]) (void);
void (*RecoverOutput[40]) (void);

uint8_t ReadInput0 (void){return GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2);}
uint8_t ReadInput1 (void){return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1);}
uint8_t ReadInput2 (void){return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2);}
uint8_t ReadInput3 (void){return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3);}
uint8_t ReadInput4 (void){return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4);}
uint8_t ReadInput5 (void){return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5);}
uint8_t ReadInput6 (void){return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);}
uint8_t ReadInput7 (void){return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7);}
uint8_t ReadInput8 (void){return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8);}
uint8_t ReadInput9 (void){return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9);}

uint8_t ReadInput10 (void){return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11);}
uint8_t ReadInput11 (void){return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12);}
uint8_t ReadInput12 (void){return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_13);}
uint8_t ReadInput13 (void){return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_14);}
uint8_t ReadInput14 (void){return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15);}
uint8_t ReadInput15 (void){return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3);}
uint8_t ReadInput16 (void){return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4);}
uint8_t ReadInput17 (void){return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5);}
uint8_t ReadInput18 (void){return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6);}
uint8_t ReadInput19 (void){return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7);}

uint8_t ReadInput20 (void){return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10);}
uint8_t ReadInput21 (void){return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);}
uint8_t ReadInput22 (void){return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12);}
uint8_t ReadInput23 (void){return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);}
uint8_t ReadInput24 (void){return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14);}
uint8_t ReadInput25 (void){return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15);}
uint8_t ReadInput26 (void){return GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0);}
uint8_t ReadInput27 (void){return GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1);}
uint8_t ReadInput28 (void){return GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2);}
uint8_t ReadInput29 (void){return GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3);}

uint8_t ReadInput30 (void){return GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4);}
uint8_t ReadInput31 (void){return GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5);}
uint8_t ReadInput32 (void){return GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6);}
uint8_t ReadInput33 (void){return GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7);}
uint8_t ReadInput34 (void){return GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8);}
uint8_t ReadInput35 (void){return GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9);}
uint8_t ReadInput36 (void){return GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10);}
uint8_t ReadInput37 (void){return GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11);}
uint8_t ReadInput38 (void){return GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_12);}
uint8_t ReadInput39 (void){return GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13);}
	
void WriteOutput0 (void){ GPIO_ResetBits(GPIOD,GPIO_Pin_6);}   void RecoverOutput0 (void){ GPIO_SetBits(GPIOD,GPIO_Pin_6);}
void WriteOutput1 (void){ GPIO_ResetBits(GPIOD,GPIO_Pin_7);}   void RecoverOutput1 (void){ GPIO_SetBits(GPIOD,GPIO_Pin_7);}
void WriteOutput2 (void){ GPIO_ResetBits(GPIOD,GPIO_Pin_11);}  void RecoverOutput2 (void){ GPIO_SetBits(GPIOD,GPIO_Pin_11);}
void WriteOutput3 (void){ GPIO_ResetBits(GPIOD,GPIO_Pin_12);}  void RecoverOutput3 (void){ GPIO_SetBits(GPIOD,GPIO_Pin_12);}
void WriteOutput4 (void){ GPIO_ResetBits(GPIOD,GPIO_Pin_13);}  void RecoverOutput4 (void){ GPIO_SetBits(GPIOD,GPIO_Pin_13);}
void WriteOutput5 (void){ GPIO_ResetBits(GPIOE,GPIO_Pin_0);}   void RecoverOutput5 (void){ GPIO_SetBits(GPIOE,GPIO_Pin_0);}
void WriteOutput6 (void){ GPIO_ResetBits(GPIOE,GPIO_Pin_1);}   void RecoverOutput6 (void){ GPIO_SetBits(GPIOE,GPIO_Pin_1);}
void WriteOutput7 (void){ GPIO_ResetBits(GPIOE,GPIO_Pin_2);}  void RecoverOutput7 (void){ GPIO_SetBits(GPIOE,GPIO_Pin_2);}
void WriteOutput8 (void){ GPIO_ResetBits(GPIOE,GPIO_Pin_3);}  void RecoverOutput8 (void){ GPIO_SetBits(GPIOE,GPIO_Pin_3);}
void WriteOutput9 (void){ GPIO_ResetBits(GPIOE,GPIO_Pin_4);}  void RecoverOutput9 (void){ GPIO_SetBits(GPIOE,GPIO_Pin_4);}

void WriteOutput10 (void){ GPIO_ResetBits(GPIOE,GPIO_Pin_5);}  void RecoverOutput10 (void){ GPIO_SetBits(GPIOE,GPIO_Pin_5);}
void WriteOutput11 (void){ GPIO_ResetBits(GPIOE,GPIO_Pin_6);}  void RecoverOutput11 (void){ GPIO_SetBits(GPIOE,GPIO_Pin_6);}
void WriteOutput12 (void){ GPIO_ResetBits(GPIOF,GPIO_Pin_0);}  void RecoverOutput12 (void){ GPIO_SetBits(GPIOF,GPIO_Pin_0);}
void WriteOutput13 (void){ GPIO_ResetBits(GPIOF,GPIO_Pin_1);}  void RecoverOutput13 (void){ GPIO_SetBits(GPIOF,GPIO_Pin_1);}
void WriteOutput14 (void){ GPIO_ResetBits(GPIOF,GPIO_Pin_2);}  void RecoverOutput14 (void){ GPIO_SetBits(GPIOF,GPIO_Pin_2);}
void WriteOutput15 (void){ GPIO_ResetBits(GPIOF,GPIO_Pin_3);}  void RecoverOutput15 (void){ GPIO_SetBits(GPIOF,GPIO_Pin_3);}
void WriteOutput16 (void){ GPIO_ResetBits(GPIOF,GPIO_Pin_4);}  void RecoverOutput16 (void){ GPIO_SetBits(GPIOF,GPIO_Pin_4);}
void WriteOutput17 (void){ GPIO_ResetBits(GPIOF,GPIO_Pin_5);}  void RecoverOutput17 (void){ GPIO_SetBits(GPIOF,GPIO_Pin_5);}
void WriteOutput18 (void){ GPIO_ResetBits(GPIOF,GPIO_Pin_6);}  void RecoverOutput18 (void){ GPIO_SetBits(GPIOF,GPIO_Pin_6);}
void WriteOutput19 (void){ GPIO_ResetBits(GPIOF,GPIO_Pin_7);}  void RecoverOutput19 (void){ GPIO_SetBits(GPIOF,GPIO_Pin_7);}

void WriteOutput20 (void){ GPIO_ResetBits(GPIOF,GPIO_Pin_8);}  void RecoverOutput20 (void){ GPIO_SetBits(GPIOF,GPIO_Pin_8);}
void WriteOutput21 (void){ GPIO_ResetBits(GPIOF,GPIO_Pin_12);}  void RecoverOutput21 (void){ GPIO_SetBits(GPIOF,GPIO_Pin_12);}
void WriteOutput22 (void){ GPIO_ResetBits(GPIOF,GPIO_Pin_13);}  void RecoverOutput22 (void){ GPIO_SetBits(GPIOF,GPIO_Pin_13);}
void WriteOutput23 (void){ GPIO_ResetBits(GPIOF,GPIO_Pin_14);}  void RecoverOutput23 (void){ GPIO_SetBits(GPIOF,GPIO_Pin_14);}
void WriteOutput24 (void){ GPIO_ResetBits(GPIOF,GPIO_Pin_15);}  void RecoverOutput24 (void){ GPIO_SetBits(GPIOF,GPIO_Pin_15);}
void WriteOutput25 (void){ GPIO_ResetBits(GPIOG,GPIO_Pin_1);}  void RecoverOutput25 (void){ GPIO_SetBits(GPIOG,GPIO_Pin_1);}
void WriteOutput26 (void){ GPIO_ResetBits(GPIOG,GPIO_Pin_2);}  void RecoverOutput26 (void){ GPIO_SetBits(GPIOG,GPIO_Pin_2);}
void WriteOutput27 (void){ GPIO_ResetBits(GPIOG,GPIO_Pin_3);}  void RecoverOutput27 (void){ GPIO_SetBits(GPIOG,GPIO_Pin_3);}
void WriteOutput28 (void){ GPIO_ResetBits(GPIOG,GPIO_Pin_4);}  void RecoverOutput28 (void){ GPIO_SetBits(GPIOG,GPIO_Pin_4);}
void WriteOutput29 (void){ GPIO_ResetBits(GPIOG,GPIO_Pin_5);}  void RecoverOutput29 (void){ GPIO_SetBits(GPIOG,GPIO_Pin_5);}

void WriteOutput30 (void){ GPIO_ResetBits(GPIOG,GPIO_Pin_6);}  void RecoverOutput30 (void){ GPIO_SetBits(GPIOG,GPIO_Pin_6);}
void WriteOutput31 (void){ GPIO_ResetBits(GPIOG,GPIO_Pin_7);}  void RecoverOutput31 (void){ GPIO_SetBits(GPIOG,GPIO_Pin_7);}
void WriteOutput32 (void){ GPIO_ResetBits(GPIOG,GPIO_Pin_8);}  void RecoverOutput32 (void){ GPIO_SetBits(GPIOG,GPIO_Pin_8);}
void WriteOutput33 (void){ GPIO_ResetBits(GPIOG,GPIO_Pin_9);}  void RecoverOutput33 (void){ GPIO_SetBits(GPIOG,GPIO_Pin_9);}
void WriteOutput34 (void){ GPIO_ResetBits(GPIOG,GPIO_Pin_10);}  void RecoverOutput34 (void){ GPIO_SetBits(GPIOG,GPIO_Pin_10);}
void WriteOutput35 (void){ GPIO_ResetBits(GPIOG,GPIO_Pin_11);}  void RecoverOutput35 (void){ GPIO_SetBits(GPIOG,GPIO_Pin_11);}
void WriteOutput36 (void){ GPIO_ResetBits(GPIOG,GPIO_Pin_13);}  void RecoverOutput36 (void){ GPIO_SetBits(GPIOG,GPIO_Pin_13);}
void WriteOutput37 (void){ GPIO_ResetBits(GPIOG,GPIO_Pin_14);}  void RecoverOutput37 (void){ GPIO_SetBits(GPIOG,GPIO_Pin_14);}
void WriteOutput38 (void){ GPIO_ResetBits(GPIOG,GPIO_Pin_15);}  void RecoverOutput38 (void){ GPIO_SetBits(GPIOG,GPIO_Pin_15);}
void WriteOutput39 (void){ GPIO_ResetBits(GPIOD,GPIO_Pin_3);}  void RecoverOutput39 (void){ GPIO_SetBits(GPIOD,GPIO_Pin_3);}


void GPIO_INPUT_CONFIG(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|
																 GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|
																 GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  =  GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|
																	GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	ReadInput[0]=ReadInput0; 	ReadInput[10]=ReadInput10; 	ReadInput[20]=ReadInput20; 	ReadInput[30]=ReadInput30;
	ReadInput[1]=ReadInput1;  ReadInput[11]=ReadInput11; 	ReadInput[21]=ReadInput21; 	ReadInput[31]=ReadInput31;
	ReadInput[2]=ReadInput2; 	ReadInput[12]=ReadInput12; 	ReadInput[22]=ReadInput22; 	ReadInput[32]=ReadInput32;
	ReadInput[3]=ReadInput3; 	ReadInput[13]=ReadInput13; 	ReadInput[23]=ReadInput23; 	ReadInput[33]=ReadInput33;
	ReadInput[4]=ReadInput4; 	ReadInput[14]=ReadInput14; 	ReadInput[24]=ReadInput24; 	ReadInput[34]=ReadInput34;
	ReadInput[5]=ReadInput5; 	ReadInput[15]=ReadInput15; 	ReadInput[25]=ReadInput25; 	ReadInput[35]=ReadInput35;
	ReadInput[6]=ReadInput6; 	ReadInput[16]=ReadInput16; 	ReadInput[26]=ReadInput26; 	ReadInput[36]=ReadInput36;
	ReadInput[7]=ReadInput7; 	ReadInput[17]=ReadInput17; 	ReadInput[27]=ReadInput27; 	ReadInput[37]=ReadInput37;
	ReadInput[8]=ReadInput8; 	ReadInput[18]=ReadInput18; 	ReadInput[28]=ReadInput28; 	ReadInput[38]=ReadInput38;
	ReadInput[9]=ReadInput9; 	ReadInput[19]=ReadInput19; 	ReadInput[29]=ReadInput29; 	ReadInput[39]=ReadInput39;

}
void GPIO_OUTPUT_CONFIG(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOG, ENABLE);	 //使能PB,PE端口时钟
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOD, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	 GPIO_SetBits(GPIOD,GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13);						 //PB.5 输出高

	 GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOE, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	 GPIO_SetBits(GPIOE,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6);						 //PB.5 输出高	
	 
	 GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|
																	GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOF, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	 GPIO_SetBits(GPIOF, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|
																	GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);						 //PB.5 输出高	
																	
	 GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|
																	GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOG, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	 GPIO_SetBits(GPIOG, GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|
																	GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);				
																	
	WriteOutput[0]=WriteOutput0; 	WriteOutput[10]=WriteOutput10; 	WriteOutput[20]=WriteOutput20; 	WriteOutput[30]=WriteOutput30;
	WriteOutput[1]=WriteOutput1;  WriteOutput[11]=WriteOutput11; 	WriteOutput[21]=WriteOutput21; 	WriteOutput[31]=WriteOutput31;
	WriteOutput[2]=WriteOutput2; 	WriteOutput[12]=WriteOutput12; 	WriteOutput[22]=WriteOutput22; 	WriteOutput[32]=WriteOutput32;
	WriteOutput[3]=WriteOutput3; 	WriteOutput[13]=WriteOutput13; 	WriteOutput[23]=WriteOutput23; 	WriteOutput[33]=WriteOutput33;
	WriteOutput[4]=WriteOutput4; 	WriteOutput[14]=WriteOutput14; 	WriteOutput[24]=WriteOutput24; 	WriteOutput[34]=WriteOutput34;
	WriteOutput[5]=WriteOutput5; 	WriteOutput[15]=WriteOutput15; 	WriteOutput[25]=WriteOutput25; 	WriteOutput[35]=WriteOutput35;
	WriteOutput[6]=WriteOutput6; 	WriteOutput[16]=WriteOutput16; 	WriteOutput[26]=WriteOutput26; 	WriteOutput[36]=WriteOutput36;
	WriteOutput[7]=WriteOutput7; 	WriteOutput[17]=WriteOutput17; 	WriteOutput[27]=WriteOutput27; 	WriteOutput[37]=WriteOutput37;
	WriteOutput[8]=WriteOutput8; 	WriteOutput[18]=WriteOutput18; 	WriteOutput[28]=WriteOutput28; 	WriteOutput[38]=WriteOutput38;
	WriteOutput[9]=WriteOutput9; 	WriteOutput[19]=WriteOutput19; 	WriteOutput[29]=WriteOutput29; 	WriteOutput[39]=WriteOutput39;
	
	RecoverOutput[0]=RecoverOutput0; 	RecoverOutput[10]=RecoverOutput10; 	RecoverOutput[20]=RecoverOutput20; 	RecoverOutput[30]=RecoverOutput30;
	RecoverOutput[1]=RecoverOutput1;  RecoverOutput[11]=RecoverOutput11; 	RecoverOutput[21]=RecoverOutput21; 	RecoverOutput[31]=RecoverOutput31;
	RecoverOutput[2]=RecoverOutput2; 	RecoverOutput[12]=RecoverOutput12; 	RecoverOutput[22]=RecoverOutput22; 	RecoverOutput[32]=RecoverOutput32;
	RecoverOutput[3]=RecoverOutput3; 	RecoverOutput[13]=RecoverOutput13; 	RecoverOutput[23]=RecoverOutput23; 	RecoverOutput[33]=RecoverOutput33;
	RecoverOutput[4]=RecoverOutput4; 	RecoverOutput[14]=RecoverOutput14; 	RecoverOutput[24]=RecoverOutput24; 	RecoverOutput[34]=RecoverOutput34;
	RecoverOutput[5]=RecoverOutput5; 	RecoverOutput[15]=RecoverOutput15; 	RecoverOutput[25]=RecoverOutput25; 	RecoverOutput[35]=RecoverOutput35;
	RecoverOutput[6]=RecoverOutput6; 	RecoverOutput[16]=RecoverOutput16; 	RecoverOutput[26]=RecoverOutput26; 	RecoverOutput[36]=RecoverOutput36;
	RecoverOutput[7]=RecoverOutput7; 	RecoverOutput[17]=RecoverOutput17; 	RecoverOutput[27]=RecoverOutput27; 	RecoverOutput[37]=RecoverOutput37;
	RecoverOutput[8]=RecoverOutput8; 	RecoverOutput[18]=RecoverOutput18; 	RecoverOutput[28]=RecoverOutput28; 	RecoverOutput[38]=RecoverOutput38;
	RecoverOutput[9]=RecoverOutput9; 	RecoverOutput[19]=RecoverOutput19; 	RecoverOutput[29]=RecoverOutput29; 	RecoverOutput[39]=RecoverOutput39;
}
void checkout(void)
{

	int i,j;
  for(i=0;i<40;i++){
	  
		for(j=0;j<40;j++){
			if(savestate[i][j]==1)
			{		
					WriteOutput[j]();
					if(ReadInput[i]()==1){
						BEEP=1;
						y_check=j;
						x_button=i;
						buttoncol[i]=GUI_RED;
						checkcol[j]=GUI_RED;
            GUI_SendKeyMsg(GUI_KEY_PGUP, 1);
						GUI_SendKeyMsg(GUI_KEY_PGDOWN, 1);
					}
					else{
						buttoncol[i]=GUI_BLACK;
						checkcol[j]=GUI_BLUE;						            							
					}
					RecoverOutput[j]();
			}
			
		}
	}
}