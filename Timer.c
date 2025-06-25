#include "Timer.h"

void Timer0_Init(void)		//1毫秒@12.000MHz
{
	// AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0xC0;				//设置定时初始值
	TH0 = 0xE0;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时

	ET0 = 1;
	EA = 1;//开总中断
}

void Timer0_Reload(void)	//定时器0重装载函数
{
	TL0 = 0xC0;				//设置定时初始值
	TH0 = 0xE0;				//设置定时初始值
}


