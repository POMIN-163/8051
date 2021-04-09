#include "DS18B20.h"
void delay_us(uchar i){   //误差 0us
    i/=5;
    while(i){
        i--;
        _nop_();
    }
}
bit DS18B20_Init(){// 初始化
    bit i;
    DS_port = 1;// 拉高总线准备
    delay_us(10);
    DS_port = 0;// 拉低总线
    delay_us(500);//>480us使其复位
    DS_port = 1;// 释放总线
    delay_us(40);// 等待40us(5-60us)
    i = DS_port;// 返回值0正常，1异常
    delay_us(200);
    DS_port = 1;// 释放总线
    led = i;// 指示灯
    return (i);
}
void DS18B20_Write(uchar dat){// 写一字节数据(严格时序)
    uchar i;
    for (i = 0; i < 8; i++){//写一字节,先低位后高位
        DS_port = 0;//拉低总线
        delay_us(5);//延时5us(>1us)
        DS_port = dat&0x01;//先低位
        delay_us(80);//保证>60且<120
        DS_port = 1;//释放总线
        delay_us(5);//延时5us准备下一位
        dat>>=1;//下一位
    }
}
uchar DS18B20_Read(){// 读一字节数据(严格时序)
    uchar j , i,dat;
    for (i = 0; i < 8; i++){//写一字节,先低位后高位
        DS_port = 0;//拉低总线
        delay_us(5);//延时5us
        DS_port = 1;//释放总线
        j = DS_port;
        delay_us(80);//保证>60us
        DS_port = 1;//释放总线
        delay_us(5);//延时5us准备下一位
        dat = (j<<7)|(dat>>1);//处理数据(先低后高)
    }
    return dat;
}
uint DS18B20_Result(){// 结果
    uchar L,M;
    DS18B20_Init();
    DS18B20_Write(0xcc);//发送跳跃ROM指令
    DS18B20_Write(0x44);//发送温度转换指令
    DS18B20_Init();//做任何操作先初始化
    DS18B20_Write(0xcc);//发送跳跃ROM指令
    DS18B20_Write(0xbe);//读取DS18B20暂存器值
    L = DS18B20_Read();//低8位
    M = DS18B20_Read();//高8位
    return ((M<<8)|L);
}