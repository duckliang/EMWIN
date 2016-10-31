/*
*********************************************************************************************************
*	                                  
*	模块名称 : ATM机主界面
*	文件名称 : MainTask.c
*	版    本 : V1.0
*	说    明 : 本工程可以自适应安富莱生产的4.3寸，5寸和7寸屏，操作方法如下：
*              1. 所有界面支持按键操作
*                 （1）K2按键用于控件焦点的切换，切换时，所选择的控件会出现浅色边框
*                 （2）K3按键用于进入下一个界面
*                 （3）摇杆的OK键用于选择相应控件后，触发控件所对应的的操作。
*              2. 如果使用触摸操作的话，请运行emWin教程第三章中的触摸校准程序，此程序
*                 会将触摸参数保存到EEPROM中，然后再运行此工程即可。
*              3. 采用触摸方式操作界面时，如果进入到没有按钮控件时，可以点击屏幕中间部分进入下一页。
*	修改记录 :
*		版本号    日期          作者         说明
*		v1.0    2014-06-03    Eric2013        首发
*	
*	Copyright (C), 2014-2015, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/
#include "includes.h"
#include "MainTask.h"


/*
*********************************************************************************************************
*                                         extern
*********************************************************************************************************
*/ 
extern GUI_CONST_STORAGE GUI_BITMAP bmLogo_AmericanExpress;
extern GUI_CONST_STORAGE GUI_BITMAP bmLogo_ECCard;
extern GUI_CONST_STORAGE GUI_BITMAP bmLogo_GeldKarte;
extern GUI_CONST_STORAGE GUI_BITMAP bmLogo_Maestro;
extern GUI_CONST_STORAGE GUI_BITMAP bmLogo_MasterCard;
extern GUI_CONST_STORAGE GUI_BITMAP bmLogo_VisaCard;
extern GUI_CONST_STORAGE GUI_BITMAP bmLogo_armfly;
extern GUI_CONST_STORAGE GUI_BITMAP bmLogo_armflySmall;

extern GUI_CONST_STORAGE GUI_FONT GUI_FontYahei;

/*
*********************************************************************************************************
*                                       宏定义
*********************************************************************************************************
*/ 
#define BUTTON_CLICK_SPEED        600
#define BUTTON_CLICK_DELAY        750
#define DEFAULT_WIDGET_EFFECT     (&WIDGET_Effect_3D2L)

#define MAIN_BKCOLOR              0xD0D0D0
#define MAIN_TEXTCOLOR            0x000000
#define MAIN_FONT                 (&GUI_FontYahei)
#define MAIN_BORDER               10
#define MAIN_TITLE_HEIGHT         30
#define MAIN_LOGO_BITMAP          (&bmLogo_armflySmall)
#define MAIN_LOGO_OFFSET_X        0
#define MAIN_LOGO_OFFSET_Y        0

#define FRAME_BKCOLOR             0xB0B0B0
#define FRAME_TEXTCOLOR           0x000000
#define FRAME_FONT                (&GUI_FontYahei)
#define FRAME_EFFECT              (&WIDGET_Effect_3D2L)
#define FRAME_BORDER              FRAME_EFFECT->EffectSize
#define FRAME_WIDTH               (LCD_GetXSize() - (FRAME_BORDER * 2) - (MAIN_BORDER * 2))
#define FRAME_HEIGHT              (LCD_GetYSize() - (FRAME_BORDER * 2) - (MAIN_BORDER + MAIN_TITLE_HEIGHT))

#define FRAME_BUTTON_BKCOLOR0     0xB8B8B8              /* Unpressed */
#define FRAME_BUTTON_BKCOLOR1     0xE0E0E0              /* Pressed   */
#define FRAME_BUTTON_BKCOLOR2     0xC0C0C0              /* Disabled  */
#define FRAME_BUTTON_COLOR0       0x000000              /* Unpressed */
#define FRAME_BUTTON_COLOR1       0x000000              /* Pressed   */
#define FRAME_BUTTON_FONT         (&GUI_FontYahei)
#define FRAME_BUTTON_EFFECT       (&WIDGET_Effect_3D2L)

#define LOGO_FRAME_OFFSET_Y       5
#define LOGO_FRAME_SIZE_X         116
#define LOGO_FRAME_SIZE_Y         92
#define LOGO_FRAME_DIST_X         4
#define LOGO_FRAME_BKCOLOR        0xFFFFFF
#define LOGO_FRAME_EFFECT         (&WIDGET_Effect_3D2L)

#define NUMPAD_BKCOLOR            GUI_LIGHTGRAY
#define NUMPAD_EFFECT             (&WIDGET_Effect_3D2L)
#define NUMPAD_BORDER             9
#define NUMPAD_PIN                1685

