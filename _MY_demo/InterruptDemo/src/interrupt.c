#include "interrupt.h"

uint PWM_Value = 1000U; // PWM 值


void int0()interrupt 0//int0中断
{
    int_0 = !int_0;
}
void int1()interrupt 2//int1中断
{
    int_1 = !int_1;
}
void timer0() interrupt 1
{
    static uint PWM_NUM = 0;// PWM 计次
    static bool order = true;
    if (order) {
				PWM_OUT = 1;
				TH0 = (65536 - PWM_Value) >> 8;
				TL0 = (char)(65536 - PWM_Value);
    }
    else {
				PWM_OUT = 0;
				TH0 = (65536 - PWM_Value) >> 8;
				TL0 = (char)(65536 - PWM_Value);
    }
    order = !order;
    PWM_NUM++;
    if (PWM_NUM == 500){PWM_OUT = !PWM_OUT;PWM_NUM = 0;}
}
void timer1()interrupt 3
{
    static uint T1_NUM;// 定时器 1 计次
    TH1 = (65536 - 1000) >> 8;// 高 8
    TL1 = (char)(65536 - 1000); // 低 8
    T1_NUM++;
    if (T1_NUM == 1000) {
        T1_NUM = 0;
        led = !led;
    }
}

