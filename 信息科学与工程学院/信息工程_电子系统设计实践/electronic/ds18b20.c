#include <ds18b20.h>
#include <hd7279a.h>
#include <common.h>
#include <util.h>
#include <REG52.h>
// https://blog.csdn.net/as480133937/article/details/112604303
extern const unsigned char Number[10];

extern float temp_now;
 
void init_ds18b20(void)
{
	reset_ds();
	sendByte_ds(DS18B20_IGNOREROM);
	sendByte_ds(DS18B20_TRANS);
    reset_ds();
}
 
void reset_ds(void){
	unsigned char i;
	DQ = 0;
	for(i=240;i>0;i--);
	DQ = 1;
	for(i=240;i>0;i--);
}
 
void sendByte_ds(unsigned char byte)
{
	unsigned char i,j;
	for(i=8;i>0;i--)
    {
		DQ = 0;
		for(j=2;j>0;j--);
		DQ = byte & 0x01;
		for(j=30;j>0;j--);
		DQ = 1;
		byte >>= 1;
	}
}
 
unsigned char receiveByte_ds(void)
{
	unsigned char i,j,s;
	for(i=8;i>0;i--)
    {
		s>>=1;
		DQ = 0;
		for(j=2;j>0;j--);
		DQ = 1;
		for(j=4;j>0;j--);
		if(DQ==1) s|=0x80;
		for(j=30;j>0;j--);
		DQ = 1;
	}
	return s;
}
 
float showTemperature(void)
{
	unsigned char temp_data;
	unsigned short TempDec;
	unsigned char lowByte,highByte;
	unsigned char temp[4];
	
    float T;
	reset_ds();
	sendByte_ds(DS18B20_IGNOREROM);
	sendByte_ds(DS18B20_TRANS);
	reset_ds();
	sendByte_ds(DS18B20_IGNOREROM);
	sendByte_ds(DS18B20_READ);
	
	lowByte=receiveByte_ds();
    highByte = receiveByte_ds();
	
	reset_ds();
	
	temp_data = highByte;
	temp_data &= 0xf0;
	if(temp_data == 0xf0)
    {
		if(lowByte == 0)
        {
			lowByte =~ lowByte + 1;
			highByte =~ highByte + 1;
		}
		else
        {
			lowByte =~ lowByte + 1;
			highByte =~ highByte;
		}
	}

	temp_data = highByte<<4 | lowByte>>4;
	temp[0]=(temp_data % 100) / 10;
	temp[1]=(temp_data % 100) % 10;
	lowByte &= 0x0f;
	TempDec = lowByte * 625;
	temp[2] = TempDec / 1000;
	temp[3] = (TempDec % 1000) / 100;
    
    T = 10 * temp[0] + temp[1] + 0.1 * temp[2] + 0.01 * temp[3];
    
    if(T == 85.) return 0.;
    if(temp_now==0)
    {
		temp_now = T;
	}
    if((T-temp_now > 0. ? T-temp_now : temp_now-T ) < 1.)  
	{
		LED[0] = Number[temp[0]];
		LED[1] = Number[temp[1]] + LED_DOT;
		LED[2] = Number[temp[2]];
		LED[3] = Number[temp[3]];	
        temp_now = T;
	}
    return temp_now;
}