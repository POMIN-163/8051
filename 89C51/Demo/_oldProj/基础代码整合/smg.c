#include <reg51.h>  
#include <jichu.h>
uchar code smgz[]={	0x3f,0x06,0x5b,0x4f,
										0x66,0x6d,0x7d,0x07,
										0x7f,0x6f,0x77,0x7c,
										0x39,0x5e,0x79,0x71};//��ʾ0~F��ֵ
uchar smg_key[]=8;
void SMG()						//�����ȫ��
{
	uchar i;
	for(i=0;i<240;i++)
	{
		smg1=0;smg=0xff;
		smg2=0;smg=0xff;
		smg3=0;smg=0xff;
		delay(1);
		smg1=~smg1;smg=0xff;
		smg2=~smg2;smg=0xff;
		smg3=~smg3;smg=0xff;
		delay(1);
		smg1=0;smg=0xff;
		smg2=0;smg=0xff;
		smg3=1;smg=0xff;
		delay(1);
		smg1=~smg1;smg=0xff;
		smg2=~smg2;smg=0xff;
		smg3=~smg3;smg=0xff;
		delay(1);
		smg1=0;smg=0xff;
		smg2=1;smg=0xff;
		smg3=0;smg=0xff;
		delay(1);
		smg1=~smg1;smg=0xff;
		smg2=~smg2;smg=0xff;
		smg3=~smg3;smg=0xff;
		delay(1);
		smg1=1;smg=0xff;
		smg2=0;smg=0xff;
		smg3=0;smg=0xff;
		delay(1);
		smg1=~smg1;smg=0xff;
		smg2=~smg2;smg=0xff;
		smg3=~smg3;smg=0xff;
		delay(1);		
	}
	smg1=1,smg2=1,smg3=1;
	delay(2000);
}
void SMG1()						//�������ʾ0~7  //OE�̽�VCC����
{
	uchar i,j;
	for(j=0;j<200;j++)
	{
	for(i=0;i<8;i++)
	{
		switch(i)	 //λѡ��ѡ�����������ܣ�
		{
		  case(0):
				smg1=1;smg2=1;smg3=1;smg=smgz[i]; break;//��ʾ��0λ
			case(1):
				smg1=0;smg2=1;smg3=1;smg=smgz[i]; break;//��ʾ��1λ
			case(2):
				smg1=1;smg2=0;smg3=1;smg=smgz[i]; break;//��ʾ��2λ
			case(3):	
				smg1=0;smg2=0;smg3=1;smg=smgz[i]; break;//��ʾ��3λ
			case(4):
				smg1=1;smg2=1;smg3=0;smg=smgz[i]; break;//��ʾ��4λ
			case(5):
				smg1=0;smg2=1;smg3=0;smg=smgz[i]; break;//��ʾ��5λ
			case(6):
				smg1=1;smg2=0;smg3=0;smg=smgz[i]; break;//��ʾ��6λ
			case(7):
				smg1=0;smg2=0;smg3=0;smg=smgz[i]; break;//��ʾ��7λ	
		}
		delay(1); 		//���һ��ʱ��ɨ��	
		smg=0x00;			//����
	}
}
led=0xff;
}
