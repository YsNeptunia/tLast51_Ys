#ifndef __ONEWIRE_H_
#define __ONEWIRE_H_

#include "System.h"

sbit DQ = P1^4;

void Delay_OneWire(unsigned int t);
void Write_DS18B20(unsigned char dat);
unsigned char Read_DS18B20(void);
bit init_ds18b20(void);
//float Read_Temper(void);

#endif