#include <reg51.h>   
#include <jichu.h>
void BEEP()						//��һ��
{
	uchar i;
	for(i=0;i<240;i++)
	{
		beep=~beep;
		delay(1);
	}
	delay(2000);
}
