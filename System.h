#ifndef __SYSTEM_H_
#define __SYSTEM_H_

#include "System.h"

typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

#define DECtoBCD(dec) (dec/10*16)+(dec%10)
#define BCDtoDEC(bcd) (bcd/16*10)+(bcd%16)

#include <REG52.H>
#include <intrins.h>

sbit    P00         =           P0^0;
sbit    P01         =           P0^1;
sbit    P02         =           P0^2;
sbit    P03         =           P0^3;
sbit    P04         =           P0^4;
sbit    P05         =           P0^5;
sbit    P06         =           P0^6;
sbit    P07         =           P0^7;

sbit    P10         =           P1^0;
sbit    P11         =           P1^1;
sbit    P12         =           P1^2;
sbit    P13         =           P1^3;
sbit    P14         =           P1^4;
sbit    P15         =           P1^5;
sbit    P16         =           P1^6;
sbit    P17         =           P1^7;

sbit    P20         =           P2^0;
sbit    P21         =           P2^1;
sbit    P22         =           P2^2;
sbit    P23         =           P2^3;
sbit    P24         =           P2^4;
sbit    P25         =           P2^5;
sbit    P26         =           P2^6;
sbit    P27         =           P2^7;

sbit    P30         =           P3^0;
sbit    P31         =           P3^1;
sbit    P32         =           P3^2;
sbit    P33         =           P3^3;
sbit    P34         =           P3^4;
sbit    P35         =           P3^5;
sbit    P36         =           P3^6;
sbit    P37         =           P3^7;

#define USER_MAX 3//3个user
extern u8 password[3][8];//系统已储存的密码
extern u8 admin[8];//管理员万能密码
extern u8 pw_input[8];//用户输入的密码，用于对照，无数据默认为0x40
extern u8 pw_index;//输入密码下标，指向8时输入密码为空
extern char user;//登录的用户ID(0或1。-1表示未登录)
extern u8 error;//错误总次数，超过3读秒
#include "PW.h"

extern bit stepflag;//步进电机每步延时（假设为1）

sbit BEEP = P2^5;

#include "Timer.h"
#include "iic.h"
#include "Uart.h"

#include "SEG.h"
#include "KBD.h"
#include "EEPROM.h"
#include "ULN2003D.h"

#endif

