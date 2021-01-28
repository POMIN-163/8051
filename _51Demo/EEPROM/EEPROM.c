#include "IIC.h"

sbit k1 = P3^1;
sbit smg1=P2^2;
sbit smg2=P2^3;
sbit smg3=P2^4;//数码管IO
uchar rec=0;
uchar code smgz[]={//显示0~F的值
    0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
    0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71
};

void delay(uint x){
    while(x--);
}
void delay5us(){   //误差 0us
    _nop_();
}
void display(uint rec){// 数码管4位16进制最高65535
    uchar i;
    if (rec<65536){
        char smg[8]={-1,-1,-1,-1,-1,-1,-1,-1,};
              smg[0] = (rec)%16;
            smg[1] = (rec)/16%16;
            smg[2] = (rec/256)%16;
            smg[3] = (rec/4096)%16;
        for (i = 0; i < 8; i++){
            smg1=((i)&0x01);
            smg2=((i>>1)&0x01);
            smg3=((i>>2)&0x01);
            if (smg[i]==-1)
                P0 = 0x00;
            else
                P0 =smgz[smg[i]];   //段码///这三行不可更改否则可能重影
            delay(100);                //延时
            P0 = 0x00;                //消隐
        }
    }
}

void PORT_START()//串口
{
    TMOD=0x20;  //定时器方式2
    PCON=0x80;  //波特率倍增
    SCON=0x50;  //8位异步收发模式
    TH1=0xf9;   //定时器初值
    TL1=0xf9;   //
    TR1=1;      //启动定时器
    ES=1;       //串口开关
    EA=1;       //总开关
}

void port()interrupt 4//串口中断
{
 //发送时发送01,02的字节形式不能用1或2整数形式
        rec = 0;
    RI=0;           //接收中断标志复位置0
    rec=SBUF;       //读取接收缓存,赋值全局变量以触发事件
    SBUF=rec;       //回复数据
    rec-=0x80;
    while (!TI);    //等待接收完毕
    TI=0;           //复位
}
void main(){
  uchar num=0;
    PORT_START();
    num = At24c02Read(3);//读出第3单元内数据送给显示变量
    rec = num;//避免初始化清除原先数据
    while (1){
        if(num != rec){
            num = rec;
            At24c02Write(3, rec);//给第3单元写入串口收到的数据
        }
        display(num);//投到数码管上面
    }
}