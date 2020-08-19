#include "reg52.h"			 //此文件中定义了单片机的一些特殊功能寄存器

void UsartInit()        //设置串口
{
	SCON=0X50;			//设置为工作方式1
	TMOD=0X20;			//设置计数器工作方式2
	PCON=0X80;			//波特率加倍
	TH1=0XFA;				//计数器初始值设置，注意波特率是9600的
	TL1=0XFA;
	ES=1;						//打开接收中断
	EA=1;						//打开总中断
	TR1=1;					//打开计数器
}


void Usart() interrupt 4	//进入中断服务函数
{
	char receiveData;

	receiveData=SBUF;//出去接收到的数据，此时SBUF存放接收数据
	RI = 0;//清除接收中断标志位
	if(receiveData=='1') 
	{
		ret=1;			 //接收1时，打开LED灯
	}
	if(receiveData=='0') 
	{
		ret=2;			 //接收0时，关闭LED灯
	}
    SBUF=receiveData;
	while(!TI);			 //等待发送数据完成
	TI=0;						 //清除发送完成标志位
}
