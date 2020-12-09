#include <reg52.h>

#define uchar unsigned char
#define uint unsigned int
uint KEY = 1234;

sbit KEY1 = P3 ^ 2; // 按键1
sbit KEY2 = P3 ^ 3; // 按键2
sbit PWM_OUT = P2 ^ 0; // PWM输出口

sbit smg1=P2^2;
sbit smg2=P2^3;
sbit smg3=P2^4;// 数码管IO

uchar code smgz[]={//显示0~F的值
    0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
    0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};   

uint PWM_Value; // 定义pwm值
uchar order = 0;
uchar flag; // 舵机按键标志
uint log = 0;
uchar rec;
uint KEY_user;
//---- 延时函数 ----//
void delay(unsigned int s)
{
    while(s--);
}
void PORT_START()
{
    TMOD = 0x20;
    PCON = 0x80;
    SCON = 0x50;
    TH1 = 0xf9;
    TL1 = 0xf9;
    ES = 1;
    EA = 1;
    TR1 = 1;
}

void port() interrupt 4
{

    RI = 0;
    rec = SBUF;
    SBUF = rec + 0x01;
    rec -= 0x80;

    while (!TI);
    TI = 0;
}

//---- 定时器初始化 ----//
void Init_Timer0()
{
    TMOD |= 0x01;
    TH0 = (65536 - 1500) / 256;
    TL0 = (65536 - 1500) % 256;
		EA = 1;
    ET0 = 1;
    TR0 = 1;
}
void display(uint rec){// 数码管4位16进制最高65535
    uchar i;
        char smg[8]={-1,-1,-1,-1,-1,-1,-1,-1,};
            smg[0] = smgz[(rec)%16];
            smg[1] = smgz[(rec/16)%16];
            smg[2] = smgz[(rec/256)%16];
            smg[3] = smgz[(rec/4096)%16];

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
uchar KeyDown(void)
{
	char a=0,KeyValue = 0;
	P1=0x0f;

	if(P1!=0x0f)//有按键按下
	{
		delay(1000);//延时10ms去抖
		if(P1!=0x0f)//有按键按下
		{	
			
			P1=0X0F;
			switch(P1)
			{
				case(0X07):	KeyValue=1;break;
				case(0X0b):	KeyValue=2;break;
				case(0X0d): KeyValue=3;break;
				case(0X0e):	KeyValue=4;break;
			}
			
			P1=0XF0;
			switch(P1)
			{
				case(0X70):	KeyValue=KeyValue;break;
				case(0Xb0):	KeyValue=KeyValue+4;break;
				case(0Xd0): KeyValue=KeyValue+8;break;
				case(0Xe0):	KeyValue=KeyValue+12;break;
			}
			while((a<50)&&(P1!=0xf0))	 
			{
				delay(1000);
				a++;
			}
			 
		}
	}
	else
	{
		KeyValue=0xff;  //无按键按下
		return KeyValue;  
	}
	
	return 17 - KeyValue;  //返回KeyValue
}
//---- 主函数 ----//
void main(void)
{
		uchar temp, KEY_bit = 0, KEY_value = 0;
    PWM_Value = 2000; // pwm初值为1500
		PORT_START();
    Init_Timer0();
		rec = 0;
    while (1) {
			temp = KeyDown();
			if(temp == 16){
					KEY_user = 0;KEY_bit = 0;flag = 1;
			}
			else if(temp != 0xff && KEY_bit < 4){
					KEY_value = temp;
					KEY_user = KEY_user*16 + KEY_value;
					KEY_bit++;
			}
			if(KEY_bit == 4 && temp == 13){
				if(KEY_user == 0x1234){
					flag = 2;
					KEY_user = 0;KEY_bit = 0;
				}
				else{
					KEY_user = 0;KEY_bit = 0;
				}
			}
			display(KEY_user);
      /*  if ((KEY1 == 0) | (KEY2 == 0)) // 按键1或按键2被按下
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
        switch (rec)
        {
            case 1:flag = 1; rec = 0;break;
            case 2:flag = 2; rec = 0;break;
            default:
                break;
        }

	}
}
//---- 中断程序 ----//
void timer0(void) interrupt 1
{
    if (flag == 1)
        PWM_Value += 10;     // 如果标志位1时，pwm的值加1
    if (flag == 2)          // 如果标志位为2时，pwm减1
        PWM_Value -= 10;
    if (PWM_Value >= 2500) { // 如果pwm的值大于2500则保持在2500(上限2.5ms)
        PWM_Value = 2500;flag = 0;}
    if (PWM_Value <= 500) {   // 如果pwm的值小于500则保持在500(下限0.5ms)
        PWM_Value = 500; flag = 0;}
    switch (order)
    {
        case 1:
            PWM_OUT = 1;
            TH0 = (65536 - PWM_Value) >> 8;// PWM_Value单位为微秒
            TL0 = (char)(65536 - PWM_Value);
            break;
        case 2:
            PWM_OUT = 0;
            TH0 = (65536 - (5000 - PWM_Value)) >> 8;// 5ms中的剩余
            TL0 = (char)(65536 - (5000 - PWM_Value));
            break;
        case 3:
            TH0 = (65536 - 10000) >> 8;// 10ms
            TL0 = (char)50536;
            order = 0;
            break;
    }
    order++;
}
