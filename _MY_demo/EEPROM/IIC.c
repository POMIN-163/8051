#include "IIC.h"
void I2c_Start(){//开始信号(严格延时)
    SCL = 1;
    delay5us();
    SDA = 1;// 上升沿
    delay5us();
    SDA = 0;// 下降沿(标志位)
    delay5us();
    SCL = 0;
    delay5us();
}
void I2c_Stop(){//结束信号(严格延时)
    SDA = 0;
    delay5us();
    SCL = 1;
    delay5us();
    SDA = 1;// 上升沿(标志位)
    delay5us();
    SDA = 0;// 下降沿
}
bit I2c_Send_Byte(uchar DAT){//写8位(一字节)数据
    uchar i,ask=0;
    for(i=0; i<8; i++){ //写8次，一次写1位，读SDA(锁存)
        SDA = DAT>>7;    //先发送最高位
        DAT <<= 1;        //准备发送下一位
        SCL = 1;        //锁定SDA防止SCL一直为0导致数据错乱
        SCL = 0;        //释放SDA允许下次写入(这两行不能修改)
    }
    SDA = 1;    //释放总线
    delay5us();    //此时SCL=0，准备处理应答>4us
    SCL = 1;    //锁住SDA，处理应答
    while (SDA){
        ask++;
        if (ask>200){//1000us判断始终为1则为非应答
            delay5us();
            SCL = 0;
            return 0;//NO
        }
    }
    SCL = 0;//拉低时钟总线，允许SDA释放
    return 1;//YES
}
uchar I2c_Read_Byte(){
    uchar i, DAT=0;
    SDA = 1;
    for(i=0; i<8; i++){ //分别读8次，每次读一位
        SCL = 1;        //拉高时钟总线，读取SDA上的数据
        DAT <<= 1;      //数据左移1位，准备接收一位
        DAT |= SDA;        //为1则写1，否则不行执行写1，通过左移补0
        SCL = 0;
    }
    return(DAT); //返回读出的数据
}
void At24c02Write(uchar ADDR ,uchar DAT){
    I2c_Start();//I2C起始信号
    I2c_Send_Byte(At24c02_address + I2c_Write);//发送器件地址加读写方向位
    I2c_Send_Byte(ADDR);//发送储存单元地址字节
    I2c_Send_Byte(DAT);//发送一字节数据
    I2c_Stop();    //I2C停止信号
}
uchar At24c02Read(uchar ADDR){
    uchar DAT;
    I2c_Start();//I2C起始信号
    I2c_Send_Byte(At24c02_address + I2c_Write);//发送器件地址加读写方向位
    I2c_Send_Byte(ADDR);//I2C发送一个字节
    I2c_Start();//再次产生I2C起始信号
    I2c_Send_Byte(At24c02_address + I2c_Read);//发送器件地址加读写方向位 读
    DAT = I2c_Read_Byte();//读一字节
    I2c_Stop(); //I2C停止信号
    return(DAT);//返回读出数据
}