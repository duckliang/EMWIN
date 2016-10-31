#ifndef _MYTASK_H
#define _MYTASK_H
#include "sys.h"

#include "GUI.h"
#include "DIALOG.h"
#include "WM.h"
#include "BUTTON.h"
#include "CHECKBOX.h"
#include "DROPDOWN.h"
#include "EDIT.h"
#include "FRAMEWIN.h"
#include "LISTBOX.h"
#include "MULTIEDIT.h"
#include "RADIO.h"
#include "SLIDER.h"
#include "TEXT.h"
#include "PROGBAR.h"
#include "SCROLLBAR.h"
#include "LISTVIEW.h"
#include "GRAPH.h"
#include "MENU.h"
#include "MULTIPAGE.h"
#include "ICONVIEW.h"
#include "TREEVIEW.h"

#define WM_RECOLOR  (WM_USER+0x01)
#define ID_BUTTON_1   (GUI_ID_USER + 0x01)
#define ID_BUTTON_2   (GUI_ID_USER + 0x02)
#define ID_BUTTON_3   (GUI_ID_USER + 0x03)
#define ID_BUTTON_4   (GUI_ID_USER + 0x04)
#define ID_BUTTON_5   (GUI_ID_USER + 0x05)
#define ID_BUTTON_6   (GUI_ID_USER + 0x06)
#define ID_BUTTON_7   (GUI_ID_USER + 0x07)
#define ID_BUTTON_8   (GUI_ID_USER + 0x08)
#define ID_BUTTON_9   (GUI_ID_USER + 0x09)
#define ID_BUTTON_10   (GUI_ID_USER + 0x0A)
#define ID_BUTTON_11   (GUI_ID_USER + 0x0B)
#define ID_BUTTON_12   (GUI_ID_USER + 0x0C)
#define ID_BUTTON_13   (GUI_ID_USER + 0x0D)
#define ID_BUTTON_14   (GUI_ID_USER + 0x0E)
#define ID_BUTTON_15   (GUI_ID_USER + 0x0F)
#define ID_BUTTON_16   (GUI_ID_USER + 0x10)
#define ID_BUTTON_17   (GUI_ID_USER + 0x11)
#define ID_BUTTON_18   (GUI_ID_USER + 0x12)
#define ID_BUTTON_19   (GUI_ID_USER + 0x13)
#define ID_BUTTON_20   (GUI_ID_USER + 0x14)
#define ID_BUTTON_21   (GUI_ID_USER + 0x15)
#define ID_BUTTON_22   (GUI_ID_USER + 0x16)
#define ID_BUTTON_23   (GUI_ID_USER + 0x17)
#define ID_BUTTON_24   (GUI_ID_USER + 0x18)
#define ID_BUTTON_25   (GUI_ID_USER + 0x19)
#define ID_BUTTON_26   (GUI_ID_USER + 0x1A)
#define ID_BUTTON_27   (GUI_ID_USER + 0x1B)
#define ID_BUTTON_28   (GUI_ID_USER + 0x1C)
#define ID_BUTTON_29   (GUI_ID_USER + 0x1D)
#define ID_BUTTON_30   (GUI_ID_USER + 0x1E)
#define ID_BUTTON_31   (GUI_ID_USER + 0x1F)
#define ID_BUTTON_32   (GUI_ID_USER + 0x20)
#define ID_BUTTON_33   (GUI_ID_USER + 0x21)
#define ID_BUTTON_34   (GUI_ID_USER + 0x22)
#define ID_BUTTON_35   (GUI_ID_USER + 0x23)
#define ID_BUTTON_36   (GUI_ID_USER + 0x24)
#define ID_BUTTON_37   (GUI_ID_USER + 0x25)
#define ID_BUTTON_38   (GUI_ID_USER + 0x26)
#define ID_BUTTON_39   (GUI_ID_USER + 0x27)
#define ID_BUTTON_40   (GUI_ID_USER + 0x28)
#define ID_BUTTON_OK   (GUI_ID_USER + 0x29)
#define ID_BUTTON_CANCLE   (GUI_ID_USER + 0x2A)
#define ID_BUTTON_BACK   (GUI_ID_USER + 0x2B)
#define ID_BUTTON_REFRESH (GUI_ID_USER + 0x2C)

#define ID_CHECKBOX_1  (GUI_ID_USER + 0x31)
#define ID_CHECKBOX_2  (GUI_ID_USER + 0x32)
#define ID_CHECKBOX_3  (GUI_ID_USER + 0x33)
#define ID_CHECKBOX_4  (GUI_ID_USER + 0x34)
#define ID_CHECKBOX_5  (GUI_ID_USER + 0x35)
#define ID_CHECKBOX_6  (GUI_ID_USER + 0x36)
#define ID_CHECKBOX_7  (GUI_ID_USER + 0x37)
#define ID_CHECKBOX_8  (GUI_ID_USER + 0x38)
#define ID_CHECKBOX_9  (GUI_ID_USER + 0x39)
#define ID_CHECKBOX_10  (GUI_ID_USER + 0x3A)
#define ID_CHECKBOX_11  (GUI_ID_USER + 0x3B)
#define ID_CHECKBOX_12  (GUI_ID_USER + 0x3C)
#define ID_CHECKBOX_13  (GUI_ID_USER + 0x3D)
#define ID_CHECKBOX_14  (GUI_ID_USER + 0x3E)
#define ID_CHECKBOX_15  (GUI_ID_USER + 0x3F)
#define ID_CHECKBOX_16  (GUI_ID_USER + 0x40)
#define ID_CHECKBOX_17  (GUI_ID_USER + 0x41)
#define ID_CHECKBOX_18  (GUI_ID_USER + 0x42)
#define ID_CHECKBOX_19  (GUI_ID_USER + 0x43)
#define ID_CHECKBOX_20  (GUI_ID_USER + 0x44)
#define ID_CHECKBOX_21  (GUI_ID_USER + 0x45)
#define ID_CHECKBOX_22  (GUI_ID_USER + 0x46)
#define ID_CHECKBOX_23  (GUI_ID_USER + 0x47)
#define ID_CHECKBOX_24  (GUI_ID_USER + 0x48)
#define ID_CHECKBOX_25  (GUI_ID_USER + 0x49)
#define ID_CHECKBOX_26  (GUI_ID_USER + 0x4A)
#define ID_CHECKBOX_27  (GUI_ID_USER + 0x4B)
#define ID_CHECKBOX_28  (GUI_ID_USER + 0x4C)
#define ID_CHECKBOX_29  (GUI_ID_USER + 0x4D)
#define ID_CHECKBOX_30  (GUI_ID_USER + 0x4E)
#define ID_CHECKBOX_31  (GUI_ID_USER + 0x4F)
#define ID_CHECKBOX_32  (GUI_ID_USER + 0x50)
#define ID_CHECKBOX_33  (GUI_ID_USER + 0x51)
#define ID_CHECKBOX_34  (GUI_ID_USER + 0x52)
#define ID_CHECKBOX_35  (GUI_ID_USER + 0x53)
#define ID_CHECKBOX_36  (GUI_ID_USER + 0x54)
#define ID_CHECKBOX_37  (GUI_ID_USER + 0x55)
#define ID_CHECKBOX_38  (GUI_ID_USER + 0x56)
#define ID_CHECKBOX_39  (GUI_ID_USER + 0x57)
#define ID_CHECKBOX_40  (GUI_ID_USER + 0x58)

#define   GUI_KEY_NextPage       42

static void _cbinput(WM_MESSAGE* pMsg);
void MainTask(void);
void textcolorch(u8 j);
#endif