#include <reg51.h>  
#include <jichu.h>
void TimerInit0()
{	
	TMOD|=0X01;	//选择为定时器0模式，
							//工作方式1，仅用TR0打开启动。
	TH0=0XFC;		//给定时器赋初值，定时1ms
	TL0=0X18;	
	ET0=1;			//打开定时器0中断允许
	EA=1;				//打开总中断
	TR0=1;			//打开定时器			
}
void timer0() interrupt 1
{
	static uint i;
	TH0=0XFC;	//给定时器赋初值，定时1ms
	TL0=0X18;
	i++;
	if(i==1000)
	{
		i=0;
		led=~led;	
	}	
}