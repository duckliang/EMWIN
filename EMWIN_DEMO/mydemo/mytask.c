#include "mytask.h"
#include "includes.h"
#include "stmflash.h"
#include "checkout.h"
#include "string.h"
static WM_HWIN    _hLastFrame;

volatile u8 getstate[40][40];
volatile u8 savestate[40][40];
volatile u8 conver[40][5];
volatile u8 reconv[40][5];
volatile u8 state_in;


const u8 TEXT_Buffer[8]={1,2,3,4,5,6,7,8};
#define SIZE sizeof(conver)		
#define FLASH_SAVE_ADDR  0X08070000		
	u8 key;
	u16 i=0;
	u8 datatemp[SIZE];
	OS_ERR err;
/*
*********************************************************************************************************
*	函 数 名: _PaintFrame
*	功能说明: 框架窗口的重绘函数
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/

static void _PaintFrame(void) 
{
	GUI_RECT r;
	WM_GetClientRect(&r);
	GUI_SetBkColor(GUI_BLACK);
	GUI_SetColor(GUI_BLUE);
	GUI_SetFont(&GUI_Font32_1);
	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_ClearRectEx(&r);

}
/*
*********************************************************************************************************
*	函 数 名: _CreateFrame
*	功能说明: 创建框架窗口
*	形    参：cb  回调函数地址
*	返 回 值: 无
*********************************************************************************************************
*/
static WM_HWIN _CreateFrame(int x,int y,int frame_width,int frame_heigt,WM_CALLBACK* cb) 
{
//	int x = 0;
//	int y = 0;
//	x = FRAME_BORDER + MAIN_BORDER;
//	y = FRAME_BORDER + MAIN_TITLE_HEIGHT;
	_hLastFrame = WM_CreateWindowAsChild(x, y, frame_width, frame_width, WM_HBKWIN, WM_CF_SHOW, cb, 0);
	return _hLastFrame;
}
/*
*********************************************************************************************************
*	函 数 名: _DeleteFrame
*	功能说明: 删除创建的框架窗口
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static void _DeleteFrame(void) 
{
	WM_DeleteWindow(_hLastFrame);
	_hLastFrame = 0;
}
/*
*********************************************************************************************************
*	函 数 名: _CreateButton
*	功能说明: 创建按钮
*	形    参：hParent  父窗口
*             pText    按键上显示的文本
*             Id       按钮Id         
*             x        x轴坐标
*             y        y轴坐标
*             w        按钮宽
*             h        按钮高
*             TextId   文本的ID     
*	返 回 值: 无
*********************************************************************************************************
*/
static WM_HWIN _CreateButton(WM_HWIN hParent, const char* pText, int Id, int x, int y, int w, int h, u32 buttoncolor) 
{
	WM_HWIN hButton;
	hButton = BUTTON_CreateEx(x, y, w, h, hParent, WM_CF_SHOW, 0, Id);
//	BUTTON_SetDefaultSkinClassic();
//  BUTTON_SetBkColor   (hButton, BUTTON_CI_UNPRESSED, GUI_YELLOW);	
	BUTTON_SetText      (hButton,    pText);
	BUTTON_SetFont      (hButton,    &GUI_Font24_1);

	BUTTON_SetTextColor (hButton, 0, buttoncolor);
	WIDGET_SetEffect    (hButton,    0);
	
	/* 设置接收输入焦点的能力 */
	BUTTON_SetFocussable(hButton,    1);
	
	return hButton;
}
static WM_HWIN _CreateCheckbox(WM_HWIN hParent,  const char * pbox, int Id, int x, int y, int w, int h, unsigned TextId) 
{
	WM_HWIN hCheckbox;
	hCheckbox =CHECKBOX_CreateEx(x, y, w, h, hParent, WM_CF_SHOW, 0, Id);
	
//	CHECKBOX_SetFont      (hCheckbox,    &GUI_Font24_1);
	CHECKBOX_SetBkColor   (hCheckbox,  GUI_BLACK);
//	CHECKBOX_SetTextColor (hCheckbox,  GUI_DARKRED);
	WIDGET_SetEffect    (hCheckbox,    0);

	/* 设置接收输入焦点的能力 */
	//CHECKBOX_SetFocussable(hCheckbox,    1);
	
	return hCheckbox;
}
/*
*********************************************************************************************************
*	函 数 名: _cbBkWindow
*	功能说明: 桌面窗口回调函数
*	形    参：pMsg  参数指针
*	返 回 值: 无
*********************************************************************************************************
*/
static void _cbBkWindow(WM_MESSAGE* pMsg) 
{
	switch (pMsg->MsgId) 
	{
		case WM_PAINT: 
			{		
				GUI_SetBkColor(GUI_BLACK);
				GUI_SetColor(GUI_LIGHTGREEN);
				GUI_SetFont(&GUI_Font32_1);
				GUI_Clear();
			} 
			break;
		default:
			WM_DefaultProc(pMsg);
	}
}
/*
*********************************************************************************************************
*	函 数 名: _cboutput
*	形    参：pMsg  参数指针
*	返 回 值: 无
*********************************************************************************************************
*/
static void _cboutput(WM_MESSAGE* pMsg) 
{u8 i,j;
	WM_HWIN hWin = pMsg->hWin;
	WM_HWIN hItem;

	switch (pMsg->MsgId) 
	{
		case WM_CREATE:
				/* 设置聚焦 */
			WM_SetFocus(hWin);

		_CreateCheckbox(hWin, "1", ID_CHECKBOX_1, 000, 0, 40, 40, 0); 
		_CreateCheckbox(hWin, "2", ID_CHECKBOX_2, 100, 0, 40, 40, 0);
		_CreateCheckbox(hWin, "3", ID_CHECKBOX_3, 200, 0, 40, 40, 0); 
		_CreateCheckbox(hWin, "4", ID_CHECKBOX_4, 300, 0, 40, 40, 0);  
		_CreateCheckbox(hWin, "5", ID_CHECKBOX_5, 400, 0, 40, 40, 0);
		_CreateCheckbox(hWin, "6", ID_CHECKBOX_6, 500, 0, 40, 40, 0);
		_CreateCheckbox(hWin, "7", ID_CHECKBOX_7, 600, 0, 40, 40, 0);
		_CreateCheckbox(hWin, "8", ID_CHECKBOX_8, 700, 0, 40, 40, 0);
		
		_CreateCheckbox(hWin, "9", ID_CHECKBOX_9,  000, 100, 40, 40, 0);
		_CreateCheckbox(hWin, "10", ID_CHECKBOX_10, 100, 100, 40, 40, 0);
		_CreateCheckbox(hWin, "11", ID_CHECKBOX_11, 200, 100, 40, 40, 0);
		_CreateCheckbox(hWin, "12", ID_CHECKBOX_12, 300, 100, 40, 40, 0);
		_CreateCheckbox(hWin, "13", ID_CHECKBOX_13, 400, 100, 40, 40, 0);
		_CreateCheckbox(hWin, "14", ID_CHECKBOX_14, 500, 100, 40, 40, 0);
		_CreateCheckbox(hWin, "15", ID_CHECKBOX_15, 600, 100, 40, 40, 0);
		_CreateCheckbox(hWin, "16", ID_CHECKBOX_16, 700, 100, 40, 40, 0);
		
		_CreateCheckbox(hWin, "17", ID_CHECKBOX_17, 000, 200, 40, 40, 0);
		_CreateCheckbox(hWin, "18", ID_CHECKBOX_18, 100, 200, 40, 40, 0);
		_CreateCheckbox(hWin, "19", ID_CHECKBOX_19, 200, 200, 40, 40, 0);
		_CreateCheckbox(hWin, "20", ID_CHECKBOX_20, 300, 200, 40, 40, 0);
		_CreateCheckbox(hWin, "21", ID_CHECKBOX_21, 400, 200, 40, 40, 0);
		_CreateCheckbox(hWin, "22", ID_CHECKBOX_22, 500, 200, 40, 40, 0);
		_CreateCheckbox(hWin, "23", ID_CHECKBOX_23, 600, 200, 40, 40, 0);
		_CreateCheckbox(hWin, "24", ID_CHECKBOX_24, 700, 200, 40, 40, 0);
		
		_CreateCheckbox(hWin, "25", ID_CHECKBOX_25, 000, 300, 40, 40, 0);
		_CreateCheckbox(hWin, "26", ID_CHECKBOX_26, 100, 300, 40, 40, 0);
		_CreateCheckbox(hWin, "27", ID_CHECKBOX_27, 200, 300, 40, 40, 0);
		_CreateCheckbox(hWin, "28", ID_CHECKBOX_28, 300, 300, 40, 40, 0);
		_CreateCheckbox(hWin, "29", ID_CHECKBOX_29, 400, 300, 40, 40, 0);
		_CreateCheckbox(hWin, "30", ID_CHECKBOX_30, 500, 300, 40, 40, 0);	
		_CreateCheckbox(hWin, "31", ID_CHECKBOX_31, 600, 300, 40, 40, 0);
		_CreateCheckbox(hWin, "32", ID_CHECKBOX_32, 700, 300, 40, 40, 0);
		
		_CreateCheckbox(hWin, "33", ID_CHECKBOX_33, 000, 400, 40, 40, 0);
		_CreateCheckbox(hWin, "34", ID_CHECKBOX_34, 100, 400, 40, 40, 0);
		_CreateCheckbox(hWin, "35", ID_CHECKBOX_35, 200, 400, 40, 40, 0);
		_CreateCheckbox(hWin, "36", ID_CHECKBOX_36, 300, 400, 40, 40, 0);
		_CreateCheckbox(hWin, "37", ID_CHECKBOX_37, 400, 400, 40, 40, 0);
		_CreateCheckbox(hWin, "38", ID_CHECKBOX_38, 500, 400, 40, 40, 0);
		_CreateCheckbox(hWin, "39", ID_CHECKBOX_39, 600, 400, 40, 40, 0);
		_CreateCheckbox(hWin, "40", ID_CHECKBOX_40, 700, 400, 40, 40, 0);	
		
		_CreateButton(hWin, "OK", ID_BUTTON_OK, 100, 440, 100, 40, 0);
		_CreateButton(hWin, "REFRESH", ID_BUTTON_CANCLE, 600, 440, 120, 40, 0);
		_CreateButton(hWin, "BACK", ID_BUTTON_BACK, 350, 440, 100, 40, 0);
		
		break;
		
		case WM_PAINT:
			_PaintFrame();
		  GUI_DispStringHCenterAt("please click output", 400, 50);

	  	GUI_SetColor(checkcol[0]); GUI_DispStringAt("1",50,0);     
		  GUI_SetColor(checkcol[1]); GUI_DispStringAt("2",150,0);    
	  	GUI_SetColor(checkcol[2]); GUI_DispStringAt("3",250,0);		
		  GUI_SetColor(checkcol[3]); GUI_DispStringAt("4",350,0);	
	  	GUI_SetColor(checkcol[4]); GUI_DispStringAt("5",450,0);
		  GUI_SetColor(checkcol[5]); GUI_DispStringAt("6",550,0);
	  	GUI_SetColor(checkcol[6]); GUI_DispStringAt("7",650,0);
		  GUI_SetColor(checkcol[7]); GUI_DispStringAt("8",750,0);	
		
			GUI_SetColor(checkcol[8]); GUI_DispStringAt("9",50,100);
		  GUI_SetColor(checkcol[9]); GUI_DispStringAt("10",150,100);
	  	GUI_SetColor(checkcol[10]); GUI_DispStringAt("11",250,100);
		  GUI_SetColor(checkcol[11]); GUI_DispStringAt("12",350,100);	
	  	GUI_SetColor(checkcol[12]); GUI_DispStringAt("13",450,100);
		  GUI_SetColor(checkcol[13]); GUI_DispStringAt("14",550,100);
	  	GUI_SetColor(checkcol[14]); GUI_DispStringAt("15",650,100);
		  GUI_SetColor(checkcol[15]); GUI_DispStringAt("16",750,100);

			GUI_SetColor(checkcol[16]); GUI_DispStringAt("17",50,200);
		  GUI_SetColor(checkcol[17]); GUI_DispStringAt("18",150,200);
	  	GUI_SetColor(checkcol[18]); GUI_DispStringAt("19",250,200);
		  GUI_SetColor(checkcol[19]); GUI_DispStringAt("20",350,200);	
	  	GUI_SetColor(checkcol[20]); GUI_DispStringAt("21",450,200);
		  GUI_SetColor(checkcol[21]); GUI_DispStringAt("22",550,200);
	  	GUI_SetColor(checkcol[22]); GUI_DispStringAt("23",650,200);
		  GUI_SetColor(checkcol[23]); GUI_DispStringAt("24",750,200);
			
			GUI_SetColor(checkcol[24]); GUI_DispStringAt("25",50,300);
		  GUI_SetColor(checkcol[25]); GUI_DispStringAt("26",150,300);
	  	GUI_SetColor(checkcol[26]); GUI_DispStringAt("27",250,300);
		  GUI_SetColor(checkcol[27]); GUI_DispStringAt("28",350,300);	
	  	GUI_SetColor(checkcol[28]); GUI_DispStringAt("29",450,300);
		  GUI_SetColor(checkcol[29]); GUI_DispStringAt("30",550,300);
	  	GUI_SetColor(checkcol[30]); GUI_DispStringAt("31",650,300);
		  GUI_SetColor(checkcol[31]); GUI_DispStringAt("32",750,300);
			
			GUI_SetColor(checkcol[32]); GUI_DispStringAt("33",50,400);
		  GUI_SetColor(checkcol[33]); GUI_DispStringAt("34",150,400);
	  	GUI_SetColor(checkcol[34]); GUI_DispStringAt("35",250,400);
		  GUI_SetColor(checkcol[35]); GUI_DispStringAt("36",350,400);	
	  	GUI_SetColor(checkcol[36]); GUI_DispStringAt("37",450,400);
		  GUI_SetColor(checkcol[37]); GUI_DispStringAt("38",550,400);
	  	GUI_SetColor(checkcol[38]); GUI_DispStringAt("39",650,400);
		  GUI_SetColor(checkcol[39]); GUI_DispStringAt("40",750,400);

	    hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_1);	CHECKBOX_SetState(hItem,savestate[state_in][0]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_2);	CHECKBOX_SetState(hItem,savestate[state_in][1]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_3);	CHECKBOX_SetState(hItem,savestate[state_in][2]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_4);	CHECKBOX_SetState(hItem,savestate[state_in][3]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_5);	CHECKBOX_SetState(hItem,savestate[state_in][4]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_6);	CHECKBOX_SetState(hItem,savestate[state_in][5]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_7);	CHECKBOX_SetState(hItem,savestate[state_in][6]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_8);	CHECKBOX_SetState(hItem,savestate[state_in][7]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_9);	CHECKBOX_SetState(hItem,savestate[state_in][8]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_10);	CHECKBOX_SetState(hItem,savestate[state_in][9]);
			
	    hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_11);	CHECKBOX_SetState(hItem,savestate[state_in][10]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_12);	CHECKBOX_SetState(hItem,savestate[state_in][11]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_13);	CHECKBOX_SetState(hItem,savestate[state_in][12]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_14);	CHECKBOX_SetState(hItem,savestate[state_in][13]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_15);	CHECKBOX_SetState(hItem,savestate[state_in][14]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_16);	CHECKBOX_SetState(hItem,savestate[state_in][15]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_17);	CHECKBOX_SetState(hItem,savestate[state_in][16]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_18);	CHECKBOX_SetState(hItem,savestate[state_in][17]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_19);	CHECKBOX_SetState(hItem,savestate[state_in][18]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_20);	CHECKBOX_SetState(hItem,savestate[state_in][19]);
			
	    hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_21);	CHECKBOX_SetState(hItem,savestate[state_in][20]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_22);	CHECKBOX_SetState(hItem,savestate[state_in][21]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_23);	CHECKBOX_SetState(hItem,savestate[state_in][22]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_24);	CHECKBOX_SetState(hItem,savestate[state_in][23]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_25);	CHECKBOX_SetState(hItem,savestate[state_in][24]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_26);	CHECKBOX_SetState(hItem,savestate[state_in][25]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_27);	CHECKBOX_SetState(hItem,savestate[state_in][26]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_28);	CHECKBOX_SetState(hItem,savestate[state_in][27]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_29);	CHECKBOX_SetState(hItem,savestate[state_in][28]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_30);	CHECKBOX_SetState(hItem,savestate[state_in][29]);
			
	    hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_31);	CHECKBOX_SetState(hItem,savestate[state_in][30]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_32);	CHECKBOX_SetState(hItem,savestate[state_in][31]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_33);	CHECKBOX_SetState(hItem,savestate[state_in][32]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_34);	CHECKBOX_SetState(hItem,savestate[state_in][33]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_35);	CHECKBOX_SetState(hItem,savestate[state_in][34]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_36);	CHECKBOX_SetState(hItem,savestate[state_in][35]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_37);	CHECKBOX_SetState(hItem,savestate[state_in][36]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_38);	CHECKBOX_SetState(hItem,savestate[state_in][37]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_39);	CHECKBOX_SetState(hItem,savestate[state_in][38]);
			hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_40);	CHECKBOX_SetState(hItem,savestate[state_in][39]);			
			
		break;
		
		case WM_KEY:
		switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) 
		{ 
			case GUI_KEY_PGDOWN:
				{
										_DeleteFrame();
					_CreateFrame(0,0,800,480,&_cboutput);
				}
			break;
		}
    break;
		
		case WM_NOTIFY_PARENT:
			if (pMsg->Data.v == WM_NOTIFICATION_RELEASED) 
			{
					int Id = WM_GetId(pMsg->hWinSrc);
					int NCode = pMsg->Data.v;
					switch (Id) 
					{
					  case ID_BUTTON_OK:      
						for(j=0;j<40;j++)
						{
							savestate[state_in][j]=getstate[state_in][j];
						}
						break;		
						
						case ID_BUTTON_CANCLE: _DeleteFrame(); _CreateFrame(0,0,800,480,&_cboutput);BEEP=0; break;
						
						case ID_BUTTON_BACK:   _DeleteFrame(); _CreateFrame(0,0,800,480,&_cbinput); break;	

						case ID_CHECKBOX_1:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_1);	getstate[state_in][0]=(u8)CHECKBOX_GetState(hItem);break;		
						case ID_CHECKBOX_2:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_2);	getstate[state_in][1]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_3:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_3);	getstate[state_in][2]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_4:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_4);	getstate[state_in][3]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_5:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_5);	getstate[state_in][4]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_6:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_6);	getstate[state_in][5]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_7:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_7);	getstate[state_in][6]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_8:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_8);	getstate[state_in][7]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_9:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_9);	getstate[state_in][8]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_10:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_10);	getstate[state_in][9]=(u8)CHECKBOX_GetState(hItem);break;	
						
						case ID_CHECKBOX_11:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_11);	getstate[state_in][10]=(u8)CHECKBOX_GetState(hItem);break;		
						case ID_CHECKBOX_12:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_12);	getstate[state_in][11]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_13:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_13);	getstate[state_in][12]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_14:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_14);	getstate[state_in][13]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_15:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_15);	getstate[state_in][14]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_16:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_16);	getstate[state_in][15]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_17:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_17);	getstate[state_in][16]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_18:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_18);	getstate[state_in][17]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_19:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_19);	getstate[state_in][18]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_20:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_20);	getstate[state_in][19]=(u8)CHECKBOX_GetState(hItem);break;		

						case ID_CHECKBOX_21:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_21);	getstate[state_in][20]=(u8)CHECKBOX_GetState(hItem);break;		
						case ID_CHECKBOX_22:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_22);	getstate[state_in][21]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_23:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_23);	getstate[state_in][22]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_24:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_24);	getstate[state_in][23]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_25:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_25);	getstate[state_in][24]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_26:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_26);	getstate[state_in][25]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_27:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_27);	getstate[state_in][26]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_28:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_28);	getstate[state_in][27]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_29:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_29);	getstate[state_in][28]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_30:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_30);	getstate[state_in][29]=(u8)CHECKBOX_GetState(hItem);break;	
						
						case ID_CHECKBOX_31:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_31);	getstate[state_in][30]=(u8)CHECKBOX_GetState(hItem);break;		
						case ID_CHECKBOX_32:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_32);	getstate[state_in][31]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_33:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_33);	getstate[state_in][32]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_34:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_34);	getstate[state_in][33]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_35:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_35);	getstate[state_in][34]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_36:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_36);	getstate[state_in][35]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_37:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_37);	getstate[state_in][36]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_38:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_38);	getstate[state_in][37]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_39:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_39);	getstate[state_in][38]=(u8)CHECKBOX_GetState(hItem);break;	
						case ID_CHECKBOX_40:	hItem = WM_GetDialogItem(hWin,ID_CHECKBOX_40);	getstate[state_in][39]=(u8)CHECKBOX_GetState(hItem);break;							
					}
			}
		break;
		default:
		WM_DefaultProc(pMsg);
	}
}
/*
*********************************************************************************************************
*	函 数 名: _cbinput
*	形    参：pMsg  参数指针
*	返 回 值: 无
*********************************************************************************************************
*/
static void _cbinput(WM_MESSAGE* pMsg) 
{
	WM_HWIN hWin = pMsg->hWin;
		WM_HWIN hItem;
	switch (pMsg->MsgId) 
	{
		case WM_CREATE:
			/* 设置聚焦 */
			WM_SetFocus(hWin);
 _CreateButton(hWin, "REFRESH", ID_BUTTON_REFRESH, 340, 150, 120, 40, GUI_BLUE);
 _CreateButton(hWin, "DOWNLOAD", ID_BUTTON_DOWNLOAD, 340, 250, 120, 40, GUI_BLUE);
 _CreateButton(hWin, "UPLOAD", ID_BUTTON_UPLOAD, 340, 350, 120, 40, GUI_BLUE);
		_CreateButton(hWin, "1", ID_BUTTON_1, 000, 0, 80, 40, buttoncol[0]);
		_CreateButton(hWin, "2", ID_BUTTON_2, 100, 0, 80, 40, buttoncol[1]);
		_CreateButton(hWin, "3", ID_BUTTON_3, 200, 0, 80, 40, buttoncol[2]);
		_CreateButton(hWin, "4", ID_BUTTON_4, 300, 0, 80, 40, buttoncol[3]);
		_CreateButton(hWin, "5", ID_BUTTON_5, 400, 0, 80, 40, buttoncol[4]);
		_CreateButton(hWin, "6", ID_BUTTON_6, 500, 0, 80, 40, buttoncol[5]);
		_CreateButton(hWin, "7", ID_BUTTON_7, 600, 0, 80, 40, buttoncol[6]);
		_CreateButton(hWin, "8", ID_BUTTON_8, 700, 0, 80, 40, buttoncol[7]);
		
		_CreateButton(hWin, "9", ID_BUTTON_9,  000, 100, 80, 40, buttoncol[8]);
		_CreateButton(hWin, "10", ID_BUTTON_10, 100, 100, 80, 40, buttoncol[9]);
		_CreateButton(hWin, "11", ID_BUTTON_11, 200, 100, 80, 40, buttoncol[10]);
		_CreateButton(hWin, "12", ID_BUTTON_12, 300, 100, 80, 40, buttoncol[11]);
		_CreateButton(hWin, "13", ID_BUTTON_13, 400, 100, 80, 40, buttoncol[12]);
		_CreateButton(hWin, "14", ID_BUTTON_14, 500, 100, 80, 40, buttoncol[13]);
		_CreateButton(hWin, "15", ID_BUTTON_15, 600, 100, 80, 40, buttoncol[14]);
		_CreateButton(hWin, "16", ID_BUTTON_16, 700, 100, 80, 40, buttoncol[15]);
		
		_CreateButton(hWin, "17", ID_BUTTON_17, 000, 200, 80, 40, buttoncol[16]);
		_CreateButton(hWin, "18", ID_BUTTON_18, 100, 200, 80, 40, buttoncol[17]);
		_CreateButton(hWin, "19", ID_BUTTON_19, 200, 200, 80, 40, buttoncol[18]);
		_CreateButton(hWin, "20", ID_BUTTON_20, 300, 200, 80, 40, buttoncol[19]);
		_CreateButton(hWin, "21", ID_BUTTON_21, 400, 200, 80, 40, buttoncol[20]);
		_CreateButton(hWin, "22", ID_BUTTON_22, 500, 200, 80, 40, buttoncol[21]);
		_CreateButton(hWin, "23", ID_BUTTON_23, 600, 200, 80, 40, buttoncol[22]);
		_CreateButton(hWin, "24", ID_BUTTON_24, 700, 200, 80, 40, buttoncol[23]);
		
		_CreateButton(hWin, "25", ID_BUTTON_25, 000, 300, 80, 40, buttoncol[24]);
		_CreateButton(hWin, "26", ID_BUTTON_26, 100, 300, 80, 40, buttoncol[25]);
		_CreateButton(hWin, "27", ID_BUTTON_27, 200, 300, 80, 40, buttoncol[26]);
		_CreateButton(hWin, "28", ID_BUTTON_28, 300, 300, 80, 40, buttoncol[27]);
		_CreateButton(hWin, "29", ID_BUTTON_29, 400, 300, 80, 40, buttoncol[28]);
		_CreateButton(hWin, "30", ID_BUTTON_30, 500, 300, 80, 40, buttoncol[29]);
		_CreateButton(hWin, "31", ID_BUTTON_31, 600, 300, 80, 40, buttoncol[30]);
		_CreateButton(hWin, "32", ID_BUTTON_32, 700, 300, 80, 40, buttoncol[31]);
		
		_CreateButton(hWin, "33", ID_BUTTON_33, 000, 400, 80, 40, buttoncol[32]);
		_CreateButton(hWin, "34", ID_BUTTON_34, 100, 400, 80, 40, buttoncol[33]);
		_CreateButton(hWin, "35", ID_BUTTON_35, 200, 400, 80, 40, buttoncol[34]);
		_CreateButton(hWin, "36", ID_BUTTON_36, 300, 400, 80, 40, buttoncol[35]);
		_CreateButton(hWin, "37", ID_BUTTON_37, 400, 400, 80, 40, buttoncol[36]);
		_CreateButton(hWin, "38", ID_BUTTON_38, 500, 400, 80, 40, buttoncol[37]);
		_CreateButton(hWin, "39", ID_BUTTON_39, 600, 400, 80, 40, buttoncol[38]);
		_CreateButton(hWin, "40", ID_BUTTON_40, 700, 400, 80, 40, buttoncol[39]);
		break;
		
		case WM_KEY:
				switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) 
				{ 
				case GUI_KEY_PGUP:
					{
					_DeleteFrame();
					_CreateFrame(0,0,800,480,&_cbinput);					
					}
				break;
		  	}
    break;
		
		case WM_PAINT:
			_PaintFrame();
		  GUI_DispStringHCenterAt("please enter input", 400, 50);
		break;
		
		case WM_NOTIFY_PARENT:
			if (pMsg->Data.v == WM_NOTIFICATION_RELEASED) 
			{
				int Id = WM_GetId(pMsg->hWinSrc);
				switch (Id) 
				{				
					case ID_BUTTON_REFRESH: _DeleteFrame(); _CreateFrame(0,0,800,480,&_cbinput);BEEP=0; break;
					case ID_BUTTON_DOWNLOAD:conversation(); STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)conver,SIZE/2);break;
					case ID_BUTTON_UPLOAD: STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)reconv,SIZE/2); reconversation();	break;
          //BUTTON开始					
					case ID_BUTTON_1: state_in=0; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput);  break;									
					case ID_BUTTON_2: state_in=1; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput);  break;									
					case ID_BUTTON_3: state_in=2; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;				
					case ID_BUTTON_4: state_in=3; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;									
					case ID_BUTTON_5: state_in=4; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;									
					case ID_BUTTON_6: state_in=5; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;
					case ID_BUTTON_7: state_in=6; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;									
					case ID_BUTTON_8: state_in=7; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;
					case ID_BUTTON_9: state_in=8; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;									
					case ID_BUTTON_10: state_in=9; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;					

					case ID_BUTTON_11: state_in=10; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput);	break;									
					case ID_BUTTON_12: state_in=11; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;									
					case ID_BUTTON_13: state_in=12; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;				
					case ID_BUTTON_14: state_in=13; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;									
					case ID_BUTTON_15: state_in=14; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;									
					case ID_BUTTON_16: state_in=15; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;
					case ID_BUTTON_17: state_in=16; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;									
					case ID_BUTTON_18: state_in=17; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;
					case ID_BUTTON_19: state_in=18; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;									
					case ID_BUTTON_20: state_in=19; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;		

					case ID_BUTTON_21: state_in=20; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput);	break;									
					case ID_BUTTON_22: state_in=21; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;									
					case ID_BUTTON_23: state_in=22; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;				
					case ID_BUTTON_24: state_in=23; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;									
					case ID_BUTTON_25: state_in=24; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;									
					case ID_BUTTON_26: state_in=25; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;
					case ID_BUTTON_27: state_in=26; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;									
					case ID_BUTTON_28: state_in=27; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;
					case ID_BUTTON_29: state_in=28; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;									
					case ID_BUTTON_30: state_in=29; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;	
					
					case ID_BUTTON_31: state_in=30; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput);	break;									
					case ID_BUTTON_32: state_in=31; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;									
					case ID_BUTTON_33: state_in=32; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;				
					case ID_BUTTON_34: state_in=33; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;									
					case ID_BUTTON_35: state_in=34; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;									
					case ID_BUTTON_36: state_in=35; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;
					case ID_BUTTON_37: state_in=36; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;									
					case ID_BUTTON_38: state_in=37; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;
					case ID_BUTTON_39: state_in=38; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;									
					case ID_BUTTON_40: state_in=39; _DeleteFrame();_CreateFrame(0,0,800,480,&_cboutput); break;	
					//BUTTON结束	
				}
					
					
			}
		break;
			
		default:
		WM_DefaultProc(pMsg);
	}
}
/*
*********************************************************************************************************
*	函 数 名: MainTask
*	功能说明: 主函数
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void MainTask(void) 
{
		OS_ERR err;
	CPU_SR_ALLOC();
	GUI_Init();
	
	/* 使能窗口使用内存设备 */
	WM_SetCreateFlags(WM_CF_MEMDEV);
	
	/* 使能控件的皮肤色 */
	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
	FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
	CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
	DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
	SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
	SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
	HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
	RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
	
	/* 设置桌面窗口的回调函数 */
	WM_SetCallback(WM_HBKWIN, &_cbBkWindow);
	
	/* 进入主界面 */
	_CreateFrame(0,0,800,480,&_cbinput);

	/* 使能UTF8解码 */
