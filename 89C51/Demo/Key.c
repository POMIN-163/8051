#include <reg51.h>           //51单片机头文件
#define uint unsigned int    //之后使用uint定义整形
#define uchar unsigned char    //之后使用uchar定义字符型

sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;
sbit k4=P3^3;//独立按键IO

//uint、uchar宏定义
sbit smg1=P2^2;
sbit smg2=P2^3;
sbit smg3=P2^4;//数码管IO
uchar code smgz[] = {
    0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
    0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
    //显示0~F的值


void delay(uint x){                //延迟函数10us左右
    while(x--);
}
// 数码管显示
void display(uchar mod,uint rec,bit dir){
    uchar i;
    char smg[8] = {-1,-1,-1,-1,-1,-1,-1,-1};
        smg[0] = smgz[rec%10];
        smg[1] = smgz[(rec/10)%10];
        smg[2] = smgz[(rec/100)%10];
        smg[4] = smgz[mod];
        smg[6] = smgz[dir];
    for (i = 0; i < 8; i++) {
        smg1 = ((i)&0x01);
        smg2 = ((i>>1)&0x01);
        smg3 = ((i>>2)&0x01);
        if (smg[i] == -1)
            P0  = 0x00;
        else
            P0  = smg[i];//段码///这三行不可更改否则可能重影
        delay(100);                //延时
        P0 = 0x00;                //消隐
    }
}
uchar KEY_ALL(){                //按键处理函数
    uchar key,a;
    P1=0x0f;
    if(P1!=0x0f){                //读取按键是否按下
        delay(1000);
        if(P1!=0x0f){            //再次检测键盘是否按下
            P1=0X0f;            //测试列
            switch(P1){
                case(0X07):    key=0;break;
                case(0X0b):    key=1;break;
                case(0X0d): key=2;break;
                case(0X0e):    key=3;break;
            }
            P1=0Xf0;            //测试行
            switch(P1){
                case(0X70):    key=key;break;
                case(0Xb0):    key=key+4;break;
                case(0Xd0): key=key+8;break;
                case(0Xe0):    key=key+12;break;
            }
        }
    }                            //测试独立按键
    if(k1==0){delay(10);if(k1==0){key=17;}while(!k1);}
    if(k2==0){delay(10);if(k2==0){key=18;}while(!k2);}
    if(k3==0){delay(10);if(k3==0){key=19;}while(!k3);}
    if(k4==0){delay(10);if(k4==0){key=20;}while(!k4);}
    while (a<50&&P1!=0xf0){
        delay(10);
        a++;
    }
    return key;
}

uchar KEY_16(){                        //矩阵按键检测函数
    uchar key,a;
    P1=0x0f;
    if(P1!=0x0f){                //读取按键是否按下
        delay(1000);
        if(P1!=0x0f){            //再次检测键盘是否按下
            P1=0X0f;            //测试列
            switch(P1){
                case(0X07):    key=0;break;
                case(0X0b):    key=1;break;
                case(0X0d): key=2;break;
                case(0X0e):    key=3;break;
            }
            P1=0Xf0;            //测试行
            switch(P1){
                case(0X70):    key=key;break;
                case(0Xb0):    key=key+4;break;
                case(0Xd0): key=key+8;break;
                case(0Xe0):    key=key+12;break;
            }
        }
    }
    while (a<50&&P1!=0xf0){
        delay(500);
        a++;
    }
    return key;
}
uchar KEY_4(){                        //独立按键检测函数
    uchar key;
    if(k1==0){delay(10);if(k1==0){key=17;}while(!k1);}
    if(k2==0){delay(10);if(k2==0){key=18;}while(!k2);}
    if(k3==0){delay(10);if(k3==0){key=19;}while(!k3);}
    if(k4==0){delay(10);if(k4==0){key=20;}while(!k4);}
    return key;
}

void main(){            //主函数入口
		uint a;
    while(1){

        a = KEY_ALL();
        //KEY_4();
      //  KEY_16();
				display(a);
    }
}