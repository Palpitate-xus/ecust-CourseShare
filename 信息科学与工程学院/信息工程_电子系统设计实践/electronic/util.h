#ifndef UTIL_H
#define UTIL_H

//https://blog.csdn.net/ourrtems/article/details/50818644
#define HD7279_RESET        0xa4  // RESET or CLEAR instruction
#define HD7279_TEST         0xbf  // TEST instruction
#define HD7279_READKEY      0x15  // READ instruction

#define DS18B20_IGNOREROM   0xcc
#define DS18B20_TRANS       0x44
#define DS18B20_READ        0xbe


#define EE24C16_WRITE_ADDRESS   0xa0
#define EE24C16_READ_ADDRESS    0xa1

#define BUTTON_DOWN         0x3b // Top left button,down arrow
#define BUTTON_UP           0x3a // Top right button,up arrow
#define BUTTON_LEFT         0x39 // Buttom left button,left arrow cancel or exit
#define BUTTON_ENTER        0x38 // Buttom right button,enter

#define LEDZERO 0x90 // the first LED position,buttom left

#define LED_0   0xfc
#define LED_1   0x44
#define LED_2   0x79
#define LED_3   0x5d
#define LED_4   0xc5
#define LED_5   0x9d
#define LED_6   0xbd
#define LED_7   0x54
#define LED_8   0xfd
#define LED_9   0xdd
    
#define LED_t   0xa9
#define LED_P   0xf1
#define LED_r   0x21
#define LED_u   0x2c
#define LED_n   0x25
#define LED_C   0xb8
#define LED_o   0x2d
#define LED_A   0xf5
#define LED_H   0xe5
#define LED_L   0xa8
#define LED_d   0x6d
#define LED_E   0xb9
#define LED_LINE 0x01
#define LED_NULL 0x00
#define LED_DOT 2 // plus this if want a dot

#define MENU_MAIN_TD    0x00
#define MENU_MAIN_MT    0x01
#define MENU_MAIN_MS    0x02
#define MENU_MAIN_PS    0x03
#define MUNU_MAIN_PID   0x04

#define MENU_TEMP_DETE      0x80 // Temperature detection
#define MENU_MOTOR_TEST     0x81 // Motor testing
#define MENU_MOTOR_SPEED    0x82 // Motor speed regulation
#define MENU_PARA_SET       0x83 // Parameter setting
#define MUNU_PID            0x84

#define MENU_PARA_MOTOR_TEST    0xc3 // para Motor testing
#define MENU_PARA_MOTOT_SPEED   0xcb // para Motor speed regulation

#endif



