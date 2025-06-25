#include "Timer.h"

void Timer0_Init(void)		//1����@12.000MHz
{
	// AUXR &= 0x7F;			//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TL0 = 0xC0;				//���ö�ʱ��ʼֵ
	TH0 = 0xE0;				//���ö�ʱ��ʼֵ
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ

	ET0 = 1;
	EA = 1;//�����ж�
}

void Timer0_Reload(void)	//��ʱ��0��װ�غ���
{
	TL0 = 0xC0;				//���ö�ʱ��ʼֵ
	TH0 = 0xE0;				//���ö�ʱ��ʼֵ
}


