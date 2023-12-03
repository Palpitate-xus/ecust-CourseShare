#include <REG52.H>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <intrins.h>
#include <hd7279a.h>
#include <common.h>
#include <ee24c16.h>
#include <ds18b20.h>
#include <util.h>
 
void init_ee24c16(void)
{
	SDA=1;
	SCL=1;
}
 
 
void I2C_start(void)
{
	
	SDA=1;
	delay(5);
	SCL=1;
	delay(5);
	SDA=0;
	delay(5);
}
 
void I2C_stop(void)
{
	SDA=0;
	delay(5);
	SCL=1;
	delay(5);
	SDA=1;
	delay(5);
}
 
void I2C_ack(void)
{
	unsigned char i;
	SCL=1;
	delay(5);
	while( (SDA==1) && (i<200) )  i++;
	SCL=0;
	delay(5);
}
 
void I2C_noack()
{
	SDA = 1;
	delay(5);
	SCL = 1;
	delay(5);
	SCL = 0;
	delay(5);
}

void writeByte_I2C(unsigned char input)
{
	unsigned char i;
	SCL = 0;
	for(i=0;i<8;i++){
		if( input & 0x80 )  
            SDA = 1;
		else 
            SDA = 0;
        
		input = input<<1;
		delay(5);
		SCL = 1;
		delay(5);
		SCL = 0;
		delay(5);
	}
	SDA = 1;
	delay(5);
}
 
unsigned char readByte_I2C(void)
{
	unsigned char i,rbyte;
	SCL = 0;
	delay(5);
	SDA = 1;
	delay(5);
	for(i = 0;i<8;++i){
		SCL = 1;
		delay(5);
		rbyte = rbyte<<1;
		if(SDA) 
            rbyte++;
		SCL = 0;
		delay(5);
	}
	return rbyte;
}
 
void writeByte_ee(unsigned char dat,unsigned char addr)
{
	init_ee24c16();
	I2C_start();
	writeByte_I2C(EE24C16_WRITE_ADDRESS);
	I2C_ack();
	writeByte_I2C(addr);
	I2C_ack();
	writeByte_I2C(dat);
	I2C_ack();
	I2C_stop();
}
 
unsigned char readByte_ee(unsigned char addr)
{
	unsigned char output;
	init_ee24c16();
	I2C_start();
	writeByte_I2C(EE24C16_WRITE_ADDRESS);
	I2C_ack();
	writeByte_I2C(addr);
	I2C_ack();
	I2C_start();
	writeByte_I2C(EE24C16_READ_ADDRESS);
	I2C_ack();
	output = readByte_I2C();
	I2C_noack();
	I2C_stop();
	return output;
}
 
void init_ee24c16_default(void){
	//只调用一次
	delay(150);
	writeByte_ee(10,0);
	delay(150);
	writeByte_ee(20,1);
	delay(150);
	writeByte_ee(30,2);
	delay(150);
	writeByte_ee(40,3);
	delay(150);
	writeByte_ee(50,4);
	delay(150);
	writeByte_ee(60,5);
	delay(150);
	writeByte_ee(70,6);
	delay(150);
	writeByte_ee(80,7);
	delay(150);
	writeByte_ee(90,8);
	delay(150);
	writeByte_ee(100,9);
	delay(150);
	writeByte_ee(28,10);//t_low
	delay(150);
	writeByte_ee(32,11);//t_high
	delay(150);
    
    writeByte_ee(0x0f,12); //low
    delay(150);
    writeByte_ee(0x27,13); //high
}