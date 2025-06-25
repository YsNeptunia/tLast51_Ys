#include "EEPROM.h"

static void I2C_Delay(unsigned char n)
{
    do{_nop_();}
    while(n--);      	
}

void EEPROM_Write(u8* dat,u8 addr,u8 num)//�βΣ���Ҫд����ַ�����д��ĵ�ַ��8��������д�������
{
	ET0 = 0;//д���ݽϳ�����IO��������ܳ�ͻ����Ƶ��Ӱ�죩�����ȹ��ж�

	I2CStart();
	I2CSendByte(0xa0);//ѡ��AT24C02оƬ��дģʽ
	I2CWaitAck();
	
	I2CSendByte(addr);//ѡ��д��ĵ�ַ
	I2CWaitAck();
	
	while(num--){
		I2CSendByte(*dat++);//д������
		I2CWaitAck();
		I2C_Delay(200);
	}
	
	I2CStop();
	ET0 = 1;
}

void EEPROM_Read(u8* dat,u8 addr,u8 num)//�βΣ���Ҫ�������ַ��������ĵ�ַ��8����������������
{
	ET0 = 0;//д���ݽϳ�����IO��������ܳ�ͻ����Ƶ��Ӱ�죩�����ȹ��ж�

	I2CStart();
	I2CSendByte(0xa0);//ѡ��AT24C02оƬ��дģʽ
	I2CWaitAck();
	
	I2CSendByte(addr);//ѡ��д��ĵ�ַ
	I2CWaitAck();
	
	I2CStart();
	I2CSendByte(0xa1);//ѡ��AT24C02оƬ����ģʽ
	I2CWaitAck();
	
	while(num--){
		*dat++ = I2CReceiveByte();
		if(num)	I2CSendAck(0);//������������Ӧ��
		else	I2CSendAck(1);//��Ӧ��
	}
	
	I2CStop();
	ET0 = 1;//д���ݽϳ�����IO��������ܳ�ͻ����Ƶ��Ӱ�죩�����ȹ��ж�
}
