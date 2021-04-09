#include "reg52.h"			 //���ļ��ж����˵�Ƭ����һЩ���⹦�ܼĴ���

void UsartInit()        //���ô���
{
	SCON=0X50;			//����Ϊ������ʽ1
	TMOD=0X20;			//���ü�����������ʽ2
	PCON=0X80;			//�����ʼӱ�
	TH1=0XFA;				//��������ʼֵ���ã�ע�Ⲩ������9600��
	TL1=0XFA;
	ES=1;						//�򿪽����ж�
	EA=1;						//�����ж�
	TR1=1;					//�򿪼�����
}


void Usart() interrupt 4	//�����жϷ�����
{
	char receiveData;

	receiveData=SBUF;//��ȥ���յ������ݣ���ʱSBUF��Ž�������
	RI = 0;//��������жϱ�־λ
	if(receiveData=='1') 
	{
		ret=1;			 //����1ʱ����LED��
	}
	if(receiveData=='0') 
	{
		ret=2;			 //����0ʱ���ر�LED��
	}
    SBUF=receiveData;
	while(!TI);			 //�ȴ������������
	TI=0;						 //���������ɱ�־λ
}