#define NUMPAD_BUTTON_BKCOLOR0    0xB8B8B8              /* Unpressed */
#define NUMPAD_BUTTON_BKCOLOR1    0xE0E0E0              /* Pressed   */
#define NUMPAD_BUTTON_BKCOLOR2    0xC0C0C0              /* Disabled  */
#define NUMPAD_BUTTON_COLOR0      0x700000              /* Unpressed */
#define NUMPAD_BUTTON_COLOR1      0x700000              /* Pressed   */
#define NUMPAD_BUTTON_RED0        0x0060FF              /* Unpressed */
#define NUMPAD_BUTTON_RED1        0x0030E8              /* Pressed   */
#define NUMPAD_BUTTON_BLUE0       0x00FF00              /* Unpressed */
#define NUMPAD_BUTTON_BLUE1       0x00FF7F              /* Pressed   */
#define NUMPAD_BUTTON_GREEN0      0x00B040              /* Unpressed */
#define NUMPAD_BUTTON_GREEN1      0x00D000              /* Pressed   */
#define NUMPAD_BUTTON_FONT        (&GUI_FontYahei)
#define NUMPAD_BUTTON_EFFECT      (&WIDGET_Effect_3D1L)
#define NUMPAD_BUTTON_WIDTH       40
#define NUMPAD_BUTTON_HEIGHT      32
#define NUMPAD_BUTTON_DIST_X      7
#define NUMPAD_BUTTON_DIST_Y      7

#define ID_FRAMEWIN_0   (GUI_ID_USER + 0x00)
#define ID_BUTTON_0   (GUI_ID_USER + 0x01)
#define ID_BUTTON_1   (GUI_ID_USER + 0x02)
#define ID_BUTTON_2   (GUI_ID_USER + 0x03)
#define ID_BUTTON_3   (GUI_ID_USER + 0x04)
#define ID_BUTTON_4   (GUI_ID_USER + 0x05)
#define ID_BUTTON_5   (GUI_ID_USER + 0x06)
#define ID_BUTTON_6   (GUI_ID_USER + 0x07)
#define ID_BUTTON_7   (GUI_ID_USER + 0x08)
#define ID_BUTTON_8   (GUI_ID_USER + 0x09)
#define ID_BUTTON_9   (GUI_ID_USER + 0x0A)
#define ID_BUTTON_10   (GUI_ID_USER + 0x0B)
#define ID_BUTTON_11   (GUI_ID_USER + 0x0C)
#define ID_BUTTON_12   (GUI_ID_USER + 0x0D)
#define ID_BUTTON_13   (GUI_ID_USER + 0x0E)
#define ID_BUTTON_14   (GUI_ID_USER + 0x0F)
#define ID_BUTTON_15   (GUI_ID_USER + 0x10)
#define ID_BUTTON_16   (GUI_ID_USER + 0x11)
#define ID_BUTTON_17   (GUI_ID_USER + 0x12)
#define ID_BUTTON_18   (GUI_ID_USER + 0x13)
#define ID_BUTTON_19   (GUI_ID_USER + 0x14)
#define ID_BUTTON_20   (GUI_ID_USER + 0x15)
#define ID_BUTTON_21   (GUI_ID_USER + 0x16)
#define ID_BUTTON_22   (GUI_ID_USER + 0x17)
#define ID_BUTTON_23   (GUI_ID_USER + 0x18)
#define ID_BUTTON_24   (GUI_ID_USER + 0x19)
#define ID_BUTTON_25   (GUI_ID_USER + 0x1A)
#define ID_BUTTON_26   (GUI_ID_USER + 0x1B)
#define ID_BUTTON_27   (GUI_ID_USER + 0x1C)
#define ID_BUTTON_28   (GUI_ID_USER + 0x1D)
#define ID_BUTTON_29   (GUI_ID_USER + 0x1E)
#define ID_BUTTON_30   (GUI_ID_USER + 0x1F)
#define ID_BUTTON_31   (GUI_ID_USER + 0x20)
#define ID_BUTTON_32   (GUI_ID_USER + 0x21)
#define ID_BUTTON_33   (GUI_ID_USER + 0x22)
#define ID_BUTTON_34   (GUI_ID_USER + 0x23)
#define ID_BUTTON_35   (GUI_ID_USER + 0x24)
#define ID_BUTTON_36   (GUI_ID_USER + 0x25)
#define ID_BUTTON_37   (GUI_ID_USER + 0x26)
#define ID_BUTTON_38   (GUI_ID_USER + 0x27)
#define ID_BUTTON_39   (GUI_ID_USER + 0x28)

