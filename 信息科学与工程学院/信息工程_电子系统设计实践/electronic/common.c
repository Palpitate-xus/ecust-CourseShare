#include<common.h>


void short_delay(void) 
{
	unsigned char i;
    for(i = 0x0f;i>0;--i);
}

void delay(unsigned int _t)
{
    while(--_t);

}