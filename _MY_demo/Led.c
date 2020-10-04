#include <reg51.h>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char
//uint、uchar宏定义
#define led P2

void delay(uint x){
    while(x--);
}
//闪烁灯函数
void LED(){
    led=0x00;//P2全亮
    delay(2000);
    led=0xFF;//全灭
}
//流水灯函数
void LED_RUN(){
    uchar i;
    P2=~0x00;//全灭
    for(i=0;i<8;i++){
        P2=~(0x01<<i);//将1右移i位，然后将结果赋值到P2口
        delay(10000);
    }
}
//主函数入口
void main(){
    while(1){
        LED();
        LED_RUN();
    }
}

//另一个移位函数
/*        for(i=0;i<7;i++)//将led左移一位
        {
            led=_crol_(led,1);
            delay(100);
        }
        for(i=0;i<7;i++)    //将led右移一位
        {
            led=_cror_(led,1);
            delay(100);
        }
*/