#define ID_CHECKBOX_0   (GUI_ID_USER + 0x30)
#define ID_CHECKBOX_1   (GUI_ID_USER + 0x31)
#define ID_CHECKBOX_2   (GUI_ID_USER + 0x32)
#define ID_CHECKBOX_3   (GUI_ID_USER + 0x33)
#define ID_CHECKBOX_4   (GUI_ID_USER + 0x34)
/*
*********************************************************************************************************
*                                       宏定义-常数
*********************************************************************************************************
*/
//#define NUMPAD_ID_0         (GUI_ID_USER +  0)
//#define NUMPAD_ID_1         (GUI_ID_USER +  1)
//#define NUMPAD_ID_2         (GUI_ID_USER +  2)
//#define NUMPAD_ID_3         (GUI_ID_USER +  3)
//#define NUMPAD_ID_4         (GUI_ID_USER +  4)
//#define NUMPAD_ID_5         (GUI_ID_USER +  5)
//#define NUMPAD_ID_6         (GUI_ID_USER +  6)
//#define NUMPAD_ID_7         (GUI_ID_USER +  7)
//#define NUMPAD_ID_8         (GUI_ID_USER +  8)
//#define NUMPAD_ID_9         (GUI_ID_USER +  9)
//#define NUMPAD_ID_X         (GUI_ID_USER + 10)
//#define NUMPAD_ID_Y         (GUI_ID_USER + 11)
//#define NUMPAD_ID_A         (GUI_ID_USER + 12)
//#define NUMPAD_ID_B         (GUI_ID_USER + 13)
//#define NUMPAD_ID_C         (GUI_ID_USER + 14)
//#define NUMPAD_ID_D         (GUI_ID_USER + 15)

#define MSG_CARD_INSERTED   (WM_USER + 0)
#define MSG_CARD_REMOVED    (WM_USER + 1)
#define MSG_MONEY_REMOVED   (WM_USER + 2)
#define MSG_PIN_CHANGED     (WM_USER + 3)
#define MSG_PIN_OK          (WM_USER + 4)
#define MSG_PIN_CANCEL      (WM_USER + 5)
#define MSG_PIN_ERROR       (WM_USER + 6)

#define LANG_GER 0
#define LANG_ENG 1

#define TEXT_ID_ABBRUCH             1
#define TEXT_ID_KORREKTUR           2
#define TEXT_ID_BESTAETIGEN         3
#define TEXT_ID_PIN_EINGEBEN        4
#define TEXT_ID_KARTE_EINFUEHREN    5
#define TEXT_ID_GELD_ABHEBEN        6
#define TEXT_ID_KONTOSTAND_ANSEHEN  7
#define TEXT_ID_AUSWAHL_TREFFEN     8
#define TEXT_ID_ANDERER_BETRAG      9
#define TEXT_ID_BITTE_GEDULD        10
#define TEXT_ID_KARTE_ENTNEHMEN     11
#define TEXT_ID_GELD_ENTNEHMEN      12
#define TEXT_ID_VIELEN_DANK         13
#define TEXT_ID_GELDAUTOMAT         14
#define TEXT_ID_KONTOSTAND          15
#define TEXT_ID_AUSWAHL_BETRAG      16
#define TEXT_ID_FALSCHE_PIN         17
#define TEXT_ID_BETRAG_EINGEBEN     18

/*
*********************************************************************************************************
*                                       结构体
*********************************************************************************************************
*/
typedef struct {
  int x;
  int y;
  int Pressed;
  int Duration;
} PID_EVENT;

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 800, 480, 0, 0x64, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 0, 0, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 0, 400, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_2, 600, 0, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_3, 0, 300, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_4, 0, 200, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_5, 700, 0, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_6, 500, 0, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_7, 400, 0, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_8, 300, 0, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_9, 200, 0, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_10, 100, 0, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_11, 1, 100, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_12, 500, 400, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_13, 500, 300, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_14, 500, 200, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_15, 500, 100, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_16, 400, 400, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_17, 400, 300, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_18, 400, 200, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_19, 400, 100, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_20, 300, 400, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_21, 300, 300, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_22, 300, 200, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_23, 300, 100, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_24, 200, 400, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_25, 200, 300, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_26, 200, 200, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_27, 200, 100, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_28, 100, 400, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_29, 100, 300, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_30, 100, 200, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_31, 100, 100, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_32, 700, 200, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_33, 700, 100, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_34, 600, 400, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_35, 600, 300, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_36, 600, 200, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_37, 600, 100, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_38, 700, 300, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_39, 700, 400, 80, 40, 0, 0x0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};
/*
*********************************************************************************************************
*                                       静态数据
*********************************************************************************************************
*/
static const char * _aLang[][2] = {
  { "取消",
    "Cancel"
  },
  { "更正",
    "Correction"
  },
  { "确认",
    "Confirm"
  },
  { "",
    "Please enter your PIN:"
  },
  { "请插入卡",
    "Please insert your card"
  },
  { "取钱",
    "Draw money"
  },
  { "查看账户余额",
    "View account balance"
  },
  { "请选择",
    "Please select..."
  },
  { " ",
    "Different amount"
  },
  { " ",
    "Please wait until your transaction\nis being processed."
  },
  { " ",
    "Please you take your card"
  },
  { " ",
    "Transaction completed.\nPlease take your money"
  },
  { " ",
    "Thank you for\nusing"
  },
  { " ",
    "ATM"
  },
  { " ",
    "Your balance amount is: -1234.56 RMB"
  },
  { " ",
    "Please select amount"
  },
  { " ",
    "Wrong PIN. At least 4 digits"
  },
  { " ",
    "Please enter amount"
  },
};

