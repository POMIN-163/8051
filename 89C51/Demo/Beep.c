#include <reg51.h>

sbit beep = P2 ^ 5;

//延迟函数10us左右
void delay(unsigned int x){
    while(x--);
}

void BEEP_OUT()
{
    beep = ~beep;
    delay(100);
}

void main()
{
    while (1)
        BEEP_OUT();
}