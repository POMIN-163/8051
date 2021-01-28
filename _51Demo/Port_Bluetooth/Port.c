#include "REG51.H"
#define uint unsigned int    //之后使用uint定义整形
#define uchar unsigned char    //之后使用uchar定义字符型
sbit led = P2^0;
sbit smg1=P2^2;
sbit smg2=P2^3;
sbit smg3=P2^4;//数码管IO

uchar rec;

uchar code smgz[]={
    0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
    0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
    //显示0~F的值

void delay(uint x){
    while(x--);
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
    RI=0;           //接收中断标志复位置0
    rec=SBUF;       //读取接收缓存,赋值全局变量以触发事件
    SBUF=rec;       //回复数据
    //rec-=0x80;
    while (!TI);    //等待接收完毕
    TI=0;           //复位
}
void main(){
    uchar i;
    char smg[8]={-1,-1,-1,-1,-1,-1,-1,-1,};
    PORT_START();
    while (1){
    /*  smg[0]=(rec&0x01);//2进制显示
        smg[1]=(rec&0x02)>>1;
        smg[2]=(rec&0x04)>>2;
        smg[3]=(rec&0x08)>>3;
        smg[4]=(rec&0x10)>>4;
        smg[5]=(rec&0x20)>>5;
        smg[6]=(rec&0x40)>>6;
        smg[7]=(rec&0x80)>>7; */
        smg[0]=rec%16;
        smg[1]=(rec)/16%16;
        smg[2]=(rec/256)%16;
        smg[3]=(rec/4096)%16;
    for (i = 0; i < 8; i++)
    {
        smg1=((i)&0x01);
        smg2=((i>>1)&0x01);
        smg3=((i>>2)&0x01);
        if (smg[i]==-1)
            P0 =0x00;
        else
            P0 =smgz[smg[i]];//段码///这三行不可更改否则可能重影
        delay(100);                //延时
        P0 = 0x00;                //消隐
    }
    switch (rec)
    {
        case(0x00):smg[5]=0;led=0;break;
        case(0x01):smg[5]=1;led=1;break;
        case(0x02):smg[5]=2;break;
        case(0x03):smg[5]=3;break;
        case(0x04):smg[5]=4;break;
        case(0x05):smg[5]=5;break;
        case(0x06):smg[5]=6;break;
        case(0x07):smg[5]=7;break;
        case(0x08):smg[5]=8;break;
        case(0x09):smg[5]=9;break;
        case(0x10):smg[5]=10;break;
        case(0x11):smg[5]=11;break;
        case(0x12):smg[5]=12;break;
        case(0x13):smg[5]=13;break;
        case(0x14):smg[5]=14;break;
        case(0x15):smg[5]=15;break;
    }
}
}