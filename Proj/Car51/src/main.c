#include "reg52.h"
#define uchar unsigned char
#define uint unsigned int
#define u8 uchar
#define u16 uint
#define true 1
#define false 0
#define bool bit

#define Qianjin 0x0a
#define Houtui 0x06
#define Right 0x02
#define Left 0x08

sbit Ir_right = P1 ^ 4;
sbit Ir_middle = P1 ^ 3;
sbit Ir_left = P1 ^ 5;
sbit Motor = P1 ^ 0;

uint PWM_motor = 700;
uint PWM_Value = 10000; // 定义pwm值
uchar PWM_flag = Qianjin;
uchar rec;// 蓝牙

void Init_PORT() {
    TMOD = 0x20;
    PCON = 0x80;
    SCON = 0x50;
    TH1 = 0xf9;
    TL1 = 0xf9;
    ES = 1;
    EA = 1;
    TR1 = 1;
	rec = 0;
}
/*延时函数*/
void delay(unsigned int s) {
    while(s--);
}
/*定时器初始化*/
void Init_Timer0() {
    TMOD |= 0x01;
    TH0 = (65536 - 1500) / 256;
    TL0 = (65536 - 1500) % 256;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}
void Scan(void){
	if(!Ir_middle){
		PWM_flag = Houtui;
		return;
	}
	else if(!Ir_right){
		PWM_flag = Right;
		return;
	}else if(!Ir_left){
		PWM_flag = Left;
		return;
	}PWM_flag = Qianjin;
}
void Switch(void){
	P2 &= 0xf0;
	P2 |= PWM_flag;
}
/*主函数*/
void main(void) {
	Init_PORT();
    Init_Timer0();
    while (1){
        switch (rec) {
            case 1:PWM_flag = Qianjin; rec = 0;break;
            case 2:PWM_flag = Houtui; rec = 0;break;
            case 3:PWM_flag = Right; rec = 0;break;
            case 4:PWM_flag = Left; rec = 0;break;
            default:
                break;
        }
		Scan();
	}
}

/*****中断程序*******/
void timer0(void) interrupt 1
{
	static uchar order = 1;// 分段延时段数
	static bool flag = 0;// 分段延时段数
	if (flag)
		PWM_motor ++;  // 标志位0时，pwm值加1
    else
		PWM_motor --;  // 标志位1时，pwm值减1
    if (PWM_motor >= 2200) {
		PWM_motor = 2200;
		flag = 0;
	}// 上限
    if (PWM_motor <= 700) {
		PWM_motor = 700;
		flag = 1;
	}// 下限
	switch (order) {
		case 1:\
			Switch();
			TH0 = (65536 - PWM_Value) >> 8;// PWM_Value单位为微秒
			TL0 = (char)(65536 - PWM_Value);
			break;
		case 2:\
			P2 &= 0xf0;
			TH0 = (65536 - (15000 - PWM_Value)) >> 8;// 总20ms
			TL0 = (char)(65536 - (15000 - PWM_Value));
			break;
		// 6000
		case 3:\
			Motor = 1;
			TH0 = (65536 - PWM_motor) >> 8;
			TL0 = (char)(65536 - PWM_motor);
		case 4:\
			Motor = 0;
			TH0 = (65536 - (15000 - PWM_motor)) >> 8;// 总20ms
			TL0 = (char)(65536 - (15000 - PWM_motor));
		default:\
			Switch();
			TH0 = (65536 - PWM_Value) >> 8;// PWM_Value单位为微秒
			TL0 = (char)(65536 - PWM_Value);
			order = 0;
			break;
	}
    order++;
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
