#include <reg51.h>  
#include <jichu.h>
void TimerInit0()
{	
	TMOD|=0X01;	//ѡ��Ϊ��ʱ��0ģʽ��
							//������ʽ1������TR0��������
	TH0=0XFC;		//����ʱ������ֵ����ʱ1ms
	TL0=0X18;	
	ET0=1;			//�򿪶�ʱ��0�ж�����
	EA=1;				//�����ж�
	TR0=1;			//�򿪶�ʱ��			
}
void timer0() interrupt 1
{
	static uint i;
	TH0=0XFC;	//����ʱ������ֵ����ʱ1ms
	TL0=0X18;
	i++;
	if(i==1000)
	{
		i=0;
		led=~led;	
	}	
}