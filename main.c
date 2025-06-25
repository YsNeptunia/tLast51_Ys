#include "System.h"

u8 password[3][8] = {{2,2,4,4,6,6,8,8},{1,2,3,4,5,6,7,8},{0,0,0,0,0,0,0,0}};//系统已储存的密码，上电会替换成E2PROM的
u8 admin[8] = {8,8,8,8,8,8,8,8};//管理员万能密码
u8 pw_input[8] = {0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40};//用户输入的密码，用于对照，登录无数据默认为0x40，修改无数据默认为0x80
u8 pw_index = 8;//输入密码下标，指向8时输入密码为空
char user = -1;//登录的用户ID(012。-1表示未登录,3表示管理员)
u8 error = 0;//错误总次数，超过3读秒

u8 mode = 0;//模式切换标志位，模式0输入密码，模式1密码正确可修改自己的密码，模式2管理员模式可修改全员密码
// bit flash;//0.1s一闪
bit errflag;//错误标志位
bit adflag = 1;//管理员子模式（0时选择ID，1时修改其ID）
bit beepflag;//蜂鸣器单响标志位

u8 segcnt = 0;//100
u8 kbdcnt = 0;//10
// u16 flashcnt = 0;//500
u8 keycnt;
u16 errcnt = 0;//倒计时重新输入5s
u8 beepcnt;//让蜂鸣器响一声0.075s
bit stepflag;//步进电机每步延时（设为1）

void KBD_Process()
{
	if(kbdcnt)	return;
	kbdcnt = 1;

	KBD_Read();

	if(error >= 3)//超过三次，停止显示，禁止输入
		return;

	switch(mode){
		case 0:{//输入密码模式
			//输入数字
            mPW_Main();

            if(pres == 0x11){//确认密码
				if(mPW_IsEmpty())	return;
				if(mPW_IsAdmin()){
					mPW_Clear();
					Open_Door();
					//密码正确，切换到模式2
					error = 0;
					mode = 2;
					user = 0;
					SEG_Clear();
					seg_buf[0] = tab[10]|0x80;//"A."表示当前在Admin模式
				}
				else if(mPW_IsCorrect()){
					mPW_Clear();
					Open_Door();
					//密码正确，切换到模式1
					error = 0;
					if(user != -1){
						mode = 1;
						SEG_Clear();
						seg_buf[0] = tab[12]|0x80;//"C."表示当前在Client模式
					}
				}
				else{
					mPW_Clear();
					//密码错误，清空输入
					beepflag = 1;
					error++;
				}return;
			}

			if(pres == 0x21)	mPW_Del();//删除密码
			
			if(cont == 0x41){//长按清空密码
				keycnt++;
				if(keycnt >= 100){
					mPW_Clear();
				}
			}

			if(keycnt && cont == 0x00){
				keycnt = 0;
			}
		};break;
		case 1:{//修改密码模式
			//输入数字
			mPW_Main();

			if(pres == 0x21)	mPW_Del();//删除密码
			
			if(cont == 0x41){//长按清空密码
				keycnt++;
				if(keycnt >= 100){
					mPW_Clear();
				}
			}

			if(keycnt && cont == 0x00){
				keycnt = 0;
			}
			
			if(pres == 0x11){//确认修改密码
				if(mPW_IsEmpty())	return;
				mPW_Set();
				EEPROM_Write(pw_input,user*8,8);//写入修改后密码
				return;
			}
		};break;
		case 2:{//管理员模式
		    if(adflag){//界面1选择ID
				if(pres == 0x28)
					if(user != USER_MAX)
						user += 1;//向上翻页
					else
						user = 0;
				if(pres == 0x18)
					if(user != 0)
						user -= 1;//向下翻页
					else
						user = USER_MAX;//置为管理员下标
			}
			else{
				mPW_Main();

				if(pres == 0x21)	mPW_Del();//删除密码
				
				if(cont == 0x14){//长按显示旧密码
						if(user != USER_MAX){
						keycnt++;
						if(keycnt >= 100){
							mPW_Observe();
						}
					}
				}

				if(cont == 0x41){//长按清空密码
					keycnt++;
					if(keycnt >= 100){
						mPW_Clear();
					}
				}

				if(keycnt && cont == 0x00){
					keycnt = 0;
				}

				if(pres == 0x11){//确认修改密码
					if(mPW_IsEmpty())	return;

					if(user == USER_MAX){//USER_MAX为管理员下标
						mPW_AdminSet();
						EEPROM_Write(pw_input,USER_MAX*8,8);
					}
					else{
						mPW_Set();
						EEPROM_Write(password[user],user*8,8);//写入修改后密码
					}
					return;
				}
			}
			if(pres == 0x12){//切换标志位便于多用户管理
				mPW_Clear();
				adflag = ~adflag;
			}
		}
	}

	if(pres == 0x81){//退出登录
		mPW_Clear();
		mode = 0;
		user = -1;
	}

	// if(pres && (pres != saved_key)){//有新按键触发
	// 	EEPROM_Write(&pres,8,1);
	// }
}

