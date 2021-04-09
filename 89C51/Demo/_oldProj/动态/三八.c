#include"reg51.h"
typedef unsigned char u8;
typedef unsigned int u16;

sbit g1=P2^2;
sbit g2=P2^3;
sbit g3=P2^4;

u8 code smgduan[]={0x3f,0x06,0x4f,0x5b,0x66,0x6d,0x7d,0x07,0x7f
,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

void delay(u8 i)
{
	while(i--);
}

void main()
{
	while(1)
	{
	g1=0,g2=0,g3=0;
	delay(1000);
	g1=0,g2=1,g3=0;
	}	
}	