static WM_HWIN    _hLastFrame;
static WM_HWIN    _hNumPad;

static unsigned   _PIN_Value;
static unsigned   _PIN_Digits;

static unsigned   _Language;
static WM_HWIN    _hTitle;

/*
*********************************************************************************************************
*	函 数 名: _GetLang
*	功能说明: 获取要显示字符串的地址
*	形    参：Index  要显示字符串的序号
*	返 回 值: p      返回要显示字符串地址
*********************************************************************************************************
*/
static const char * _GetLang(unsigned Index) 
{
	const char * p;
	
	p = NULL;
	Index--;
	
	if ((Index < GUI_COUNTOF(_aLang)) && (_Language < GUI_COUNTOF(_aLang[0]))) 
	{
		p = _aLang[Index][_Language];
	}
	
	return p;
}

/*
*********************************************************************************************************
*	函 数 名: _DrawDownRectEx
*	功能说明: 显示凹陷的矩形框
*	形    参：pEffect  控件显示效果
*             pRect    GUI_RECT类型变量地址
*	返 回 值: 无
*********************************************************************************************************
*/
static void _DrawDownRectEx(const WIDGET_EFFECT* pEffect, const GUI_RECT* pRect) 
{
	WM_LOCK();
	pEffect->pfDrawDownRect(pRect);
	WM_UNLOCK();
}

/*
*********************************************************************************************************
*	函 数 名: _DrawDownRect
*	功能说明: 显示凹陷的矩形框
*	形    参：pEffect  控件显示效果
*             x0       起始x轴坐标
*             y0       起始y轴坐标
*             x1       结束x轴坐标
*             y1       结束y轴坐标
*	返 回 值: 无
*********************************************************************************************************
*/
static void _DrawDownRect(const WIDGET_EFFECT* pEffect, int x0, int y0, int x1, int y1) 
{
	GUI_RECT r;
	
	r.x0 = x0;
	r.y0 = y0;
	r.x1 = x1;
	r.y1 = y1;
	_DrawDownRectEx(pEffect, &r);
}

/*
*********************************************************************************************************
*	函 数 名: _DrawUpRectEx
*	功能说明: 显示凸起的矩形框
*	形    参：pEffect  控件显示效果
*             pRect    GUI_RECT类型变量地址
*	返 回 值: 无
*********************************************************************************************************
*/
static void _DrawUpRectEx(const WIDGET_EFFECT* pEffect, const GUI_RECT* pRect) 
{
	WM_LOCK();
	pEffect->pfDrawUpRect(pRect);
	WM_UNLOCK();
}

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
	GUI_SetBkColor(FRAME_BKCOLOR);
	GUI_SetColor(FRAME_TEXTCOLOR);
	GUI_SetFont(FRAME_FONT);
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
static WM_HWIN _CreateFrame(WM_CALLBACK* cb) 
{
	int x = 0;
	int y = 0;
	x = FRAME_BORDER + MAIN_BORDER;
	y = FRAME_BORDER + MAIN_TITLE_HEIGHT;
//	_hLastFrame = WM_CreateWindowAsChild(x, y, FRAME_WIDTH, FRAME_HEIGHT, WM_HBKWIN, WM_CF_SHOW, cb, 0);
		_hLastFrame = WM_CreateWindowAsChild(0, 0, 800, 440, WM_HBKWIN, WM_CF_SHOW, cb, 0);
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
static WM_HWIN _CreateButton(WM_HWIN hParent, const char* pText, int Id, int x, int y, int w, int h, unsigned TextId) 
{
	WM_HWIN hButton;
	hButton = BUTTON_CreateEx(x, y, w, h, hParent, WM_CF_SHOW, 0, Id);
	
	/* 获取当前创建按钮要显示的文本 */
	if (TextId) 
	{
		pText = _GetLang(TextId);
	}
	BUTTON_SetText      (hButton,    pText);
	BUTTON_SetFont      (hButton,    FRAME_BUTTON_FONT);
	BUTTON_SetBkColor   (hButton, 0, FRAME_BUTTON_BKCOLOR0);
	BUTTON_SetBkColor   (hButton, 1, FRAME_BUTTON_BKCOLOR1);
	BUTTON_SetBkColor   (hButton, 2, FRAME_BUTTON_BKCOLOR2);
	BUTTON_SetTextColor (hButton, 0, FRAME_BUTTON_COLOR0);
	BUTTON_SetTextColor (hButton, 1, FRAME_BUTTON_COLOR1);
	BUTTON_SetTextColor (hButton, 2, FRAME_BUTTON_COLOR0);
	WIDGET_SetEffect    (hButton,    FRAME_BUTTON_EFFECT);
	
	/* 设置接收输入焦点的能力 */
	BUTTON_SetFocussable(hButton,    1);
	
	return hButton;
}

static WM_HWIN _CreateCheckbox(WM_HWIN hParent, const char* pText, int Id, int x, int y, int w, int h, unsigned TextId) 
{
	WM_HWIN hCheckbox;
	hCheckbox =CHECKBOX_CreateEx(x, y, w, h, hParent, WM_CF_SHOW, 0, Id);
	
	/* 获取当前创建按钮要显示的文本 */
	if (TextId) 
	{
		pText = _GetLang(TextId);
	}
	CHECKBOX_SetText      (hCheckbox,    pText);
//	CHECKBOX_SetFont      (hCheckbox,    FRAME_BUTTON_FONT);
//	CHECKBOX_SetBkColor   (hCheckbox,  FRAME_BUTTON_BKCOLOR0);
//	CHECKBOX_SetBkColor   (hCheckbox,  FRAME_BUTTON_BKCOLOR1);
//	CHECKBOX_SetBkColor   (hCheckbox,  FRAME_BUTTON_BKCOLOR2);
//	CHECKBOX_SetTextColor (hCheckbox,  FRAME_BUTTON_COLOR0);
//	CHECKBOX_SetTextColor (hCheckbox,  FRAME_BUTTON_COLOR1);
//	CHECKBOX_SetTextColor (hCheckbox,  FRAME_BUTTON_COLOR0);
//	WIDGET_SetEffect    (hCheckbox,    FRAME_BUTTON_EFFECT);
	
	/* 设置接收输入焦点的能力 */
//	CHECKBOX_SetFocussable(hCheckbox,    1);
	
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
//				int x, y, w, h;
//				
				GUI_SetBkColor(MAIN_BKCOLOR);
				GUI_SetColor(MAIN_TEXTCOLOR);
				GUI_SetFont(MAIN_FONT);
				GUI_Clear();
//				x = MAIN_LOGO_OFFSET_X + MAIN_BORDER;
//				y = MAIN_LOGO_OFFSET_Y + ((MAIN_TITLE_HEIGHT - MAIN_LOGO_BITMAP->YSize) >> 1);
//				GUI_DrawBitmap(MAIN_LOGO_BITMAP, x, y);
//				x = MAIN_BORDER;
//				y = MAIN_TITLE_HEIGHT;
//				w = LCD_GetXSize() - (MAIN_BORDER * 2);
//				h = LCD_GetYSize()  - (MAIN_BORDER + MAIN_TITLE_HEIGHT);
//				_DrawDownRect(FRAME_EFFECT, x, y, x + w - 1, y + h - 1);
			} 
			break;
		default:
			WM_DefaultProc(pMsg);
	}
}