//	GUI_UC_SetEncodeUTF8();
	while(1)
	{
	
		 checkout();
		GUI_Delay(100);
	}
}
void conversation(void)
{
	u8 i,j;
	for(j=0;j<40;j++){
	for(i=0;i<5;i++){
	conver[j][i]=(savestate[j][8*i])|(savestate[j][8*i+1]<<1)|(savestate[j][8*i+2]<<2)|(savestate[j][8*i+3]<<3)|(savestate[j][8*i+4]<<4)|(savestate[j][8*i+5]<<5)|(savestate[j][8*i+6]<<6)|(savestate[j][8*i+7]<<7);
	}
}
}
void reconversation(void)
{
	u8 i,j;
	for(j=0;j<40;j++){
	for(i=0;i<5;i++){
	savestate[j][8*i]=(reconv[j][i])&0x01;
	savestate[j][8*i+1]=(reconv[j][i]&0x02)>>1;
	savestate[j][8*i+2]=(reconv[j][i]&0x04)>>2;
	savestate[j][8*i+3]=(reconv[j][i]&0x08)>>3;
	savestate[j][8*i+4]=(reconv[j][i]&0x10)>>4;
	savestate[j][8*i+5]=(reconv[j][i]&0x20)>>5;
	savestate[j][8*i+6]=(reconv[j][i]&0x40)>>6;		
	savestate[j][8*i+7]=(reconv[j][i]&0x80)>>7;		

	}
}
}

