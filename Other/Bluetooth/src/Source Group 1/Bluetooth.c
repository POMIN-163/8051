#include "REG51.H"
#define uint unsigned int
#define uchar unsigned char
sbit k3 = P3 ^ 2;
sbit k4 = P3 ^ 3;

sbit led1 = P2 ^ 1;
sbit led2 = P2 ^ 2;
sbit led3 = P2 ^ 3;
sbit beep = P2 ^ 5;

uchar rec;

void PORT_START()
{
    TMOD = 0x20;
    PCON = 0x80;
    SCON = 0x50;
    TH1 = 0xf3;
    TL1 = 0xf3;
    TR1 = 1;
    ES = 1;
    EA = 1;
}

void port() interrupt 4
{
    rec = SBUF;
    RI = 0;
    SBUF = rec + 0x01;
    while (!TI)
        ;
    TI = 0;
}
void main()
{
    PORT_START();
    while (1)
    {
        if (rec % 2)
        {
            P2 = 0x00;
        }
        else
        {
            P2 = 0xff;
        }
    }
}