/*
*********************************************************************************************************
*	函 数 名: _cbEnterPIN
*	功能说明: 第三个界面，输入密码
*	形    参：pMsg  参数指针
*	返 回 值: 无
*********************************************************************************************************
*/
static void _cbInsertCard(WM_MESSAGE* pMsg);
static void _cbEnterPIN(WM_MESSAGE* pMsg) 
{
	WM_HWIN hItem, hWin = pMsg->hWin;
	static int PinError;
	
	switch (pMsg->MsgId) 
	{
		case WM_CREATE:
			/* 创建后，设置聚焦 */
			PinError = 0;
			WM_SetFocus(hWin);
		    /* 创建小键盘,数值55是下面编辑框的高度和起始位置的和30+25=55*/
//			_CreateNumPad(hWin, FRAME_WIDTH >> 1, (55 + FRAME_HEIGHT)>>1);
			hItem = EDIT_CreateEx((FRAME_WIDTH >> 1) - 50, 30, 100, 25, hWin, WM_CF_SHOW, 0, GUI_ID_EDIT0, 4);
			EDIT_SetFont(hItem, &GUI_FontYahei);
			EDIT_SetTextAlign(hItem, GUI_TA_CENTER);
			WIDGET_SetEffect(hItem, DEFAULT_WIDGET_EFFECT);
			WM_DisableWindow(hItem);
			break;
		case WM_PAINT:
			_PaintFrame();
		    /* 为了方便显示，这里将密码输入错误时的文本和这个界面的小标题显示在一个位置上 */
			if (PinError) 
			{
				_PIN_Digits = 0;
				GUI_SetColor(GUI_RED);
				GUI_DispStringHCenterAt(_GetLang(TEXT_ID_FALSCHE_PIN), FRAME_WIDTH >> 1, 0);
				WM_CreateTimer(hWin, 0, 1000, 0);
			}
			else
			{
				GUI_DispStringHCenterAt(_GetLang(TEXT_ID_PIN_EINGEBEN), FRAME_WIDTH >> 1, 0);
			}
			
			/* 这里是将密码输入错误时的文本和这个界面的小标题显示在不同位置上 */
			/*
			GUI_DispStringHCenterAt(_GetLang(TEXT_ID_PIN_EINGEBEN), FRAME_WIDTH >> 1, 0);
			if (PinError) 
			{
				_PIN_Digits = 0;
				GUI_SetColor(GUI_RED);
				GUI_DispStringHCenterAt(_GetLang(TEXT_ID_FALSCHE_PIN), FRAME_WIDTH >> 1, 0);
				WM_CreateTimer(hWin, 0, 1000, 0);
			}
			*/
			
			break;
		case WM_TIMER:
			/* 密码输入错误，1s后将编辑框中的密码清除 */
			PinError = 0;
			EDIT_SetText(WM_GetDialogItem(hWin, GUI_ID_EDIT0), "");
			/* 使能重绘 */
			WM_InvalidateWindow(hWin);
			break;
		case MSG_PIN_ERROR:
			/* 密码输入错误，使能重绘 */
			PinError++;
			WM_InvalidateWindow(hWin);
			break;
		case MSG_PIN_OK:
			/* 密码输入正确，进入下一个界面 */
//			_DeleteNumPad();
			_DeleteFrame();
//			_CreateFrame(&_cbMainMenu);
			break;
		case MSG_PIN_CANCEL:
			/* 取消，返回到上一个界面 */
//			_DeleteNumPad();
			_DeleteFrame();
			_CreateFrame(&_cbInsertCard);
			break;
		case MSG_PIN_CHANGED:
			/* 输入密码实时更新 */
			if (_PIN_Digits == 0) 
			{
				EDIT_SetText(WM_GetDialogItem(hWin, GUI_ID_EDIT0), "");
			} 
			else if (_PIN_Digits == 1) 
			{
				EDIT_SetText(WM_GetDialogItem(hWin, GUI_ID_EDIT0), "x");
			} 
			else if (_PIN_Digits == 2) 
			{
				EDIT_SetText(WM_GetDialogItem(hWin, GUI_ID_EDIT0), "xx");
			} 
			else if (_PIN_Digits == 3) 
			{
				EDIT_SetText(WM_GetDialogItem(hWin, GUI_ID_EDIT0), "xxx");
			} else if (_PIN_Digits == 4) 
			{
				EDIT_SetText(WM_GetDialogItem(hWin, GUI_ID_EDIT0), "xxxx");
			}
			break;
		default:
			WM_DefaultProc(pMsg);
	}
}

