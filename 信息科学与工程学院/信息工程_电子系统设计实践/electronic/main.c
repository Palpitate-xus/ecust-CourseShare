#include <REG52.H>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <intrins.h>

#include <hd7279a.h>
#include <ds18b20.h>
#include <motor.h>
#include <para.h>
#include <pid.h>
#include <util.h>
#include <common.h>

#define MAIN_MENU_NUM 5 // change it if add or reduce menu nums

unsigned char MenuID = 0x00; // up to 1 bit means is enter menu,next bit means menu layer,last 3bits means main menu ,mid 3bits means submenu of main menu
unsigned char motorMode;
unsigned char paraMode=0;
extern char pidMenuMode;

unsigned char key=0xff,lastKey=0xff;
float temp_now=0.;
unsigned char sped=50;
const unsigned char Number[10] = {LED_0,LED_1,LED_2,LED_3,LED_4,LED_5,LED_6,LED_7,LED_8,LED_9};

unsigned char tP[8]     =   {LED_t, LED_P,  LED_LINE,   LED_NULL,   LED_1 + LED_DOT,  LED_NULL,   LED_NULL,   LED_NULL};
unsigned char run[8]    =   {LED_r, LED_u,  LED_n,      LED_LINE,   LED_2 + LED_DOT,  LED_NULL,   LED_NULL,   LED_NULL};
unsigned char Con[8]    =   {LED_C, LED_o,  LED_n,      LED_LINE,   LED_3 + LED_DOT,  LED_NULL,   LED_NULL,   LED_NULL};
unsigned char PA[8]     =   {LED_P, LED_A,  LED_LINE,   LED_NULL,   LED_4 + LED_DOT,  LED_NULL,   LED_NULL,   LED_NULL};
unsigned char PID[8]    =   {LED_P, LED_1,  LED_d,      LED_LINE,   LED_5 + LED_DOT,  LED_NULL,   LED_NULL,   LED_NULL};
unsigned char my[8]     =   {LED_n, LED_u,  LED_n,      LED_LINE,   LED_6 + LED_DOT,  LED_NULL,   LED_NULL,   LED_NULL};

unsigned char score=0;

void game(void)
{
    static unsigned char i=0;
    unsigned char j;
    for(j=0; j<8; ++j)
    {
        LED[j] = LED_NULL;
    }
    LED[i] = LED_8;
    delay(8000);
    i = (i + 1) % 8;
    switch(key)
    {
        case BUTTON_ENTER:
            if(i == 0)
            {
                score++;
                P2 = 0x00;
                delay(100000);
                P2 = 0xff;
            }
            
    }
}



void menu(void)
{   
    unsigned char i=0;
    switch(MenuID)
    {
        case MENU_MAIN_TD:
            for(i=0;i<8;++i) LED[i] = tP[i];
            return;
        case MENU_MAIN_MT:
            for(i=0;i<8;++i) LED[i] = run[i];
            return;
        case MENU_MAIN_MS:
            for(i=0;i<8;++i) LED[i] = Con[i];
            return;
        case MENU_MAIN_PS:
            for(i=0;i<8;++i) LED[i] = PA[i];
            return;
        case MUNU_MAIN_PID:
            for(i=0;i<8;++i) LED[i] = PID[i];
            
            return;      
        case MENU_TEMP_DETE:
            showTemperature();
            LED[4] = LED_t;
            LED[5] = LED_P;
            LED[6] = LED_o;
            LED[7] = LED_C;
            return;
        case MENU_MOTOR_TEST:
            motorTest(sped);
            return;
        case MENU_MOTOR_SPEED:
            temp_now = showTemperature();
            motorControl(temp_now);
            return;
        case MENU_PARA_SET:
            paraMenu();
            return;
        case MUNU_PID:
            temp_pid();
            return;
     
        case MENU_PARA_MOTOR_TEST:
            para_motorTest();
            return;
        case MENU_PARA_MOTOT_SPEED:
            //temp_now = showTemperature();
            para_tempModift();
            return;
    }
}

void switchMenu()
{
    if(key == 0xff)
    {
        return;
    }
    else
    {

        if(lastKey == 0xff)
        {                     
            if(0 == MenuID >> 6)
            {
                switch(key)
                {
                    case BUTTON_DOWN:
                        MenuID = (MenuID + (MAIN_MENU_NUM - 1)) % MAIN_MENU_NUM; // may error
                        return;
                    case BUTTON_UP:
                        MenuID = (MenuID + 1) % MAIN_MENU_NUM;
                        return;
                    case BUTTON_ENTER:
                        MenuID = MenuID | 0x80;
                        if(MenuID == MUNU_PID)
                            pidMenuMode = 0;
                        return;
                }
            }
            else if(2 == MenuID >> 6)
            {
                if(MenuID == MUNU_PID)
                    return;
                switch(key)
                {
                    case BUTTON_LEFT:
                        MenuID = MenuID & 0x7f;
                        EA = 0;
                        motor = 0;
                        return;
                    case BUTTON_DOWN:
                        if(MenuID == MENU_MOTOR_TEST)
                        {
                            motorMode = (motorMode + 9) % 10;
                            sped = readByte_ee(motorMode);
                        }
                        else if(MenuID == MENU_PARA_SET)
                            paraMode = (paraMode + 1) % 2;
                        break;
                    case BUTTON_UP:
                        if(MenuID == MENU_MOTOR_TEST)
                        {
                            motorMode = (motorMode + 1) % 10;
                            sped = readByte_ee(motorMode);
                        }
                        else if(MenuID == MENU_PARA_SET)
                            paraMode =(paraMode + 1) % 2;
                        break;
                    case BUTTON_ENTER:
                        if(MenuID == MENU_PARA_SET)
                            MenuID = MenuID | 0x40 + (paraMode << 3);
                        break;
                }
            }            
        }
    }
}


void main (void) 
{   
    init_hd7279(); 
    init_ds18b20();
    init_motor();
    init_ee24c16_default();
    
	while(1)
	{  
        
        key = receiveByte_hd();

        switchMenu();
        menu();
        show();
        
        lastKey = key;
	}
}

