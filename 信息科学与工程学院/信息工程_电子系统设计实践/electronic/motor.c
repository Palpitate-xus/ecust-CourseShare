#include <REG52.h>
#include <motor.h>

unsigned char tick;
int Speed;
extern unsigned char motorMode;

extern unsigned char key,lastKey;

unsigned char tempMax;
unsigned char tempMin;

extern const unsigned char Number[10];
extern unsigned char LED[8];

void motorTest(unsigned char sped)
{
    EA = 1;
    
    Speed = sped;
    
    LED[0] = LED_NULL;
    LED[1] = Number[Speed / 100];
    LED[2] = Number[(Speed / 10) % 10];
    LED[3] = Number[Speed %10];
    LED[4] = LED_NULL;
    LED[5] = LED_r;
    LED[6] = Number[(motorMode + 1) / 10];
    LED[7] = Number[(motorMode + 1) % 10];

}

void motorControl(float temp)
{
    EA = 1;
    if(temp >= (float)tempMax)
    {
        Speed = 100;
    }
    else if(temp <= (float)tempMin)
    {
        Speed = 0;
    }
    else 
    {
        Speed = 50 * ((temp - tempMin) / (tempMax - tempMin)) + 50;
    }
    LED[4] = LED_NULL;
    LED[5] = Number[Speed / 100];
    LED[6] = Number[(Speed % 100) / 10];
    LED[7] = Number[Speed % 10];
}

void init_motor(void)
{
    TMOD |= 0x01;
    TH0 = 0xfe;
    TL0 = 0x00;
    
    TR0 = 1;
    ET0 = 1;
    EA = 0;
    
    motor = 0;
    motorMode = 0;
    
    tempMin = readByte_ee(10);
    tempMax = readByte_ee(11);
    Speed = 50;
}

int setSpeed(float speedDelta)
{
    Speed = Speed + speedDelta;
    
    if(Speed > 100) Speed = 100;
    else if(Speed < 0) Speed = 0;
    return Speed;
}



void pwmMotor(void) interrupt 1
{
    TH0 = 0xfe;
	TL0 = 0x00;
	tick++;	
	if(tick > 100)	
	{				
		tick = 0;
	}

	if(100 - Speed < tick)
	{
		motor = 1;	
	}
	else
	{
		motor = 0;	
	}

}