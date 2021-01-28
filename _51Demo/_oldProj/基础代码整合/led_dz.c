#include <reg51.h>   
#include <intrins.h>	
#include <jichu.h>
uchar ledduan[]={
0x00,0x00,0x3E,0x41,
0x41,0x41,0x3E,0x00};		//类似于动态数码管的段选 0
uchar ledwei[]={
0x7f,0xbf,0xdf,0xef,
0xf7,0xfb,0xfd,0xfe};		//类似于动态数码管的位选 0
void LED_Byte(uchar dat)//一位一位发送（一个一个灯点亮）
{
	uchar a;
	SRCLK = 1;
	RCLK = 1;
	for(a=0;a<8;a++)			//发送8位数
	{	
		SER = dat >> 7;		 	//从最高位开始发送
		dat <<= 1;
		SRCLK = 0;					//发送时序
		_nop_();
		_nop_();
		SRCLK = 1;	
	}
	RCLK = 0;
	_nop_();
	_nop_();
	RCLK = 1;
}
void LED_Z()						//显示单字
{
		uchar i,j;
		for(j=0;j<100;j++)
		{	
			for(i=0;i<8;i++)
	   {
				led_dz=ledwei[i];
	   		LED_Byte(ledduan[i]);			  
				delay(2);		
				LED_Byte(0x00);
	   }
		}
}