#ifndef MOTOR_H
#define MOTOR_H

#include <REG52.h>
#include <util.h>
#include <common.h>
#include <ee24c16.h>

sbit motor = P1^2;

int setSpeed(float speedDelta);
void motorTest(unsigned char speed);
void motorControl(float temp);
void init_motor(void);
void pwmMotor(void);



#endif