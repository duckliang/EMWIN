#ifndef _CHECKOUT_H
#define _CHECKOUT_H
#include "stm32f10x.h"
#include "beep.h"
#include "GUI.h"
#include "WM.h"
#define INPUT1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)//读取INPUT1
#define INPUT2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//读取INPUT2
#define INPUT3  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//读取INPUT2
#define INPUT4  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//读取INPUT2
#define INPUT5  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)//读取INPUT2
extern volatile u8 x_button,y_check;
extern volatile u8 buttoncol[40];
extern volatile u32 checkcol[40];
void GPIO_INPUT_CONFIG(void);
void GPIO_OUTPUT_CONFIG(void);
void checkout(void);
#endif