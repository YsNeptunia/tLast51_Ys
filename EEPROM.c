#include "EEPROM.h"

static void I2C_Delay(unsigned char n)
{
    do{_nop_();}
    while(n--);      	
}

void EEPROM_Write(u8* dat,u8 addr,u8 num)//形参：将要写入的字符串；写入的地址（8倍数）；写入的数量
{
	ET0 = 0;//写数据较长，且IO口与数码管冲突（高频较影响），故先关中断

	I2CStart();
	I2CSendByte(0xa0);//选择AT24C02芯片，写模式
	I2CWaitAck();
	
	I2CSendByte(addr);//选择写入的地址
	I2CWaitAck();
	
	while(num--){
		I2CSendByte(*dat++);//写入数据
		I2CWaitAck();
		I2C_Delay(200);
	}
	
	I2CStop();
	ET0 = 1;
}

void EEPROM_Read(u8* dat,u8 addr,u8 num)//形参：将要读出的字符串；读的地址（8倍数）；读的数量
{
	ET0 = 0;//写数据较长，且IO口与数码管冲突（高频较影响），故先关中断

	I2CStart();
	I2CSendByte(0xa0);//选择AT24C02芯片，写模式
	I2CWaitAck();
	
	I2CSendByte(addr);//选择写入的地址
	I2CWaitAck();
	
	I2CStart();
	I2CSendByte(0xa1);//选择AT24C02芯片，读模式
	I2CWaitAck();
	
	while(num--){
		*dat++ = I2CReceiveByte();
		if(num)	I2CSendAck(0);//继续读，发送应答
		else	I2CSendAck(1);//不应答
	}
	
	I2CStop();
	ET0 = 1;//写数据较长，且IO口与数码管冲突（高频较影响），故先关中断
}
