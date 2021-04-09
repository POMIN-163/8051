#ifndef _DS18B20_H_
#define _DS18B20_H_
//---包含头文件---//
#include "REG51.H"
#include "intrins.h"
//---重定义关键词---//
#ifndef uchar
#define uchar unsigned char
#endif
#ifndef uint
#define uint unsigned int
#endif
sbit led = P2^0;//指示灯

sbit smg1=P2^2;
sbit smg2=P2^3;
sbit smg3=P2^4;//数码管IO

sbit DS_port = P3^7;//DS18B20总线

void delay_us(uchar i);//高精度延时

bit DS18B20_Init();//初始化
void DS18B20_Write(uchar dat);//发送数据
uchar DS18B20_Read();//读数据
uint DS18B20_Result();//返回16位结果

#endif
