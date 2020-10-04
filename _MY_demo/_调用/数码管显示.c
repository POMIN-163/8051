#include <reg51.h>
#define uint unsigned int
#define uchar unsigned char
//uint、uchar宏定义
sbit smg1=P2^2;
sbit smg2=P2^3;
sbit smg3=P2^4;//数码管IO

void delay(uint x){
    while(x--);
}

uchar code smgz[]={
    0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
    0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//显示0~F的值

//接收数值-->显示
void display(uint rec){
    uchar i;
    char smg[8]={-1,-1,-1,-1,-1,-1,-1,-1};
        smg[0]=smgz[rec%10];
        smg[1]=smgz[(rec/10)%10];
        smg[2]=smgz[(rec/100)%10];
        smg[3]=smgz[(rec/1000)%10];
        smg[4]=smgz[(rec/10000)%10];
    for (i = 0; i < 8; i++) {
        smg1=((i)&0x01);
        smg2=((i>>1)&0x01);
        smg3=((i>>2)&0x01);
        if (smg[i]==-1)
            P0 =0x00;
        else
            P0 =smg[i];//段码///这三行不可更改否则可能重影
        delay(100);//延时
        P0 = 0x00;//消隐
    }
}