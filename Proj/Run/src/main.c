#include "REG51.H"
#define uint unsigned int
#define uchar unsigned char
sbit k1 = P3^1;
sbit k2 = P3^0;
sbit k3 = P3^2;
sbit k4 = P3^3;

sbit smg1 = P2^2;
sbit smg2 = P2^3;
sbit smg3 = P2^4;//数码管IO

uchar code smgz[] = {
	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
	//显示0~F的值

uchar code mode[3][8] = {
    {0x01, 0x02, 0x04, 0x08, 0x01, 0x02, 0x04, 0x08},
    {0x03, 0x06, 0x0c, 0x09, 0x03, 0x06, 0x0c, 0x09},
    {0x01, 0x03, 0x02, 0x06, 0x04, 0x0c, 0x08, 0x09}
};
// 延时函数
void delay(uint a){
    while (a--);
}

void delay_ms(uint a)
{
    uchar b;
    for(b = 199;b>0;b--)
        for(;a>0;a--);
}

// 数码管显示
void display(uchar mod,uint rec,bit dir){
    uchar i;
    char smg[8] = {-1,-1,-1,-1,-1,-1,-1,-1};
        smg[0] = smgz[rec%10];
        smg[1] = smgz[(rec/10)%10];
        smg[2] = smgz[(rec/100)%10];
        smg[4] = smgz[mod];
        smg[6] = smgz[dir];
    for (i = 0; i < 8; i++) {
    	smg1 = ((i)&0x01);
		smg2 = ((i>>1)&0x01);
		smg3 = ((i>>2)&0x01);
        if (smg[i] == -1)
            P0  = 0x00;
        else
            P0  = smg[i];//段码///这三行不可更改否则可能重影
		delay(100);				//延时
		P0 = 0x00;				//消隐
    }
}

//启动步进电机，1为顺时针0为逆时针
void motor_Run(uchar mod, uint speed, bit dir){
    uchar i;
    if(mod > 3||mod == 0)
        return;
    if(speed >=  1000)
        return;
    if(dir){
        for ( i = 0; i < 8; i++)
        {
            P1 = mode[mod - 1][i];
            delay_ms(1000 - speed);
        }
    }
    else{
        for ( i = 0; i < 8; i++)
        {
            P1 = mode[mod - 1][7 - i];
            delay_ms(1000 - speed);
        }
    }
}
uchar Keyscan(){
    if(k1 == 0){delay(10);if(k1 == 0){delay(10);}while(!k1);return 1;}
    if(k2 == 0){delay(10);if(k2 == 0){delay(10);}while(!k2);return 2;}
    if(k3 == 0){delay(10);if(k3 == 0){delay(10);}while(!k3);return 3;}
    if(k4 == 0){delay(10);if(k4 == 0){delay(10);}while(!k4);return 4;}
    return 0;
}

void main(){
    uchar mod = 3, cmd;
    uint speed = 990;
    bit dir;
    while(1){
        cmd = Keyscan();
        switch (cmd)//类似命令集的操作
        {
        case 1:
            mod++;
            if(mod > 3)
                mod = 1;
            break;
        case 2:
            if(speed < 990)
                speed +=  90;
            break;
        case 3:
            if(speed > 0)
                speed -=  90;
            break;
        case 4:
            dir = ~dir;
            break;
        default:
            break;
        }
        cmd = 0;
        motor_Run(mod, speed, dir);
        display(mod,speed,dir);
    }
}