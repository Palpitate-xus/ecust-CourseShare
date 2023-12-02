#ifndef DS18B20_H
#define DS18B20_H

#include <REG52.h>
sbit DQ = P1^3;

 
void init_ds18b20(void);
void reset_ds(void);
void sendByte_ds(unsigned char);
unsigned char receiveByte_ds(void);
float showTemperature(void);


#endif