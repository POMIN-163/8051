#define uint unsigned int		//之后使用uint定义整形
#define uchar unsigned char	//之后使用uchar定义字符型
#define eint extern int			//外部整型变量引用
#define echar extern char		//外部字符型变量引用
#define led P2
#define smg P0
#define led_dz P0
#define key_jz P1
//数码管IO
sbit smg1=P2^2;
sbit smg2=P2^3;
sbit smg3=P2^4;
//蜂鸣器IO
sbit beep=P2^5;
//独立按键IO
sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;
sbit k4=P3^3;
//点阵IO
sbit SRCLK=P3^6;
sbit RCLK=P3^5;	
sbit SER=P3^4;	



void delay(uint x);
void delay1(uint y);
void LED(void);	//函数声明
void LED1(void);

void SMG(void);
void SMG1(void);

void BEEP(void);
void BEEP1(void);

void order(void);

void KEY_Z(void);

void LED_Z(void);
void LED_Byte(uchar dat);
