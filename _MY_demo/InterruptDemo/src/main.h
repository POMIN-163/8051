#ifndef _MAIN_
#define _MAIN_
#include "REG51.H"
#define uint unsigned int
#define uchar unsigned char// 简化变量定义
#define u16 uint
#define u8 uchar

#define bool bit
#define true 1
#define false 0 // 引入伪 bool 类型

sbit int_0 = P2 ^ 4;
sbit int_1 = P2 ^ 5;
sbit led = P2 ^ 1;

sbit PWM_OUT = P2 ^ 0;// PWM 输出管脚


#endif
