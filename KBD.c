#include "KBD.h"

/*
	键值如下(0x)
	88	84	82	81
	48	44	42	41
	28	24	22	21
	18	14	12	11
*/
u8 KBD_IO(void)
{
	u8 io = 0xff;
	
	//列扫描
	P14 = 1; P15 = 1; P16 = 1; P17 = 1;
    P10 = 0; P11 = 0; P12 = 0; P13 = 0;
    if(P17 == 0) io = 0x70;
    if(P16 == 0) io = 0xb0;
    if(P15 == 0) io = 0xd0;
    if(P14 == 0) io = 0xe0;
    
	//行扫描
    P10 = 1; P11 = 1; P12 = 1; P13 = 1;
    P14 = 0; P15 = 0; P16 = 0; P17 = 0;
    if(P13 == 0) io |= 0x07;
    if(P12 == 0) io |= 0x0b;
    if(P11 == 0) io |= 0x0d;
    if(P10 == 0) io |= 0x0e;
	
	return io;
}

//触发（按下）和长按
u8 pres = 0,cont = 0;
void KBD_Read(void)
{
	u8 state = KBD_IO() ^ 0xff;
	pres = state & (state ^ cont);
	cont = state;
}
