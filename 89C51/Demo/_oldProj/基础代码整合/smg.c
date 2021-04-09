#include <reg51.h>  
#include <jichu.h>
uchar code smgz[]={	0x3f,0x06,0x5b,0x4f,
										0x66,0x6d,0x7d,0x07,
										0x7f,0x6f,0x77,0x7c,
										0x39,0x5e,0x79,0x71};//显示0~F的值
uchar smg_key[]=8;
void SMG()						//数码管全亮
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
void SMG1()						//数码管显示0~7  //OE短接VCC！！
{
	uchar i,j;
	for(j=0;j<200;j++)
	{
	for(i=0;i<8;i++)
	{
		switch(i)	 //位选，选择点亮的数码管，
		{
		  case(0):
				smg1=1;smg2=1;smg3=1;smg=smgz[i]; break;//显示第0位
			case(1):
				smg1=0;smg2=1;smg3=1;smg=smgz[i]; break;//显示第1位
			case(2):
				smg1=1;smg2=0;smg3=1;smg=smgz[i]; break;//显示第2位
			case(3):	
				smg1=0;smg2=0;smg3=1;smg=smgz[i]; break;//显示第3位
			case(4):
				smg1=1;smg2=1;smg3=0;smg=smgz[i]; break;//显示第4位
			case(5):
				smg1=0;smg2=1;smg3=0;smg=smgz[i]; break;//显示第5位
			case(6):
				smg1=1;smg2=0;smg3=0;smg=smgz[i]; break;//显示第6位
			case(7):
				smg1=0;smg2=0;smg3=0;smg=smgz[i]; break;//显示第7位	
		}
		delay(1); 		//间隔一段时间扫描	
		smg=0x00;			//消隐
	}
}
led=0xff;
}
