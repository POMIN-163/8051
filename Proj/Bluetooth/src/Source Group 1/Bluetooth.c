#include "REG51.H"
#define uint unsigned int
#define uchar unsigned char

sbit d1 = P2 ^ 1;
sbit d2 = P2 ^ 2;

uchar rec;

void PORT_START()
{
    TMOD = 0x20;
    PCON = 0x80;
    SCON = 0x50;
    TH1 = 0xf9;
    TL1 = 0xf9;
    TR1 = 1;
    ES = 1;
    EA = 1;
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
void main()
{
    PORT_START();
    rec = 0
    ;
    while (1)
    {
        switch (rec)
        {
            case 1:d1 = ~d1; rec = 0;break;
            // case 2:d1 = 1; rec = 0;break;
            // case 3:led1 = ~led1;rec = 0;break;
            // case 4:led1 = ~led1;rec = 0;break;
            default:
                break;
        }
    }
}