#include <reg51.h>   		//51��Ƭ��ͷ�ļ�
#include <jichu.h>
uchar code smgz1[]={		//��ʾ0~F��ֵ
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,
	0x39,0x5e,0x79,0x71};
void KEY_Z()						//����������
{
	echar key;
	key_jz=0x0f;
	if(key_jz!=0x0f)			//��ȡ�����Ƿ���
	{
		delay1(1000);
		if(key_jz!=0x0f)		//�ٴμ������Ƿ���
		{									
			key_jz=0X0f;			//������
			switch(key_jz)
			{
				case(0X07):	key=0;break;
				case(0X0b):	key=1;break;
				case(0X0d): key=2;break;
				case(0X0e):	key=3;break;
			}		
			key_jz=0Xf0;			//������
			switch(key_jz)
			{
				case(0X70):	key=key;break;
				case(0Xb0):	key=key+4;break;
				case(0Xd0): key=key+8;break;
				case(0Xe0):	key=key+12;break;
			}		
		}
	}											//���Զ�������
	if(k1==0){delay(10);if(k1==0){key=17;}while(!k1);}
	if(k2==0){delay(10);if(k2==0){key=18;}while(!k2);}
	if(k3==0){delay(10);if(k3==0){key=19;}while(!k3);}
	if(k4==0){delay(10);if(k4==0){key=20;}while(!k4);}
}
void order()
{
	echar key;
	KEY_Z();
	if(key==17)						//����ʵ��չʾ
	{
		LED();						
		LED1();
		SMG();
		SMG1();
		BEEP();
		LED_Z();
		key=0;
	}
	if(key<17)
	{
		smg=smgz1[key];	
	}
}