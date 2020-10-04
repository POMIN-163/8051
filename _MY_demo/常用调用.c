#include <reg51.h>
#include "INTRINS.H"
#define uint unsigned int    //之后使用uint定义整形
#define uchar unsigned char    //之后使用uchar定义字符型

void delay(uint x){//1us延时
    while(x--);
}
void delay5us(){// 5us延时
    _nop_();
}
uchar code smgz[]={//显示0~F的值
    0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
    0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};    
void delay(uint z){// 1ms延时
    uint x,y;
    for(x = z; x > 0; x--)
        for(y = 114; y > 0 ; y--);
}