/*
*********************************************************************************************************
*	函 数 名: _cbInsertCard
*	功能说明: 第二个界面，等待用户插入银行卡
*	形    参：pMsg  参数指针
*	返 回 值: 无
*********************************************************************************************************
*/
static void _cbInsertCard(WM_MESSAGE* pMsg) 
{
	WM_HWIN hWin = pMsg->hWin;
	switch (pMsg->MsgId) 
	{
		case WM_CREATE:
			/* 设置聚焦 */
			WM_SetFocus(hWin);
			break;
//		case WM_KEY:
//            switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) 
//            { 
//				case GUI_KEY_ESCAPE:
//                    GUI_EndDialog(hWin, 1);
//                    break;
//				case GUI_KEY_TAB:
//					WM_SetFocusOnNextChild(hWin);
//					break;
//				case GUI_KEY_NextPage:
//					{
//						GUI_PID_STATE CurrentState;
//						CurrentState.x = WM_GetWindowOrgX(hWin);
//						CurrentState.y = WM_GetWindowOrgY(hWin);
//						CurrentState.Layer = 0;
//						CurrentState.Pressed = 1;
//						GUI_PID_StoreState(&CurrentState);
//					}
//					break;
//            }
//            break;
		case WM_PAINT:
			_PaintFrame();
//			_DrawLogoBox(0, &bmLogo_ECCard);
//			_DrawLogoBox(1, &bmLogo_Maestro);
//			_DrawLogoBox(2, &bmLogo_MasterCard);
//			_DrawLogoBox(3, &bmLogo_VisaCard);
//			_DrawLogoBox(4, &bmLogo_AmericanExpress);
			GUI_DispStringHCenterAt(_GetLang(TEXT_ID_KARTE_EINFUEHREN), FRAME_WIDTH >> 1, 15);
			break;
		case WM_TOUCH:
			if (((GUI_PID_STATE *)pMsg->Data.p)->Pressed == 1) 
			{
				_DeleteFrame();
				_CreateFrame(&_cbEnterPIN);
			}
			break;
		default:
			WM_DefaultProc(pMsg);
	}
}

