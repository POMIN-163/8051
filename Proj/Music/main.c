#include <reg52.h>           // 调取头文件
#define SONG 4               // 歌曲的数量
#define uint  unsigned int   // 以后unsigned int 就可以用uint 代替
#define uchar unsigned char  // 以后unsigned char就可以用uchar代替
#define ulong unsigned long  // 以后unsigned long就可以用ulong代替
sbit neizhi  = P1^0;         // 播放内置
sbit qingchu = P1^1;         // 清除录制
sbit tanzhou = P1^2;         // 播放录制
sbit speaker = P1^4;         // 扬声器
sbit Do  = P3^0;             // Do
sbit Re  = P3^1;             // Re
sbit Mi  = P3^2;             // Mi
sbit Fa  = P3^3;             // Fa
sbit So  = P3^4;             // So
sbit La  = P3^5;             // La
sbit Si  = P3^6;             // Si
sbit Do_ = P3^7;             // Do_
uchar luzhi = 0;             // 一直进行录制状态
uchar TheTone = 0;           // 代表当前要播放的音调
uchar nSong;                 // 代表当前播放到第几首歌
uchar zhuangtai;             // 代表当前的播放状态，0是停止，1是播放
///////////////////////////////////////////////////////////////////////
//  定时器初值            低1  低2  低3  低4  低5  低6  低7  中1  中2  中3  中4  中5  中6  中7  高1  高2  高3  高4  高5  高6  高7     升4    升5
uchar code  ArrTL0[] = { 140,  91,  21, 103,   4, 144,  12,  68, 121, 220,  52, 130, 200,   6,  34,  86, 133, 154, 193, 228,   3 ,185,75};
uchar code  ArrTH0[] = { 248, 249, 250, 250, 251, 251, 252, 252, 252, 252, 253, 253, 253, 254, 254, 254, 254, 254, 254, 254, 255 ,251,251};
//                        0    1    2    3     4   5    6     7       8   9      10   11   12   13   14   15   16   17   18   19   20    21    22
//《天空之城》的乐谱
uchar code Music3[] = {
    12,2,13,2,14,6,13,2,14,4,16,4,
    13,16,9,2,9,2,12,6,11,2,12,4,
    14,4,11,16,9,4,10,6,9,2,10,4,14,4,9,8};
//《茉莉花》的乐谱
uchar code Music1[] = {
    9,4,  9,2,  11,2, 12,2, 14,2, 14,2, 12,2,
    11,4, 11,2, 12,2, 11,8, 9,4,  9,2,  11,2,
    12,2, 14,2, 14,2, 12,2, 11,4, 11,2, 12,2,
    11,8, 11,4, 11,4, 11,4, 9,2,  11,2, 12,4,
    12,4, 11,8};
//《欢乐颂》的乐谱
uchar code Music2[] = {
    9,2,  9,2,  10,2, 11,2,
    11,2, 10,2, 9,2,  8,2,
    7,2,  7,2,  8,2,  9,2,
    9,3,  8,1,  8,4,  9,2,
    9,2,  10,2, 11,2, 11,2,
    10,2, 9,2,  8,2,  7,2,
    7,2,  8,2,  9,2,  8,3,
    7,1,  7,4,  8,2,  8,2,
    9,2,  7,2,  8,2,  9,1,
    10,1, 9,2,  7,2,  8,2,
    9,1,  10,1, 9,2};
//《水手》的乐谱
uchar code Music4[] = {
    5,4,  9,2,  8,2,  9,4, 8,2,  9,2,
    10,3, 11,1, 10,2, 8,2, 9,8,  9,1,
    10,2, 10,1, 9,1,  8,2, 7,1,  7,1,
    8,2,  7,1,  7,1,  8,2, 9,2,  7,2,
    6,2,  5,2,  7,2,  6,8, 5,4,  9,2,
    8,2,  9,4,  8,2,  9,2, 10,2, 10,1,
    11,1, 9,2};
//《挥着翅膀的女孩》的乐谱
uchar code Music5[] = {
    9,4,  9,2,  10,2, 11,4, 7,2,  8,2,
    9,2,  9,2,  9,2,  10,2, 11,4, 8,2,
    9,2,  10,4, 10,2, 9,2,  7,4,  10,2,
    9,2,  10,4, 5,2,  7,2,  8,4,  7,2,
    8,2,  9,4,  9,2,  10,2, 11,4, 12,2,
    13,2, 14,2, 14,2, 9,2};
