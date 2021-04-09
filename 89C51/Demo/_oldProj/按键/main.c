#include"reg51.h"
typedef unsigned int u16;
typedef unsigned char u8;
sbit led1=P2^0;
sbit s1=P3^1;
sbit s2=P3^2;
sbit GAA=P2^2;
sbit GBB=P2^3;
sbit GCC=P2^4;

u8 code smgduan[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
void delay(u16 i)
{
	while(i--);
}

void smg()
{
	u8 i;
	for(i=0;i<8;i++)
	{
		switch(i)
		{
			case(0):
			GAA=0;GBB=0;GCC=0;break;
			case(1):
			GAA=1;GBB=0;GCC=0;break;
			case(2):
			GAA=0;GBB=1;GCC=0;break;
			case(3):
			GAA=1;GBB=1;GCC=0;break;
			case(4):
			GAA=0;GBB=0;GCC=1;break;
			case(5):
			GAA=1;GBB=0;GCC=1;break;
			case(6):
			GAA=0;GBB=1;GCC=1;break;
			case(7):
			GAA=1;GBB=1;GCC=1;break;
		}
		P0=smgduan[i];
		delay(10000);
		P0=0x00;
	}	
}
void key()
{
	if(s1==0)
		{
			delay(10);
			if(s1==0&s2==0)
				{
					while(1)
					{
					smg();
					if(s1==0){break;}
					}
				}
		}
		while(!s1&!s2);
}

void main()
{
	{key();}
}
