#include "REG51.H"
#define uint unsigned int    //之后使用uint定义整形
#define uchar unsigned char    //之后使用uchar定义字符型
sbit k3=P3^2;
sbit k4=P3^3;

sbit led1=P2^1;
sbit led2=P2^2;
sbit led3=P2^3;
sbit beep=P2^5;

uchar rec;

/* void delay(uint x){
    while(x--);
} */
/*void INT0_START()//对应k3
{
    IT0=1;//信号类型(1为下降沿触发，0为高电平触发)
    EX0=1;//int0开关
    EA=1;//总开关
}
void INT1_START()//对应k4
{
    IT1=1;//信号类型(1为下降沿触发，0为高电平触发)
    EX1=1;//int1开关
    EA=1;//总开关
}
void TIME0_START()//定时器0
{
    TMOD|=0x01;
    TH0=0xfc;//高位
    TL0=0x18;//低位
    ET0=1;//time0开关
    TR0=1;//开启定时器
    EA=1;//总开关
}
void TIME1_START()//定时器1
{
    TMOD|=0x10;
    TH1=0xfc;//高位
    TL1=0x18;//低位
    ET1=1;//time1开关
    TR1=1;//开启定时器
    EA=1;//总开关
} */
void PORT_START()//串口
{
    TMOD=0x20;  //定时器方式2
    PCON=0x80;  //波特率倍增
    SCON=0x50;  //8位异步收发模式
    TH1=0xf3;   //定时器初值
    TL1=0xf3;   //
    TR1=1;      //启动定时器
    ES=1;       //串口开关
    EA=1;       //总开关
}
/* void int0()interrupt 0//int0中断
{
    delay(1000);
    if (k3==0)
        led1=~led1;
}
void int1()interrupt 2//int1中断
{
    delay(1000);
    if (k4==0)
        led2=~led2;
}
void time0()interrupt 1//定时器0中断
{
    static uint a;
    TH0=0xfc;//高位     //定时器初值复位配置
    TL0=0x18;//低位
    if (a==1000)
    {
        a=0;
        //led3=~led3;
    }
}
void time1()interrupt 3//定时器1中断
{
    static uint a;
    TH1=0xfc;//高位     //定时器初值复位配置
    TL1=0x18;//低位
    a++;
    if (a==1000)
    {
        a=0;
        //led3=~led3;
    }
} */

void port()interrupt 4//串口中断
{
 //发送时发送01,02的字节形式不能用1或2整数形式
    rec=SBUF;       //读取接收缓存,赋值全局变量以触发事件
    RI=0;           //接收中断标志复位置0
    SBUF=rec+0x01;  //回复数据
    while (!TI);    //等待接收完毕
    TI=0;           //复位
}
void main(){
/*     INT0_START();
    INT1_START();
    TIME0_START();
    TIME1_START(); */
    PORT_START();
    while (1){
        if (rec%2)//触发事件
        {
            P2=0x00;
        }else
        {
            P2=0xff;
        }
    }
}