#include "DS1302.h"

sbit smg1=P2^2;
sbit smg2=P2^3;
sbit smg3=P2^4;//数码管IO

uchar code smgz[]={
    0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
    0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//显示0~F的值

void delay(uint i){
    while(i--);
}
void display(){// 数码管4位16进制最高65535
    uchar i;
    char smg[8]={-1,-1,-1,-1,-1,-1,-1,-1,};
    Ds1302ReadTime();
    smg[0] = smgz[TIME[0]&0x0f];      //秒
    smg[1] = smgz[(TIME[0]<<1)>>5];
    smg[2] = 0x40;
    smg[3] = smgz[TIME[1]&0x0f];      //分
    smg[4] = smgz[(TIME[1]<<1)>>5];
    smg[5] = 0x40;
    smg[6] = smgz[TIME[2]&0x0f];      //时
    smg[7] = smgz[(TIME[2]<<1)>>5];
  /*smg[0] = smgz[TIME[3]&0x0f];      //日
    smg[1] = smgz[TIME[3]>>4];
    smg[2] = 0x40;
    smg[3] = smgz[TIME[4]&0x0f];      //月
    smg[4] = smgz[TIME[4]>>4];
    smg[5] = 0x40;
    smg[6] = smgz[TIME[6]&0x0f];      //年
    smg[7] = smgz[TIME[6]>>4];
    smgz[TIME[5]];                      //星期
    */
    for (i = 0; i < 8; i++){
        smg1=((i)&0x01);
        smg2=((i>>1)&0x01);
        smg3=((i>>2)&0x01);
        if (smg[i]==-1)
            P0 = 0x00;
        else
            P0 =smg[i];     //段码///这三行不可更改否则可能重影
        delay(100);            //延时
        P0 = 0x00;            //消隐
    }
}
void main(){
//Ds1302Init();//第一次初始化后就可以注释该条语句，这样下次重启就不会再次初始化了
    while(1){
        display();//数码管显示函数
    }
}
