#include<reg51.h>
#include"intrins.h"
typedef unsigned char u8;
typedef unsigned int u16;

#define led P2
void delay(u16 i)
{
while(i--);
}
void main()
{
u8 i=0;
led=0xfe;
delay(50000);
while(1)
{
for(i=0;i<7;i++)
{
led=_crol_(led,1);
delay(50000);
}
for(i=0;i<999;i++)
{
led=_cror_(led,1);
delay(50000);
}
led=0;
delay(50000);
led=1;
delay(50000);
}
}
