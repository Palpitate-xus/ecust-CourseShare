#ifndef EE24C16_H
#define EE24C16_H

#include <REG52.h>

sbit SCL = P1^1;
sbit SDA = P1^0;
 
void init_ee24c16(void);
 
unsigned char readByte_ee(unsigned char);
void writeByte_ee(unsigned char,unsigned char);

unsigned char readByte_I2C(void);
void writeByte_I2C(unsigned char);

void I2C_noack(void);
void I2C_ack(void);
void I2C_stop(void);
void I2C_start(void);

void init_ee24c16_default(void);

#endif



