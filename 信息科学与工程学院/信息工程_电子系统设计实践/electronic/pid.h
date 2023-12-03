#ifndef PID_H
#define PID_H

#include <REG52.h>
#include <ee24c16.h>
#include <motor.h>
#include <ds18b20.h>
#include <util.h>
#include <common.h>
extern unsigned char LED[8];
extern const unsigned char Number[10];
extern unsigned char paraMode;
extern unsigned char key,lastKey;
extern unsigned char MenuID;



void pidControl(float tempNow, float tempSet);
void modifyPassword(unsigned short password);
void temp_pid();

#endif