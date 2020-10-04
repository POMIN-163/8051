#include <reg51.h>
#include <stdio.h>

int a=0;
int a1[100];










void delay_5ms();
/*void delay()
{
	unsigned int b;
	for(b=0;b<1000;b++);
}*/

unsigned char code disp[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
unsigned char code number[]={0x3E,0x3D,0x3B,0x37,0x2F,0x1F};

void main()
{
	TMOD=0x01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	EA=1;
	ET0=1;
	TR0=1;
	while(1)
	{
		  for(a=0;a<86400;)
		  {
			  P0=disp[a%10];
			  P1=number[5];
				delay_5ms();
				P0=0x00;
			  P0=disp[(a/10)%6];
			  P1=number[4];
				delay_5ms();
				P0=0x00;
				P0=disp[(a/60)%10];
			  P1=number[3];
				delay_5ms();
				P0=0x00;
				P0=disp[(a/60)%6];
			  P1=number[2];
				delay_5ms();
				P0=0x00;
				P0=disp[(a/3600)%10];
			  P1=number[1];
				delay_5ms();
				P0=0x00;
				P0=disp[(a/3600)%3];
			  P1=number[0];
				delay_5ms();
				P0=0x00;
			}

		}
}

/*void delay()
{
	unsigned int j;
	TMOD=0x01;
	for(j=0;j<20;j++)
	{
		TH0=(65536-50000)/256;
		TL0=(65536-50000)%256;
		TR0=1;
		while(TF0==0);
		TF0=0;
		a++;
	}
}*/

void timer_1s() interrupt 1
{
	unsigned int j=0;
	j++;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	if(j==20)
	{
		j=0;
		a++;
	}
}

void delay_5ms()
{
  unsigned int i;
  for(i=0;i<5;i++)
	{
  TH1=0xFC;
  TL1=0x18;
  TR1=1;
  while(!TF1);
  TF1=0;
	}
}