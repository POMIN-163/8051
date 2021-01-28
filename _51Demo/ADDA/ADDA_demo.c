#include "ADC.h"

sbit k1 = P3^1;
sbit k2 = P3^2; //按键(切换模式)

sbit smg1=P2^2;
sbit smg2=P2^3;
sbit smg3=P2^4; // 数码管IO

sbit PWM=P2^1;  // PMW管脚

uint timer1;    // 定时器全局变量

uchar code smgz[]={
0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,};
// 0、1、2、3、4、5、6、7、8、9、A、b、C、d、E、F的显示码

uchar address[]={0x94,0xd4,0xa4,0xe4};//电位器,热敏电阻,光敏电阻,预留脚地址

//---- 延时函数 ----//
void delay(uint x){
    while(x--);
}
//---- 数码管显示 ----//
void display(uint rec,uchar num){
    uchar i;
    char smg[8]={-1,-1,-1,-1,-1,-1,-1,-1};
        smg[0]=smgz[rec%10];
        smg[1]=smgz[(rec/10)%10];
        smg[2]=smgz[(rec/100)%10];
        smg[3]=smgz[(rec/1000)%10];
        smg[4]=smgz[(rec/10000)%10];
        smg[7]=smgz[num+1];
    for (i = 0; i < 8; i++) {
        smg1=((i)&0x01);
        smg2=((i>>1)&0x01);
        smg3=((i>>2)&0x01);
        if (smg[i]==-1)
            P0 =0x00;
        else
            P0 =smg[i];//段码///这三行不可更改否则可能重影
        delay(100);                //延时
        P0 = 0x00;                //消隐
    }
}
//---- 定时器1初始化 ----//
void Timer1Init()
{
    TMOD|=0X10;     //选择为定时器1模式，工作方式1，仅用TR1打开启动。

    TH1 = 0xff;
    TL1 = 0xff;     //1us

    ET1=1;          //打开定时器1中断允许
    EA=1;           //打开总中断
    TR1=1;          //打开定时器
}
//---- 主函数 ----//
void main(){
    uchar num,i;
    uint log, value = 0; bit turn = 0, type = 0;
    Timer1Init();
    ADC_Start();
    while(1){
        if (k2==0)              // 按键切换ADC/DAC
            {
                delay(500);
                if (k2==0)
                    type = ~type;
                while (k2==0);
            }
        if (type){              // DAC呼吸灯
            EA = 1;
            value += (turn*(-2)+1);
            if(value==1000|value==0)
                turn = ~turn;
            if(timer1 > 1000)
                timer1=0;
            if(timer1 < value)
                PWM=1;
            else
                PWM=0;
        }else{
            EA = 0;                 // ADC检测
            log = AD_Read_Data(address[num]);
            while (i<20)            // 防止频闪
            {
                if (k1==0)          // 按键切换检测ADC目标
                {
                    delay(500);
                    if (k1==0)
                    {
                        num++;
                        if (num==4)
                            num=0;
                    }while (k1==0);
                    log = AD_Read_Data(address[num]);
                }
                    display(log,num);
                    i++;

            }
            i=0;
        }
    }
}
//---- 定时器1中断(呼吸灯用) ----//
void Time1(void) interrupt 3
{
    TH1 = 0xff;
    TL1 = 0xff;
    timer1++;
}