void SEG_Process()
{
	u8 i;

	// for (i = 0; i < 8; i++)
	// seg_buf[i] = password[1][i];
	
	if(segcnt)	return;
	segcnt = 1;

	if(error >= 3){//超过三次，停止显示，禁止输入
		for (i = 0; i < 8; i++){
			seg_buf[i] = 0x00;
		}
		return;
	}

	switch(mode)
	{
		case 0:{
			for (i = 0; i < 8; i++)
				seg_buf[i] = (pw_input[i] != 0x40) ? tab[pw_input[i]] : 0x40;//无输入显示"-"
		};break;
		case 1:{
			// seg_buf[0] = (pw_input[0] != 0x40) ? tab[pw_input[0]] : (tab[12]|0x80);//"C."表示当前在Client模式
			if(pw_input[7] == 0x40){
				seg_buf[0] = tab[12]|0x80;//"C."表示当前在Client模式
				seg_buf[1] = tab[user]|0x80;//当前用户ID
			}
			else{
				seg_buf[0] = (pw_input[0] != 0x40) ? tab[pw_input[0]] : 0x80;;//有输入则变为点
				seg_buf[1] = (pw_input[1] != 0x40) ? tab[pw_input[1]] : 0x80;
			}
			for (i = 2; i < 8; i++)
				seg_buf[i] = (pw_input[i] != 0x40) ? tab[pw_input[i]] : 0x80;
		};break;
		case 2:{
			if(adflag){
				seg_buf[0] = tab[10]|0x80;//"A."表示当前在Admin模式
				seg_buf[1] = 0x40;//"-"
				seg_buf[2] = 0x40;
				seg_buf[3] = 0x40;
				seg_buf[4] = 0x40;
				seg_buf[5] = 0x40;
				if (user < USER_MAX){
					seg_buf[6] = tab[12]; //"C"
					seg_buf[7] = tab[user];
				}
				else{
					seg_buf[6] = tab[10];//"A"
					seg_buf[7] = tab[13];//"D"
				}
			}
			else{
				for (i = 0; i < 8; i++)
					seg_buf[i] = (pw_input[i] != 0x40) ? tab[pw_input[i]] : 0x80;//无输入显示"."
			}
		};break;
	}
}

void BEEP_Process(void)
{
	if(~errflag && (error >= 3)){//密码错误锁定长响
		BEEP = 1;
		errflag = 1;
	}
	else if(errflag && (error < 3)){
		BEEP = 0;
		errflag = 0;
	}

	if(beepflag && ~BEEP)//密码正确短响
		BEEP = 1;
	else if(!beepflag && BEEP)
		BEEP = 0;
}

void main()
{
	BEEP = 0;
	mPW_Read();
	Timer0_Init();
	UartInit();
	Stepper_Init();
	
	while(1){
		SEG_Process();
		KBD_Process();
		BEEP_Process();
	}
}

void T0ISR(void)	interrupt 1
{
	Timer0_Reload();
	SEG_Display();
	
	if(++segcnt >= 50)	segcnt = 0;
	if(++kbdcnt >= 10)	kbdcnt = 0;
	// if(++flashcnt >= 500){
	// 	flashcnt = 0;
	// 	flash = ~flash;
	// }

	if(error >= 3){
		if(++errcnt >= 5000){
			errcnt = 0;
			error = 0;
		}
	}
	if(beepflag){
		if(++beepcnt >= 75){
			beepcnt = 0;
			beepflag = 0;
		}
	}
	stepflag = 1;
}

// void Uart_Rounite() interrupt 4 //WIFI数据接收
// {
// 	RI = 0;
// 	receiveData = SBUF;
//	Uart_Send(receiveData);
// }
