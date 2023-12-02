// hd7279
// https://max.book118.com/html/2019/0811/5011102311002113.shtm
#include <hd7279a.h>
#include <common.h>
#include <util.h>

unsigned char LED[8] = {0xa9,0xf1,0x01,0x00,0x44,0x00,0x00,0x00};



void init_hd7279(void)
{
	sendByte_hd(HD7279_RESET);
}

// tc89c52 to hd7279a
void sendByte_hd(unsigned char byte)
{
    unsigned char i;
    
    CS = 0;   
    for(i = 0; i < 8; ++i)
    {

        DAT = byte & 0x80;
        byte = byte << 1; 
        
        CLK = 1;
        short_delay();
        CLK = 0;
    }
}

// hd7279a to tc89c52
unsigned char receiveByte_hd(void)
{
	unsigned char i;
    unsigned char byte;

    sendByte_hd(HD7279_READKEY);
    
	DAT = 1;
	short_delay();
	for(i=0;i<8;++i){	
        CLK = 1;
        
		byte = byte << 1;
		if(DAT) byte = byte|0x01;
		    
        short_delay();
		CLK = 0;
	}
	DAT = 0;
	return(byte);
}

void show(void)
{
    unsigned char i;
    for(i=0;i<8;++i)
    {
        sendByte_hd(LEDZERO + i);
        sendByte_hd(LED[i]);
    }
}
