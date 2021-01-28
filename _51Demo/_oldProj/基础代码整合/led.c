#include <reg51.h>   	//51单片机头文件
#include <intrins.h>	//左右移函数等头文件
#include <jichu.h>
void LED()			//灯全亮
{
	led=0x00;			//8位字码，使"0"亮"1"灭
	delay(2000);
	led=0xff;			//全灭
}
void LED1()			//流水灯函数
{
	uchar i,j,k;
	P2=~0x00;
	for(j=0;j<1;j++)
	{
	for(i=0;i<8;i++)		//运行8次
		{
			P2=~(0x01<<i);	//将1右移i位，然后将结果赋值到P2口
			delay(100);
		}	
	if(i==8)
	{
		for(k=0;k<8;k++)	//运行8次
		{
			P2=~(0x80>>k);	//将1左移k位，然后将结果赋值到P2口
			delay(100); 
		}
		i=9;							//跳出函数
	}
	}
		delay(2000);
}
//另一个移位函数
/*		for(i=0;i<7;i++)	 //将led左移一位
		{
			led=_crol_(led,1);
			delay(100); 
		}
		for(i=0;i<7;i++)	//将led右移一位
		{
			led=_cror_(led,1);
			delay(100); 
		}
*/
