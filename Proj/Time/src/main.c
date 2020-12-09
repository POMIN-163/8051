#include "REG51.H"
#define uint unsigned int
#define uchar unsigned char

sbit smg1 = P2^2;
sbit smg2 = P2^3;
sbit smg3 = P2^4;//数码管IO

sbit kA = P3^1;
sbit kB = P3^2;
sbit kC = P3^3;

uint m_sec = 0;//1ms
uchar time[] = {0 , 0 , 12};

uchar code smgz[]=// 显示0~9,H的值
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40};

void delay(uint s)
{
    while(s--);
}
void Time0_Init()
{
    TMOD|=0x01;
    TH0 = (65536 - 1000) >> 8;
    TL0 = (char)(65536 - 1000);//1ms
    ET0=1;
    TR0=1;
    EA=1;
}
void display(bit a, bit b, bit c){
    uchar i;
    char smg[8]={-1,-1,-1,-1,-1,-1,-1,-1,};
    if(a) {
        smg[0] = smgz[(time[0])%10];
        smg[1] = smgz[(time[0])/10];
    }
    if(b){
        smg[3] = smgz[(time[1])%10];
        smg[4] = smgz[(time[1])/10];
    }
    if(c){
        smg[6] = smgz[(time[2])%10];
        smg[7] = smgz[(time[2])/10];
    }
    if(a&&b&&c){
        smg[2] = smgz[10];
        smg[5] = smgz[10];
    }
    for (i = 0; i < 8; i++){
        smg1=((i)&0x01);
        smg2=((i>>1)&0x01);
        smg3=((i>>2)&0x01);
        if (smg[i]==-1)
            P0 = 0x00;
        else
            P0 = smg[i];
        delay(100);
        P0 = 0x00;
    }
}
uchar key_A(){
    if (kA == 0)
    {
        TR0 = 0;
        delay(100);
        if (kA == 0){
            while (!kA);
            return 1;
        }
    }
    return 0;
}
uchar key_Change(){
    if (kB == 0)//+
    {
        delay(100);
        if (kB == 0){
            while (!kB);
            return 2;
        }
    }
    if (kC == 0)//-
    {
        delay(100);
        if (kC == 0){
            while (!kC);
            return 0;
        }
    }
    return 1;
}
void time_Change(uchar log,uchar change,uchar max){
    if(time[3-log] == 0&&change == 0)
        time[3-log] = max;//下界
    else if(time[3-log] == max&&change == 2){
        time[3-log] = 0;//上界
    }else{
        time[3-log] += -1 + change;
    }
}
void main(){
    uchar log;
    Time0_Init();
    while (1)
    {
    log += key_A();// 改写模式标志位
    if(!log){
        display(1, 1, 1);
    }else{
        switch (log) {
            case 1 :
                time_Change(log, key_Change(), 23);
                display(0, 0, 1);
                break;
            case 2 :
                time_Change(log, key_Change(), 59);
                display(0, 1, 0);
                break;
            case 3 :
                time_Change(log, key_Change(), 59);
                display(1, 0, 0);
                break;
            default:
                log =0;
                Time0_Init();
                display(1, 1, 1);
                break;
        }
    }
    }
}
void Time0 () interrupt 1
{
    m_sec++;
    TH0 = (65536 - 1000) >> 8;
    TL0 = (char)(65536 - 1000);//1ms
    if (m_sec == 200)//200ms到一秒
    {
        m_sec = 0;
        time[0]++;
    }
    if (time[0] == 60)
    {
        time[1]++;
        time[0] = 0;
    }
    if (time[1] == 60)
    {
        time[2]++;
        time[1] = 0;
    }
    if (time[2] == 24)//24小时制
    {
        time[2] = 0;
    }
}