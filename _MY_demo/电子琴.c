#include <reg52.h>                        // 调取头文件

#define uint  unsigned int        // 以后unsigned int 就可以用uint 代替
#define uchar unsigned char        // 以后unsigned char就可以用uchar代替
#define ulong unsigned long        // 以后unsigned long就可以用ulong代替

sbit qingchu = P3^2;        // 清除录制
sbit tanzhou = P3^1;        // 播放录制
sbit speaker = P2^5;        // 扬声器

uchar luzhi=0;            //一直进行录制状态
uchar TheTone=0;        // TheTone代表当前要播放的音调,初值为0(暂存)

uchar ret;                // 用于保存音调键函数的返回值

///////////////////////////////////////////////////////////////////////
//  定时器初值         低1  低2  低3  低4  低5  低6  低7  中1  中2  中3  中4  中5  中6  中7  高1  高2  高3  高4  高5  高6  高7     升4    升5
uchar code  ArrTL0[]={ 140,  91,  21, 103,   4, 144,  12,  68, 121, 220,  52, 130, 200,   6,  34,  86, 133, 154, 193, 228,   3 ,185,75};
uchar code  ArrTH0[]={ 248, 249, 250, 250, 251, 251, 252, 252, 252, 252, 253, 253, 253, 254, 254, 254, 254, 254, 254, 254, 255 ,251,251};
//                      0    1    2    3     4   5    6     7       8   9      10   11   12   13   14   15   16   17   18   19   20    21    22
// 延时函数
void delay(uint time)                //延时1ms左右
{
    uint i,j;
    for(i=0;i<time;i++)
        for(j=0;j<112;j++);
}
// 发出指定音调及其节拍的声音，tone代表音调，beat代表节拍
void PlayTone(uchar tone,float beat)
{
    int i;                        // 定义一个变量
    TheTone=tone;                // 将音调值赋给全局变量TheTone
    TH0 = ArrTH0[tone];            // 装入定时器TH0的初值
    TL0 = ArrTL0[tone];            // 装入定时器TL0的初值
    TR0=1;                        // 启动定时器
    for(i=0;i<beat;i++)            // 节拍
    {
        delay(200);                  // 延时
    }
    TR0=0;                        // 停止定时器
    speaker=1;                    // 关闭扬声器
}
// 定时器初始化函数
void TimerInit()
{
    TMOD=1;            // 定时器0，工作方式1
    TH0=0;            // 装定时器TH0的初值
    TL0=0;            // 装定时器TL0的初值
    ET0=1;            // 开启定时器0中断
    EA=1;            // 开启总中断
}
void PORT_START()//串口
{
    TMOD=0x21;  //定时器方式2
    PCON=0x80;  //波特率倍增
    SCON=0x50;  //8位异步收发模式
    TH1=0xf9;   //定时器初值
    TL1=0xf9;   //
    TR1=1;      //启动定时器
    ES=1;       //串口开关
    EA=1;       //总开关
}
// 主函数，程序从这里开始执行
void main()
{
    uchar i;                // 循环变量
    uchar count;            // 用于记录当前录制了多少个音调
    uchar record[100]={0};    // 存储录制歌曲的数组
    TimerInit();            // 定时器初始化
    PORT_START();
    PlayTone(8,4);
    while(1)
    {
        //清零按键的处理
        if(qingchu==0)
        {
            count=0;                      // 清零记录按键值计数，从新开始计数
            delay(10);                    // 消除按键按下的抖动
            while(!qingchu);        // 等待按键释放
            delay(10);                    // 消除按键松开的抖动
        }
        //播放录制的音乐
        if(tanzhou==0)
        {
            for(i=0;i<count;i++)
            {
                {PlayTone(record[i],2);}
            }
            delay(10);                                // 消除按键按下的抖动
            while(!tanzhou);                    // 等待按键释放
            delay(10);                                // 消除按键松开的抖动
        }
        //8个弹奏按键的扫描
        if(ret!=0)                            // 如果有按键按下去了
        {
            /*TH0 = ArrTH0[ret+6];            // 装入定时器TH0的初值
            TL0 = ArrTL0[ret+6];            // 装入定时器TL0的初值
            TheTone=ret+6;
            */record[count]=TheTone;    // 记录当前弹奏的按键值
            count++;                // 准备记录下一个
            delay(200);
            PlayTone(ret,2);
            /*TR0=1;                // 启动定时器，播放弹奏的音符
            delay(20);            // 去除按键按下的抖动
            while (ret==0);*/
            delay(70);        // 按键释放之后，再播放70毫秒，达到余音的效果
            /*TR0=0;            // 停止定时器
            speaker=1;        // 关闭定时器，停止弹奏音符的播放*/
        }
    }
}
// 定时器0中断处理函数
void time0() interrupt 1
{
    speaker=!speaker;            // 将控制扬声器的管脚取反
    TH0=ArrTH0[TheTone];        // 重装定时器TH0的初值
    TL0=ArrTL0[TheTone];        // 重装定时器TL0的初值
}
void port()interrupt 4//串口中断
{
 //发送时发送01,02的字节形式不能用1或2整数形式
    RI=0;           //接收中断标志复位置0
    ret=SBUF;       //读取接收缓存,赋值全局变量以触发事件
    SBUF=ret;       //回复数据
    ret-=0x80;
    while (!TI);    //等待接收完毕
    TI=0;           //复位
}