////////////////////////////////////////////////////////////////////////
// 延时函数延时1ms左右
void delay(uint time)
{
    uint i,j;
    for(i=0;i<time;i++)
        for(j=0;j<112;j++);
}
// 发出指定音调及其节拍的声音，tone代表音调，beat代表节拍
void PlayTone(uchar tone,float beat)
{
    int i;                        // 局部循环变量
    TheTone=tone;                 // 将音调值赋给全局变量TheTone
    TH0 = ArrTH0[tone];           // 装入定时器TH0的初值
    TL0 = ArrTL0[tone];           // 装入定时器TL0的初值
    TR0=1;                        // 启动定时器
    for(i=0;i<beat;i++)           // 节拍
    {
        delay(200);               // 延时
    }
    TR0=0;                        // 停止定时器
    speaker=1;                    // 关闭扬声器
}
// 播放内置的音乐
// music[]是要播放的乐谱数组，num是数组里面的元素个数
void PlayMusic(uchar music[],uint num)
{                                          ////此段运用比较进度与总长度来播放内置
    uint i=0;                              // 定义一个变量
    while(i<num)                           // 循环函数，运用下面的sizeof来判断音节数
    {
        if(zhuangtai==1)                   // 判断播放状态是否为播放还是暂停
        {
            PlayTone(music[i],music[i+1]); // 开始演奏一个节拍
            i+=2;                          // 进入下一个节拍，因为每2个数为1组，所以每次要加2
            if(i==num)                     // 判断歌曲是否播放完了
            {
                zhuangtai=0;               // 播放完了的话，则把播放状态改为暂停，否则会循环播放
            }                              ////此段运用比较进度与总长度来播放内置
        }
        if(neizhi==0)                      // 下一曲
        {
            delay(10);                     // 消除按键按下的抖动
            while(!neizhi);                // 等待按键释放
            delay(10);                     // 消除按键松开的抖动
            nSong++;                       // 把当前播放到第几首歌的变量nSong加1，即切到下一曲
            if(nSong>SONG)                 // 如果nSong为SONG，说明到后面的尽头了，则转为第一首
                nSong=0;
    break;
        }
    }
}
// 定时器初始化函数
void TimerInit()
{
    TMOD=1;           // 定时器0，工作方式1
    TH0=0;            // 装定时器TH0的初值
    TL0=0;            // 装定时器TL0的初值
    ET0=1;            // 开启定时器0中断
    EA=1;             // 开启总中断
}
// 弹奏键扫描函数
uchar KeyScanf()
{
    if(Do==0)
        return 1;
    if(Re==0)
        return 2;
    if(Mi==0)
        return 3;
    if(Fa==0)
        return 4;
    if(So==0)
        return 5;
    if(La==0)
        return 6;
    if(Si==0)
        return 7;
    if(Do_==0)
        return 8;
    return 0;      // 8个按键都没被按下，返回0
}
// 主函数
void main()
{
    uchar i;                      // 循环变量
    uchar ret;                    // 用于保存音调键函数的返回值
    uchar count;                  // 用于记录当前录制了多少个音调
    uchar record[100]={0};        // 存储录制歌曲的数组
    TimerInit();                  // 定时器初始化
    nSong=0;                      // 上电默认准备第一首歌
    zhuangtai=0;                  // 上电默认是0停止状态（1为播放状态）
    PlayTone(8,4);
    while(1)
    {
        if(zhuangtai==1)          // 如果处于播放状态，则判断是哪一首歌曲需要播放
        {
            switch(nSong)         // 选择歌曲播放
            {
                case 1 : PlayMusic(Music1,sizeof(Music1)); break;
                case 2 : PlayMusic(Music2,sizeof(Music2)); break;
                case 3 : PlayMusic(Music3,sizeof(Music3)); break;
                case 4 : PlayMusic(Music4,sizeof(Music4)); break;
                default:                                       break;
            }
        }
        //播放内置的音乐
        if(neizhi==0)                 // 开始播放
        {
            delay(10);                // 消除按键按下的抖动
            while(!neizhi);           // 等待按键释放
            delay(10);                // 消除按键松开的抖动
            nSong++;                  // 把当前播放到第几首歌的变量nSong加1，即切到下一曲
            if(nSong>SONG)            // 如果nSong为SONG，说明到后面的尽头了，则转为暂停
            {nSong=0;}
            zhuangtai=1;              // 播放状态改为1，即播放
        }
        //清零按键的处理
        if(qingchu==0)
        {
            count=0;                  // 清零记录按键值计数，从新开始计数
            delay(10);                // 消除按键按下的抖动
            while(!qingchu);          // 等待按键释放
            delay(10);                // 消除按键松开的抖动
        }
        //播放录制的音乐
        if(tanzhou==0)
        {
            for(i=0;i<count;i++)
            {
                if(i<11||i==12||i==13||i==20||i==19||i==25||i==26||i==27||i==28||i==30||i==31){PlayTone(record[i],2);}
                if(i==11||i==14||i==29||i==32){PlayTone(record[i],1.6);}    // 播放该音调
                if(i==15||i==16||i==17||i==18||i==21||i==22||i==23||i==24){PlayTone(record[i],1.6);}
                if(i>32){PlayTone(record[i],2);}

            }
            delay(10);                      // 消除按键按下的抖动
            while(!tanzhou);                // 等待按键释放
            delay(10);                      // 消除按键松开的抖动
        }
        //8个弹奏按键的扫描
        ret=KeyScanf();                     // 获取8个按键的扫描结果
        if(ret!=0)                          // 如果有按键按下去了
        {
            TH0 = ArrTH0[ret+6];            // 装入定时器TH0的初值
            TL0 = ArrTL0[ret+6];            // 装入定时器TL0的初值
            TheTone=ret+6;
            if(luzhi==0)                    // 如果是录音状态，则把弹奏值记录下来
            {
                record[count]=TheTone;      // 记录当前弹奏的按键值
                count++;                    // 准备记录下一个
            }
            TR0=1;                          // 启动定时器，播放弹奏的音符
            delay(20);                      // 去除按键按下的抖动
            while(KeyScanf());              // 等待按键释放
            delay(70);                      // 按键释放之后，再播放70毫秒，达到余音的效果
            TR0=0;                          // 停止定时器
            speaker=1;                      // 关闭定时器，停止弹奏音符的播放
        }
    }
}
// 定时器0中断处理函数
void time0() interrupt 1
{
    speaker=!speaker;           // 将控制扬声器的管脚取反
    TH0=ArrTH0[TheTone];        // 重装定时器TH0的初值
    TL0=ArrTL0[TheTone];        // 重装定时器TL0的初值
}