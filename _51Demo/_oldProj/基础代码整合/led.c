#include <reg51.h>   	//51��Ƭ��ͷ�ļ�
#include <intrins.h>	//�����ƺ�����ͷ�ļ�
#include <jichu.h>
void LED()			//��ȫ��
{
	led=0x00;			//8λ���룬ʹ"0"��"1"��
	delay(2000);
	led=0xff;			//ȫ��
}
void LED1()			//��ˮ�ƺ���
{
	uchar i,j,k;
	P2=~0x00;
	for(j=0;j<1;j++)
	{
	for(i=0;i<8;i++)		//����8��
		{
			P2=~(0x01<<i);	//��1����iλ��Ȼ�󽫽����ֵ��P2��
			delay(100);
		}	
	if(i==8)
	{
		for(k=0;k<8;k++)	//����8��
		{
			P2=~(0x80>>k);	//��1����kλ��Ȼ�󽫽����ֵ��P2��
			delay(100); 
		}
		i=9;							//��������
	}
	}
		delay(2000);
}
//��һ����λ����
/*		for(i=0;i<7;i++)	 //��led����һλ
		{
			led=_crol_(led,1);
			delay(100); 
		}
		for(i=0;i<7;i++)	//��led����һλ
		{
			led=_cror_(led,1);
			delay(100); 
		}
*/
