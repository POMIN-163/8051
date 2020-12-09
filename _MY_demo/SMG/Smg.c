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
    0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
    //显示0~F的值

uchar smg[8]={0,1,2,3,4,5,6,7};

void SMG_LIGHT(uchar smg[]){        //八位数码管的内容数组
    uchar i;
    for (i = 0x00; i < 0x08; i++){    //八位数码管内容
        smg1=((i)&0x01);
        smg2=((i>>1)&0x01);
        smg3=((i>>2)&0x01);
        P0 =smgz[smg[7-i]];         //段码///这三行不可更改否则可能重影
        delay(100);                    //延时
        P0 = 0x00;                    //消隐
    }
}
/* void SMG_ALL(){                    //数码管全亮
    uchar i;
    for(i=0;i<240;i++){
        smg1=((i)&0x01);
        smg2=((i>>1)&0x01);
        smg3=((i>>2)&0x01);
        P0=smgz[8]
    }
    smg1=1,smg2=1,smg3=1;
    delay(2000);
} */

//数码管显示0~7  //OE短接VCC！        //位选方式
/* void SMG_SWITCH(){
    uchar i,j;
    for(j=0;j<200;j++){
    for(i=0;i<8;i++){
        switch(i){                     //位选，选择点亮的数码管，
            case(0):
                smg1=1;smg2=1;smg3=1;smg=smgz[i]; break;//显示第0位
            case(1):
                smg1=0;smg2=1;smg3=1;smg=smgz[i]; break;//显示第1位
            case(2):
                smg1=1;smg2=0;smg3=1;smg=smgz[i]; break;//显示第2位
            case(3):
                smg1=0;smg2=0;smg3=1;smg=smgz[i]; break;//显示第3位
            case(4):
                smg1=1;smg2=1;smg3=0;smg=smgz[i]; break;//显示第4位
            case(5):
                smg1=0;smg2=1;smg3=0;smg=smgz[i]; break;//显示第5位
            case(6):
                smg1=1;smg2=0;smg3=0;smg=smgz[i]; break;//显示第6位
            case(7):
                smg1=0;smg2=0;smg3=0;smg=smgz[i]; break;//显示第7位
        }
        delay(1);         //间隔一段时间扫描
        P0=0x00;        //消隐
    }
    }
} */

void main(){
    while (1){
        SMG_LIGHT(smg);
    }
}