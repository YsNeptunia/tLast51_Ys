#ifndef __KBD_H_
#define __KBD_H_

#include "System.h"

u8 KBD_IO(void);
extern u8 pres,cont;//按键状态: 触发，长按
void KBD_Read(void);

#endif