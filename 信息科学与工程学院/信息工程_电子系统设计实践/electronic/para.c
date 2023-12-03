#include <para.h>

unsigned char para_motorTestMode = 0;
unsigned char para_tempModify = 0;
unsigned char keyTime;
unsigned char isChanging=0;
void paraMenu(void)
{ 
    if(paraMode == 0)
    {
        LED[0] = LED_NULL;
        LED[1] = LED_r;
        LED[2] = LED_u;
        LED[3] = LED_n;
    }
    else if(paraMode == 1)
    {
        LED[0] = LED_NULL;
        LED[1] = LED_C;
        LED[2] = LED_o;
        LED[3] = LED_n;
    }
    
    LED[4] = LED_P;
    LED[5] = LED_A;
    LED[6] = LED_LINE;
    LED[7] = LED_NULL;
}

void para_motorTest(void)
{
    static unsigned char dutyRation=0;
    static unsigned char steps;
    
    if(!isChanging)     dutyRation = readByte_ee(para_motorTestMode);
    
    if(key == 0xff)
    {
        keyTime = 0;
        steps = 1;
        return;
    }
    else
    {
        keyTime++;
        
        if(keyTime == 1)
        {
            if(!isChanging)
            {
                switch(key)
                {
                    case BUTTON_DOWN:
                        para_motorTestMode = (para_motorTestMode + (10 - steps)) % 10;             
                        break;
                    case BUTTON_UP:
                        para_motorTestMode = (para_motorTestMode + steps) % 10;
                        break;
                    case BUTTON_ENTER:
                        isChanging = 1;
                        break;
                    case BUTTON_LEFT:
                        MenuID = MENU_PARA_SET;
                        break;
                }
            }
            else
            {
                switch(key)
                {
                    case BUTTON_DOWN:
                        dutyRation = (dutyRation + (100 - steps)) % 101;             
                        break;
                    case BUTTON_UP:
                        dutyRation = (dutyRation + steps) % 101;
                        break;
                    case BUTTON_ENTER:
                        writeByte_ee(dutyRation,para_motorTestMode);
                        isChanging = 0;
                        break;
                    case BUTTON_LEFT:
                        isChanging = 0;
                        break;
                }
            }
        }
        else if(keyTime > 30)
        {
            keyTime = 0;
            steps = 1.5 * steps + 1;
            steps = steps > 10 ? 10 : steps;
        }
    }
       
    {
        LED[0] = LED_NULL;
        LED[1] = Number[dutyRation / 100];
        LED[2] = Number[(dutyRation % 100) / 10];
        LED[3] = Number[dutyRation % 10];
        if(!isChanging) LED[4] = LED_P;
        else LED[4] = LED_A;
        LED[5] = LED_LINE;
        LED[6] = Number[(para_motorTestMode + 1) / 10];
        LED[7] = Number[(para_motorTestMode + 1) % 10];
    } 
}

void para_tempModift(void)
{
    static unsigned char temp=0;
    static unsigned char steps;
    
    if(!isChanging)     temp = readByte_ee(10 + para_tempModify);
    
    if(key == 0xff)
    {
        keyTime = 0;
        steps = 1;
        return;
    }
    else
    {
        keyTime++;
        
        if(keyTime == 1)
        {
            if(!isChanging)
            {
                switch(key)
                {
                    case BUTTON_DOWN:
                        para_tempModify = (para_tempModify + 1) % 2;             
                        break;
                    case BUTTON_UP:
                        para_tempModify = (para_tempModify + 1) % 2;
                        break;
                    case BUTTON_ENTER:
                        isChanging = 1;
                        break;
                    case BUTTON_LEFT:
                        MenuID = MENU_PARA_SET;
                        break;
                }
            }
            else
            {
                switch(key)
                {
                    case BUTTON_DOWN:
                        temp = (temp - steps) > 10 ? (temp - steps) : 10;
                        break;
                    case BUTTON_UP:
                        temp = (temp + steps) < 70 ? (temp + steps) : 70;
                        break;
                    case BUTTON_ENTER:
                        writeByte_ee(temp,10 + para_tempModify);
                        tempMin = readByte_ee(10);
                        tempMax = readByte_ee(11);
                        isChanging = 0;
                        break;
                    case BUTTON_LEFT:
                        isChanging = 0;
                        break;
                }
            }
        }
        else if(keyTime > 30)
        {
            keyTime = 0;
            steps = 1.5 * steps + 1;
            steps = steps > 5 ? 5 : steps;
        }
    }
    
    {
        LED[0] = Number[(temp / 10) % 10];
        LED[1] = Number[temp % 10];
        LED[2] = LED_o;
        LED[3] = LED_C;
        LED[4] = LED_t;
        LED[5] = LED_LINE;
        LED[6] = LED_LINE;
        if(para_tempModify) LED[7] = LED_H;
        else LED[7] = LED_L;
    }
    
}