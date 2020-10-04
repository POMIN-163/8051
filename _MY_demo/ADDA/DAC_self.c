#include<reg52.h>
#define uint unsigned int

sbit PWM=P2^1;
uint timer1;

//---- 定时器1初始化 ----//
void Timer1Init()
{
    TMOD|=0X10;    //选择为定时器1模式，工作方式1，仅用TR1打开启动。

    TH1 = 0xff;
    TL1 = 0xff; //1us

    ET1=1;        //打开定时器1中断允许
    EA=1;        //打开总中断
    TR1=1;        //打开定时器
}
//---- 主函数 ----//
void main()
{
    uint value = 0; bit turn = 0;
    Timer1Init();
    while(1)
    {
        value += (turn*(-2)+1);
        if(value==1000|value==0)
            turn = ~turn;
        if(timer1 > 1000)
            timer1=0;
        if(timer1 < value)
            PWM=1;
        else
            PWM=0;
    }
}
//---- 定时器1的中断 ----//
void Time1(void) interrupt 3
{
    TH1 = 0xff;
    TL1 = 0xff;
    timer1++;
}
