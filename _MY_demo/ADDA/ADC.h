#ifndef _ADC_h_
#define _ADC_h_

#include<reg52.h>
#include<intrins.h>

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

sbit DOUT = P3^7;//输出
sbit DCLK  = P3^6;//时钟
sbit DIN  = P3^4;//输入
sbit CS   = P3^5;//片选

void ADC_Start(void);
uint AD_Read_Data(uchar cmd);
uint ADC_Read(void);
void ADC_Write(uchar dat);

#endif