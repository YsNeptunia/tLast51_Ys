#ifndef __SEG_H_
#define __SEG_H_

#include "System.h"

extern u8 seg_buf[8];
extern code unsigned char tab[];

void SEG_Ctrl(u8 seg_bit, u8 seg_data);
void SEG_Display();
void SEG_Clear(void);

#endif