/*
*********************************************************************************************************
*	函 数 名: _cbLanguage
*	功能说明: 第一个界面，用于中文和英语的选择
*	形    参：pMsg  参数指针
*	返 回 值: 无
*********************************************************************************************************
*/static void _cbDialog3(WM_MESSAGE * pMsg);
static void _cbLanguage(WM_MESSAGE* pMsg) 
{
	WM_HWIN hWin = pMsg->hWin;
	switch (pMsg->MsgId) 
	{
		case WM_CREATE:
			/* 设置聚焦 */
			WM_SetFocus(hWin);
			/* 创建两个按钮，用于选择中文和英文 */
			_CreateButton(hWin, "中文", GUI_ID_BUTTON0, (FRAME_WIDTH >> 1) - 150, 80, 300,  50, 0);
			_CreateButton(hWin, "English", GUI_ID_BUTTON1, (FRAME_WIDTH >> 1) - 150, 150, 300,  50, 0);
			break;
//		 case WM_KEY:
//            switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) 
//            { 
//				case GUI_KEY_ESCAPE:
//                    GUI_EndDialog(hWin, 1);
//                    break;
//				case GUI_KEY_TAB:
//					WM_SetFocusOnNextChild(hWin);
//					break;
//            }
//            break;
		case WM_PAINT:
			_PaintFrame();
		  GUI_DispStringHCenterAt("请选择语言", FRAME_WIDTH >> 1, 5);
			GUI_DispStringHCenterAt("Please select your language", FRAME_WIDTH >> 1, 32);
			break;
		case WM_NOTIFY_PARENT:
			if (pMsg->Data.v == WM_NOTIFICATION_RELEASED) 
			{
				int Id = WM_GetId(pMsg->hWinSrc);
				switch (Id) 
				{
					case GUI_ID_BUTTON0:
//						_Language = 0;
				_DeleteFrame();
				_CreateFrame(&_cbDialog3);
						break;
					case GUI_ID_BUTTON1:
						_Language = 1;
						break;
				}
//				/* 创建标题，居中显示 */
//				_hTitle = TEXT_CreateEx(0, 0, LCD_GetXSize(), 32, WM_HBKWIN, WM_CF_SHOW, 0, GUI_ID_TEXT0, _GetLang(TEXT_ID_GELDAUTOMAT));
//				TEXT_SetTextAlign(_hTitle, GUI_TA_HCENTER);
//				TEXT_SetFont(_hTitle, MAIN_FONT);
//				/* 删除这个创建的界面 */
//				_DeleteFrame();
//				_CreateFrame(&_cbInsertCard);
			}
			break;
		default:
		WM_DefaultProc(pMsg);
	}
}
static void _cbDialog3(WM_MESSAGE * pMsg){
	WM_HWIN hWin = pMsg->hWin;
	int     NCode;
  int     Id;
	switch (pMsg->MsgId) 
	{
		case WM_CREATE:
			/* 设置聚焦 */
			WM_SetFocus(hWin);
			/* 创建两个按钮，用于选择中文和英文 */
		  _CreateCheckbox(hWin, "1", ID_CHECKBOX_0, 0, 20, 80,  20, 0);
		  _CreateCheckbox(hWin, "2", ID_CHECKBOX_1, 100, 20, 80,  20, 0);
		  _CreateCheckbox(hWin, "3", ID_CHECKBOX_2, 200, 20, 80,  20, 0);
			_CreateCheckbox(hWin, "4", ID_CHECKBOX_3, 300, 20, 80,  20, 0);
//			_CreateButton(hWin, "中文", GUI_ID_BUTTON0, (FRAME_WIDTH >> 1) - 150, 80, 300,  50, 0);
//			_CreateButton(hWin, "English", GUI_ID_BUTTON1, (FRAME_WIDTH >> 1) - 150, 150, 300,  50, 0);
		
			break;
//		 case WM_KEY:
//            switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) 
//            { 
//				case GUI_KEY_ESCAPE:
//                    GUI_EndDialog(hWin, 1);
//                    break;
//				case GUI_KEY_TAB:
//					WM_SetFocusOnNextChild(hWin);
//					break;
//            }
//            break;
		case WM_PAINT:
			_PaintFrame();
			GUI_DispStringHCenterAt("Please click output", FRAME_WIDTH >> 1, 32);
			break;
		case WM_NOTIFY_PARENT:
//			if (pMsg->Data.v == WM_NOTIFICATION_RELEASED) 
//			{
//				int Id = WM_GetId(pMsg->hWinSrc);
//				switch (Id) 
//				{
//					case GUI_ID_BUTTON0:
//						_Language = 0;
//						break;
//					case GUI_ID_BUTTON1:
//						_Language = 1;
//						break;
//				}
//				/* 创建标题，居中显示 */
//				_hTitle = TEXT_CreateEx(0, 0, LCD_GetXSize(), 32, WM_HBKWIN, WM_CF_SHOW, 0, GUI_ID_TEXT0, _GetLang(TEXT_ID_GELDAUTOMAT));
//				TEXT_SetTextAlign(_hTitle, GUI_TA_HCENTER);
//				TEXT_SetFont(_hTitle, MAIN_FONT);
//				/* 删除这个创建的界面 */
//				_DeleteFrame();
//				_CreateFrame(&_cbInsertCard);
//			}
		 Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_CHECKBOX_0: // Notifications sent by 'Checkbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_CHECKBOX_1: // Notifications sent by 'Checkbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_CHECKBOX_2: // Notifications sent by 'Checkbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_CHECKBOX_3: // Notifications sent by 'Checkbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    }
			break;
		default:
		WM_DefaultProc(pMsg);
	}
}
 void _cbDialog1(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  // USER START (Optionally insert additional variables)
  // USER END
  switch (pMsg->MsgId) {
//	case WM_CREATE:
	
  case WM_INIT_DIALOG:
//    //
//    // Initialization of 'Framewin'
//    //
    hItem = pMsg->hWin;
		WM_SetFocus(hItem);
    FRAMEWIN_SetTitleHeight(hItem, 30);
    FRAMEWIN_SetTextColor(hItem, 0x0000FF00);
    FRAMEWIN_SetText(hItem, "please click  input");
    FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    FRAMEWIN_SetFont(hItem, GUI_FONT_24B_ASCII);
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetText(hItem, "1");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
    BUTTON_SetText(hItem, "33");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
    BUTTON_SetText(hItem, "7");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
    BUTTON_SetText(hItem, "25");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_4);
    BUTTON_SetText(hItem, "17");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5);
    BUTTON_SetText(hItem, "8");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_6);
    BUTTON_SetText(hItem, "6");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_7);
    BUTTON_SetText(hItem, "5");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_8);
    BUTTON_SetText(hItem, "4");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_9);
    BUTTON_SetText(hItem, "3");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_10);
    BUTTON_SetText(hItem, "2");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_11);
    BUTTON_SetText(hItem, "9");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_12);
    BUTTON_SetText(hItem, "38");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_13);
    BUTTON_SetText(hItem, "30");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_14);
    BUTTON_SetText(hItem, "22");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_15);
    BUTTON_SetText(hItem, "14");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_16);
    BUTTON_SetText(hItem, "37");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_17);
    BUTTON_SetText(hItem, "29");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_18);
    BUTTON_SetText(hItem, "21");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_19);
    BUTTON_SetText(hItem, "13");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_20);
    BUTTON_SetText(hItem, "36");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_21);
    BUTTON_SetText(hItem, "28");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_22);
    BUTTON_SetText(hItem, "20");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_23);
    BUTTON_SetText(hItem, "12");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_24);
    BUTTON_SetText(hItem, "35");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_25);
    BUTTON_SetText(hItem, "27");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_26);
    BUTTON_SetText(hItem, "19");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_27);
    BUTTON_SetText(hItem, "11");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_28);
    BUTTON_SetText(hItem, "34");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_29);
    BUTTON_SetText(hItem, "26");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_30);
    BUTTON_SetText(hItem, "18");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_31);
    BUTTON_SetText(hItem, "10");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_32);
    BUTTON_SetText(hItem, "24");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_33);
    BUTTON_SetText(hItem, "16");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_34);
    BUTTON_SetText(hItem, "39");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_35);
    BUTTON_SetText(hItem, "31");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_36);
    BUTTON_SetText(hItem, "23");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_37);
    BUTTON_SetText(hItem, "15");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_38);
    BUTTON_SetText(hItem, "32");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_39);
    BUTTON_SetText(hItem, "40");
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_BUTTON_0: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
//				_hTitle = TEXT_CreateEx(0, 0, LCD_GetXSize(), 32, WM_HBKWIN, WM_CF_SHOW, 0, GUI_ID_TEXT0, _GetLang(TEXT_ID_GELDAUTOMAT));
//				TEXT_SetTextAlign(_hTitle, GUI_TA_HCENTER);
//				TEXT_SetFont(_hTitle, MAIN_FONT);
				/* 删除这个创建的界面 */
				_DeleteFrame();
				_CreateFrame(&_cbLanguage);
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_2: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_3: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_4: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_5: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_6: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_7: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_8: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_9: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_10: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_11: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_12: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_13: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_14: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_15: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_16: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_17: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_18: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_19: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_20: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_21: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_22: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_23: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_24: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_25: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_26: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_27: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_28: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_29: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_30: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_31: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_32: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_33: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_34: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_35: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_36: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_37: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_38: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_39: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}
 WM_HWIN CreateFramewin1(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog1, WM_HBKWIN, 0, 0);
  return hWin;
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
	GUI_Init();
	
	/* 使能窗口使用内存设备 */
	WM_SetCreateFlags(WM_CF_MEMDEV);
	
	/* 使能控件的皮肤色 */
//	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
//	FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
//	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
//	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
//	CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
//	DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
//	SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
//	SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
//	HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
//	RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
	
	/* 设置桌面窗口的回调函数 */
	WM_SetCallback(WM_HBKWIN, &_cbBkWindow);
	
	/* 进入主界面 */
	_CreateFrame(&_cbLanguage);
//	_CreateFrame(&_cbDialog1);

	/* 使能UTF8解码 */
//	GUI_UC_SetEncodeUTF8();
//	CreateFramewin1();
	while(1)
	{
		GUI_Delay(10);
	}
}

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
