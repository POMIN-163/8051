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