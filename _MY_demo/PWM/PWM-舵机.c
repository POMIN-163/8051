#include <reg52.h>

#define uchar unsigned char
#define uint unsigned int

sbit KEY1 = P3 ^ 2; // 按键1
sbit KEY2 = P3 ^ 3; // 按键2
sbit PWM_OUT = P2 ^ 0; // PWM输出口

sbit smg1=P2^2;
sbit smg2=P2^3;
sbit smg3=P2^4;// 数码管IO

uchar code smgz[]=// 显示0~9的值
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

uint PWM_Value; // 定义pwm值
uchar order = 0;
uchar flag; // 舵机按键标志

//---- 延时函数 ----//
void delay(unsigned int s)
{
    while(s--);
}
//---- 定时器初始化 ----//
void Init_Timer0()
{
    TMOD = 0x11;
    TH0 = (65536 - 1500) / 256;
    TL0 = (65536 - 1500) % 256;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
    PT0 = 1;
}
void display(uint rec){// 数码管4位16进制最高65535
    uchar i;
        char smg[8]={-1,-1,-1,-1,-1,-1,-1,-1,};
              smg[0] = smgz[(rec)%10];
            smg[1] = smgz[(rec/10)%10];
            smg[2] = smgz[(rec/100)%10];
            smg[3] = smgz[(rec/1000)%10];
        for (i = 0; i < 8; i++){
            smg1=((i)&0x01);
            smg2=((i>>1)&0x01);
            smg3=((i>>2)&0x01);
            if (smg[i]==-1)
                P0 = 0x00;
            else P0 = smg[i];
            delay(100);                // 延时
            P0 = 0x00;                // 消隐
    }
}
//---- 主函数 ----//
void main(void)
{
    uint log = 0;
    PWM_Value = 1500; // pwm初值为1500
    Init_Timer0();
    while (1)
    {
        display(PWM_Value);
        log++;
        if(log < 1500) flag = 1; // 运用log来使得舵机摆头
        if(log > 1500) flag = 2;
        if(log > 3000) log = 0;
        /* if ((KEY1 == 0) | (KEY2 == 0)) // 按键1或按键2被按下
        {
            if (KEY1 == 0) // 确认按键1被按下
                flag = 1; // 标志位赋值1
            if (KEY2 == 0) // 确认按键2被按下
                flag = 2; // 标志位赋值2
        }
        else
        {
            // flag = 0; // 否则标志位为0
        }*/
        delay(100);
    }
}

//---- 中断程序 ----//
void timer0(void) interrupt 1
{
    if (flag == 1)
        PWM_Value += 1;     // 如果标志位1时，pwm的值加1
    if (flag == 2)          // 如果标志位为2时，pwm减1
        PWM_Value -= 1;
    if (PWM_Value >= 2500)  // 如果pwm的值大于2500则保持在2500(上限2.5ms)
        PWM_Value = 2500;
    if (PWM_Value <= 500)   // 如果pwm的值小于500则保持在500(下限0.5ms)
        PWM_Value = 500;
    switch (order)
    {
        case 1:
            PWM_OUT = 1;
            TH0 = (65536 - PWM_Value) >> 8;// PWM_Value单位为微秒
            TL0 = (char)(65536 - PWM_Value);
            break;
        case 2:
            PWM_OUT = 0;
            TH0 = (65536 - (5000 - PWM_Value)) >> 8;// 5ms
            TL0 = (char)(65536 - (5000 - PWM_Value));
            break;
        case 3:
            TH0 = 50536 >> 8;// 15ms
            TL0 = (char)50536;
            order = 0;
            break;
    }
    order++;
}
