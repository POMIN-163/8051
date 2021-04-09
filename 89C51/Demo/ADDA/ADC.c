#include"ADC.h"

//---- 初始设置(可以不用) ----//
void ADC_Start(void)
{
    DCLK = 0;
    CS  = 1;
    DIN = 1;
    DCLK = 1;
    CS  = 0;
}
//---- 写八位数据 ----//
void ADC_Write(uchar dat)
{
    uchar i;
    DCLK = 0;
    for(i=0; i<8; i++)
    {
        DIN = dat >> 7;        //放置最高位
        dat <<= 1;
        DCLK = 0;            //上升沿放置数据

        DCLK = 1;
    }
}
//---- 读入AD信号 ----//
uint ADC_Read(void)
{
    uint i, dat=0;
    DCLK = 0;
    for(i=0; i<12; i++)        //接收12位数据
    {
        dat <<= 1;

        DCLK = 1;
        DCLK = 0;

        dat |= DOUT;
    }
    return dat;
}
//---- 发送指令(传递所读目标) ----//
uint AD_Read_Data(uchar cmd)
{
    uchar i;
    uint AD_Value;
    DCLK = 0;
    CS  = 0;
    ADC_Write(cmd);
    for(i=6; i>0; i--);     //延时等待转换结果
    DCLK = 1;                //发送一个时钟周期，清除BUSY
        _nop_();_nop_();
    DCLK = 0;
        _nop_();_nop_();
    AD_Value = ADC_Read();
    CS = 1;
    return AD_Value;
}
