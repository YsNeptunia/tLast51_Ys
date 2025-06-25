#include "Uart.h"

void UartInit(void)		//9600bps@11.0592MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFD;		//设定定时初值
	TH1 = 0xFD;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//打开定时器1
	EA = 1;
	ES = 1;
}

// void SendByte(u8 dat)//串口送出一字节数据
// {
// 	SBUF = dat;
// 	while(TI == 0);
// 	TI = 0;
// }

// void Uart_Send(u8* dat)//串口送出字符串
// {
// 	while(*dat != '\0'){
// 		SendByte(*dat++);
// 	}
// }
