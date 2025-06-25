#ifndef __PW_H_
#define __PW_H_

#include "System.h"

void mPW_Shift(bit lr);//密码左移右移
void mPW_Ins(u8 b);//输入一位密码
void mPW_Del(void);//删除一位密码
void mPW_Clear(void);//清除输入的密码
bit mPW_IsEmpty(void);//判断密码是否空
bit mPW_IsCorrect(void); // 密码判断函数
bit mPW_IsAdmin(void);//超级管理员密码判断函数
void mPW_AdminSet(void);
void mPW_Set(void);//设置密码
void mPW_Read(void);
void mPW_Observe(void);
void mPW_Main(void);

#endif