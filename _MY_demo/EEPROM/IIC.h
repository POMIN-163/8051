#ifndef _IIC_H_
//标识的命名规则一般是头文件名全大写，前后加下划线，
//并把文件名中的“.”也变成下划线
#define _IIC_H_
//---包含头文件---//
#include <reg51.h>
#include "intrins.h"
//---重定义关键词---//
#ifndef uchar
#define uchar unsigned char
#endif
#ifndef uint
#define uint unsigned int
#endif

#define At24c02_address 0xa0//AT24C02地址位
#define I2c_Read 1//AT24C02读
#define I2c_Write 0//AT24C02写

sbit SCL=P2^1;//IIC时钟线
sbit SDA=P2^0;//IIC数据线

void delay5us();//精确延时

void I2c_Start();//开始收发数据
void I2c_Stop();//停止收发数据

uchar I2c_Read_Byte();//读一字节
bit I2c_Send_Byte(uchar DAT);//发一字节，返回应答结果

void At24c02Write(uchar ADDR ,uchar DAT);//写入指令
uchar At24c02Read(uchar ADDR);//读出指令

#endif