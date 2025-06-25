#include "PW.h"
//密码操作相关函数

void mPW_Shift(bit lr)//密码左移右移
{
	u8 i;
	if(lr == 0){//左移
		for(i = pw_index;i < 8;i++){
			pw_input[i-1] = pw_input[i];
		}
		pw_input[7] = 0x40;
	}
	else{//右移
		if(pw_index == 0){//数组已满
			for(i = 7;i > 0;i--){
				pw_input[i] = pw_input[i-1];
			}
			pw_input[0] = 0x40;
		}
		else{//数组未满
			for(i = 6;i >= pw_index;i--){
				pw_input[i+1] = pw_input[i];
			}
			pw_input[i+1] = 0x40;
		}
	}
}

void mPW_Ins(u8 b)//输入一位密码
{
	if(pw_input[0] == 0x40){
		mPW_Shift(0);
		pw_index--;
		pw_input[7] = b;
	}
}

void mPW_Del(void)//删除一位密码
{
	if(pw_input[7] != 0x40){
		mPW_Shift(1);
		pw_index++;
	}
}

void mPW_Clear(void){//清除输入的密码
	u8 i;
	for(i = 0;i < 8;i++){
		pw_input[i] = 0x40;
	}
	pw_index = 8;
}

bit mPW_IsEmpty(void)//判断输入密码是否有空格
{
    u8 i;
    for (i = 0; i < 8; i++) {
        if (pw_input[i] == 0x40) {
            return 1;
        }
    }
    return 0;
}

bit mPW_IsCorrect(void) // 密码判断函数
{
    u8 i, login;

    for (login = 0; login < USER_MAX; login++) {
        for (i = 0; i < 8; i++) {
            if (pw_input[i] != password[login][i]) {
                break; // 如果当前密码不匹配，跳出内层循环
            }
        }
        if (i == 8) { // 如果内层循环正常结束，说明密码匹配
            user = login;//登录用户ID确认
            return 1;
        }
    }
    return 0; // 如果所有密码都不匹配，返回0
}


//超级管理员密码判断函数
bit mPW_IsAdmin(void)
{
	u8 i;
	for(i = 0;i < 8;i++){
		if(pw_input[i] != admin[i])
			return 0;
	}
	return 1;
}

void mPW_AdminSet(void)//设置管理员密码
{
	u8 i;
	for(i = 0;i < 8;i++){
		admin[i] = pw_input[i];
	}
}

void mPW_Set(void)//设置密码
{
	u8 i;
	for(i = 0;i < 8;i++){
		password[user][i] = pw_input[i];
	}
}

void mPW_Read(void)//从E2PROM读取密码到程序
{
	u8 i;
	for(i = 0;i < USER_MAX;i++)
		EEPROM_Read(password[i],i*8,8);
	EEPROM_Read(admin,i*8,8);
}

void mPW_Observe(void)//管理员可读取旧密码
{
	u8 i;
	for(i = 0;i < 8;i++){
		pw_input[i] = password[user][i];
	}
}

void mPW_Main(void)//扫描键盘密码
{
    if ((pres == 0x18) || (pres == 0x14))
        mPW_Ins(0);
    if (pres == 0x28)
        mPW_Ins(1);
    if (pres == 0x24)
        mPW_Ins(2);
    if (pres == 0x22)
        mPW_Ins(3);
    if (pres == 0x48)
        mPW_Ins(4);
    if (pres == 0x44)
        mPW_Ins(5);
    if (pres == 0x42)
        mPW_Ins(6);
    if (pres == 0x88)
        mPW_Ins(7);
    if (pres == 0x84)
        mPW_Ins(8);
    if (pres == 0x82)
        mPW_Ins(9);
}
