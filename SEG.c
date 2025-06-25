#include "SEG.h"

u8 seg_buf[8];//数码管缓存
code unsigned char tab[] =
{
0x3f, //0
0x06, //1
0x5b, //2
0x4f, //3
0x66, //4
0x6d, //5
0x7d, //6
0x07, //7
0x7f, //8
0x6f, //9
0x77, //A
0x7c, //b
0x39, //C
0x5e, //d
0x79, //E
0x71  //F
};

void SEG_Display()//数码管刷新函数
{
	static u8 i = 7;
	
	P0 = 0X00;//消隐
	P2 = (P2 & 0xe3) | ((7-i) << 2);//位选
	P0 = seg_buf[i];//段选
	i = (i - 1) & 7;
}

void SEG_Clear(void){//数码管清屏
	u8 i;
	for(i = 0;i < 8;i++){
		seg_buf[i] = 0x00;
	}
}
