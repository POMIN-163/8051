#ifndef _MAIN_
#define _MAIN_
#include "REG51.H"
#define uint unsigned int
#define uchar unsigned char// �򻯱�������
#define u16 uint
#define u8 uchar

#define bool bit
#define true 1
#define false 0 // ����α bool ����

sbit int_0 = P2 ^ 4;
sbit int_1 = P2 ^ 5;
sbit led = P2 ^ 1;

sbit PWM_OUT = P2 ^ 0;// PWM ����ܽ�


#endif
