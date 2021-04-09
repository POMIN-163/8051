#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
#define GPIO_KEY P1;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

uint KeyValue;
uint a;

char code duan[16]={0x3f,0x06,0x5b,0x4f,0x66,
                    0x6d,0x7d,0x07,0xef,0xcf};

void delayms(uint i)//**************延时函数，约为 i ms
{
	uint j;
	for(i;i>0;i--)
  {
		for(j=110;j>0;j++);
	}
}

void keydown()
{
  P1 = 0x0f;
  if(P1!=0x0f)
  {
	delayms(1);//*******************按键消抖
    if(P1!=0x0f)
		{
			P1=0x0f;
			switch(P1)//************列扫描
			{
				case(0x07):KeyValue=0;break;
				case(0x0b):KeyValue=1;break;
				case(0x0d):KeyValue=2;break;
				case(0x0e):KeyValue=3;break;
			}
			P1=0xf0;
			switch(P1)//************行扫描
			{
				case(0x70):KeyValue=KeyValue+0;break;
				case(0xb0):KeyValue=KeyValue+4;break;
				case(0xd0):KeyValue=KeyValue+8;break;
				case(0xe0):KeyValue=KeyValue+12;break;
			}
			while((a<50)&&(P1!=0xf0))//按键按下超时自动退出
			{
				delayms(1);
				a++;
			}
		}
	}
}


void main()
{
	LSA=0;LSB=0;LSC=0;
	while(1)
	{
		keydown();
		P0=duan[KeyValue];
	}
}