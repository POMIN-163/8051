#include "REG51.H"

#define uint unsigned int
#define uchar unsigned char
#define u16 uint
#define u8 uchar

#define SPEED 1500

sbit smg1 = P2 ^ 0;
sbit smg2 = P2 ^ 1;
sbit smg3 = P2 ^ 2;

uchar code smgz[] = {
	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40,
};

char G_num = 0;
char G_carry = 0;

void delay(uint s);
void display(char *smg);
void Init_Timer1();

void delay(uint s) {
    while(s--);
}
void display(char *smg) {
    uchar i;
		for (i = 0; i < 8; i++) {
				smg1=((i) & 0x01);
				smg2=((i >> 1) & 0x01);
				smg3=((i >> 2) & 0x01);      
				if (smg[i] == -1)
						P0 = 0x00;
				else
						P0 = smgz[smg[i]];   
				delay(100);
				P0 = 0x00;
		}
}
void Init_Timer1() {
    TMOD |= 0x01 << 4;
    TH1 = (65536 - SPEED) >> 8;
    TL1 = (char)(65536 - SPEED); 
    EA = 1; 
    ET1 = 1;
//    PT1 = 0;
    TR1 = 1;
} 
void main(void) {
  char smg[26] = {-1,-1,-1,-1,-1,-1,-1,-1,1,9,1,0,2,3,1,3,2,5,-1,-1,-1,-1,-1,-1,-1,-1};
	Init_Timer1();
	while(1) {
		display(smg + G_carry);
	}
}
void timer1() interrupt 3
{
    TH1 = (65536 - SPEED) >> 8;
    TL1 = (char)(65536 - SPEED);
    G_num++;
    if (G_num > 120) {G_carry ++; G_num = 0;}
		if(G_carry > 18) G_carry = 0;
}
