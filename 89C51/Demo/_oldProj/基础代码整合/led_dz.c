#include <reg51.h>   
#include <intrins.h>	
#include <jichu.h>
uchar ledduan[]={
0x00,0x00,0x3E,0x41,
0x41,0x41,0x3E,0x00};		//�����ڶ�̬����ܵĶ�ѡ 0
uchar ledwei[]={
0x7f,0xbf,0xdf,0xef,
0xf7,0xfb,0xfd,0xfe};		//�����ڶ�̬����ܵ�λѡ 0
void LED_Byte(uchar dat)//һλһλ���ͣ�һ��һ���Ƶ�����
{
	uchar a;
	SRCLK = 1;
	RCLK = 1;
	for(a=0;a<8;a++)			//����8λ��
	{	
		SER = dat >> 7;		 	//�����λ��ʼ����
		dat <<= 1;
		SRCLK = 0;					//����ʱ��
		_nop_();
		_nop_();
		SRCLK = 1;	
	}
	RCLK = 0;
	_nop_();
	_nop_();
	RCLK = 1;
}
void LED_Z()						//��ʾ����
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