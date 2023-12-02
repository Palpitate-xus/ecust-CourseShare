#ifndef PARA_H
#define PARA_H

#include <util.h>
#include <ee24c16.h>

extern unsigned char LED[8];
extern const unsigned char Number[10];
extern unsigned char paraMode;
extern unsigned char key;
extern unsigned char MenuID;

extern unsigned char tempMax;
extern unsigned char tempMin;

void paraMenu(void);
void para_motorTest(void);
void para_tempModift(void);

#endif