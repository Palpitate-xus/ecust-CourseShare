#ifndef HD7279_H
#define HD7279_H

#include <REG52.h>

sbit CS = P1^4; // from PCB
sbit CLK = P1^5;
sbit DAT = P1^7;
sbit KEY = P1^6;

extern unsigned char LED[8];

void init_hd7279(void);
void sendByte_hd(unsigned char byte);
unsigned char receiveByte_hd(void);
void show(void);

#endif

