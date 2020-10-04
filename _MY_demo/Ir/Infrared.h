#ifndef _INFRARED_H_
#define _INFRARED_H_
//---包含头文件---//
#include<reg52.h>

//---重定义关键词---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

sbit Ir_IN = P3^2;
sbit Ir_OUT = P2^0;

void delay(uint i);
void Ir_Init();
void Ir_Read();
void IR_Send(unsigned long dat);

#endif
