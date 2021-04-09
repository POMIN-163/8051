#include"reg51.h"
typedef unsigned char u8;
typedef unsigned int u16;
sbit key=P3^0;
sbit beep=P2^5;
void delay(u16 i)
{
while(i--);
}
void speak()
{
	beep=~beep;
	delay(100);
}
void main()
{
while(1)
{
	if(key==0)
	{
		delay(1000);
		if(key==0)
		{
			speak();
		}
		while(!key);
	}	
}
}