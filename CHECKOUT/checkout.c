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
const uint16_t OUT_select[5]={GPIO_Pin_1,GPIO_Pin_2,GPIO_Pin_3,GPIO_Pin_4,GPIO_Pin_5};
const uint16_t IN_select[5]={GPIO_Pin_1,GPIO_Pin_2,GPIO_Pin_3,GPIO_Pin_4,GPIO_Pin_5};
void GPIO_INPUT_CONFIG(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOE, &GPIO_InitStructure);
}
void GPIO_OUTPUT_CONFIG(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);	 //使能PB,PE端口时钟
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;//LED0-->PB.5 端口配置
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOF, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	 GPIO_SetBits(GPIOF,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5);						 //PB.5 输出高
}
void checkout(void)
{
	int i,j;
  for(i=0;i<40;i++){
	  
		for(j=0;j<40;j++){
			if(savestate[i][j]==1)
			{		
					GPIO_ResetBits(GPIOF,OUT_select[j]);
					if(GPIO_ReadInputDataBit(GPIOE,IN_select[i])==0){
						BEEP=1;
						y_check=j;
						x_button=i;
						buttoncol[i]=GUI_RED;
						checkcol[j]=GUI_RED;
            GUI_SendKeyMsg(GUI_KEY_PGUP, 1);
						GUI_SendKeyMsg(GUI_KEY_PGDOWN, 1);
					}
					else{
//						BEEP=0;
						buttoncol[i]=GUI_BLACK;
						checkcol[j]=GUI_BLUE;						            
//						GUI_SendKeyMsg(GUI_KEY_UP, 1);
//						GUI_SendKeyMsg(GUI_KEY_DOWN, 1);
						

					}
				GPIO_SetBits(GPIOF,OUT_select[j]);
			}
			
		}
	}
}