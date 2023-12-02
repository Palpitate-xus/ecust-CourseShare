#include <pid.h>

extern int Speed;
extern float temp_now;
float temp_set;
char pidMenuMode=0;


void modifyPassword(unsigned short password)
{
    unsigned char lowPassword,highPassword;
    unsigned char low,high;
    lowPassword  =  readByte_ee(12);
    highPassword =  readByte_ee(13);
    
    low = password;
    high = password >> 8;
    
    
    if(lowPassword == (unsigned char)password && highPassword == (unsigned char)(password >> 8))
    {
        pidMenuMode = 1;
        temp_set = readByte_ee(10);
    }
    else 
    {
        pidMenuMode = -1;
    }
}

void pidControl(float tempNow, float tempSet)
{
    static float e_1=0.,e_2=0.,e=0.;
    static float kp=4.0,ki=0.07,kd=0.9;
    float A,B,C,speedDelta;
    
    e_2 = e_1;
    e_1 = e;
    e = tempNow - tempSet;
    
    A = kp * (1 + ki + kd);
    B = - kp * (1 + 2 * kd);
    C = kp * kd;
    speedDelta = (A * e + B * e_1 + C * e_2);
    
    if(speedDelta < 0.2)
        speedDelta--;
    if(speedDelta > 0.5)
        speedDelta++;
    
    Speed = Speed + speedDelta;
    
    if(Speed > 100) Speed = 100;
    if(Speed< 0) Speed = 0;
    
    LED[4] = LED_NULL;
    LED[5] = Number[Speed / 100];
    LED[6] = Number[(Speed / 10) % 10];
    LED[7] = Number[Speed % 10];
    delay(10000);
}

void temp_pid()
{
    static unsigned short inputPassword=0;
    static unsigned char keyTime;
    static unsigned char steps;
    
    
    if(key == 0xff)
    {
        keyTime = 0;
        steps = 1;
    }
    else
    {
        keyTime++;
        
        if(keyTime == 1)
        {
            if(pidMenuMode == 0)
            {
                switch(key)
                {
                    case BUTTON_DOWN:
                        inputPassword = (inputPassword + (10000 - steps)) % 10000;             
                        break;
                    case BUTTON_UP:
                        inputPassword = (inputPassword + steps) % 10000;
                        break;
                    case BUTTON_ENTER:
                        if(lastKey != key)  modifyPassword(inputPassword);
                        break;
                    case BUTTON_LEFT:
                        MenuID = MUNU_MAIN_PID;
                        break;
                }
            }
            
            else if(pidMenuMode == -1)
            {
                if(lastKey != key)
                {
                    switch(key)
                    {
                        case BUTTON_ENTER:
                        case BUTTON_LEFT:
                            pidMenuMode = 0;
                            EA = 0;
                            break;
                    }
                }
            }
            
            else if(pidMenuMode == 1)
            {
                switch(key)
                {
                    case BUTTON_LEFT:
                        pidMenuMode = 0;
                        EA = 0;
                        break;
                }
            }
        }
        else if(keyTime > 30)
        {
            keyTime = 0;
            steps = 2. * steps + 1;
            steps = steps > 500 ? 500 : steps;
        }
    }
    
    if(pidMenuMode == 0)
    {
        LED[0] = Number[inputPassword / 1000];
        LED[1] = Number[(inputPassword / 100) % 10];
        LED[2] = Number[(inputPassword / 10) % 10];
        LED[3] = Number[inputPassword % 10];
        LED[4] = LED_P;
        LED[5] = LED_LINE;
        LED[6] = LED_LINE;
        LED[7] = LED_LINE;
    }
    else if(pidMenuMode == -1) 
    {
        LED[0] = LED_8 + LED_DOT;
        LED[1] = LED_8 + LED_DOT;
        LED[2] = LED_8 + LED_DOT;
        LED[3] = LED_8 + LED_DOT;
        LED[4] = LED_E;
        LED[5] = LED_r;
        LED[6] = LED_r + LED_DOT;
        LED[7] = LED_NULL;
    }
    else if(pidMenuMode == 1)
    {
        EA = 1;
        temp_now = showTemperature();
        
        pidControl(temp_now, temp_set);
    }
    
}