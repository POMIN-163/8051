#include "reg52.h"			 //���ļ��ж����˵�Ƭ����һЩ���⹦�ܼĴ���

sbit led=P0^0;   //����Ƭ����P0.0�˿ڶ���Ϊled

void UsartInit()        //���ô���
{
	SCON=0X50;			//����Ϊ������ʽ1
	TMOD=0X20;			//���ü�����������ʽ2
	PCON=0X80;			//�����ʼӱ�
	TH1=0XF4;				//��������ʼֵ���ã�ע�Ⲩ������4800��
	TL1=0XF4;
	ES=1;						//�򿪽����ж�
	EA=1;						//�����ж�
	TR1=1;					//�򿪼�����
}

void main()
{	
	UsartInit();  //	���ڳ�ʼ��
	while(1);		
}

void Usart() interrupt 4	//�����жϷ�����
{
	char receiveData;

	receiveData=SBUF;//��ȥ���յ������ݣ���ʱSBUF��Ž�������
	RI = 0;//��������жϱ�־λ
	if(receiveData=='1') 
	{
		led=1;			 //����1ʱ����LED��
	}
	if(receiveData=='0') 
	{
		led=0;			 //����0ʱ���ر�LED��
	}
    SBUF=receiveData;
	while(!TI);			 //�ȴ������������
	TI=0;						 //���������ɱ�־λ
}
