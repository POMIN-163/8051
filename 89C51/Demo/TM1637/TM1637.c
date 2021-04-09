#include <reg52.h>
#include<intrins.h>

sbit CLK = P0^0;  //ʱ���ź�
sbit DIO = P0^1;  //����/��ַ����
                     //�����������
unsigned char code SEGData[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//1-9
unsigned char code SEGDataDp[]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef}; //��С����ֻ���ڵ�ַ0xc1

unsigned char dpFlag = 0; //���Ƶڶ�������ܵ�dp����ʾ

void TM1637_start(void);
void TM1637_stop(void);
void TM1637_write1Bit(unsigned char mBit);
void TM1637_write1Byte(unsigned char mByte);
void TM1637_writeCammand(unsigned char mData);
void TM1637_writeData(unsigned char addr, unsigned char mData);
void time_set(char hour, char min);
void time_judge(void);
void time_display(void);
void timer0_init(void);

void delay_140us(void);
void delay_1ms(unsigned int i);

unsigned int countTime = 0;
unsigned char time, sec;
struct {
 char shi;
 char ge;
}Hour;

struct {
 char shi;
 char ge;
}Min;

/***********************************************************
*****
***** ������
*****
***********************************************************/
void main(void)
{
 //timer0_init();
 time_set(4, 0);  //����5Сʱ����ʱ

  time_display();  //��ʾʱ��

}

/********************************************************************
* ���� :voidtime_set(char hour, char min)
* ���� : ����ʱ��
* ���� : char hour, char min
* ��� : ��
**************************************************************/
void time_set(char hour, char min)
{
 if((hour < 0) || (min<0))
 {
  hour = 0;
  min = 0;
 }
 Hour.shi = hour/10;
 Hour.ge = hour%10;
 Min.shi = min/10;
 Min.ge = min%10;  
}

/*************************************************************
* ���� : time_judge(void)
* ���� : �ж�ʱ��仯
* ���� : void
* ��� : ��
**************************************************************/
void time_judge(void)
{
 if(++sec == 60)    //60��
 { 
  sec = 0;
  if((Hour.shi || Hour.ge || Min.shi || Min.ge) && (--Min.ge <= -1))
  {
   Min.ge = 9;
   if((Hour.shi) ||(Hour.ge) && (--Min.shi <= -1))
   {
    Min.shi = 5;
    if(Hour.shi && (--Hour.ge <= -1))
    {
     Hour.ge = 9;
     if(--Hour.shi <= -1)
     {
      Hour.shi = 0; 
     }
    }
    else
    if((!Hour.shi) && (--Hour.ge <= -1))
    {
     Hour.ge = 0;
    }
   }
   else
   if((!Hour.shi) && (!Hour.ge) && (--Min.shi <= -1))
   {
    Min.shi = 0;
   }
  }
  else
  if(((!Hour.shi) && (!Hour.ge) && (!Min.shi) ) && (Min.ge <= -1))
  {
   Min.ge = 0;
  }
 } 
}

/********************************************************************
* ���� :voidtime_display(void)
* ���� : ��ʾʱ��
* ���� : void
* ��� : ��
**************************************************************/
void time_display(void)
{
 TM1637_writeCammand(0x44);
 TM1637_writeData(0xc0, SEGData[Hour.shi]);
 if(dpFlag)
  TM1637_writeData(0xc1, SEGDataDp[Hour.ge]); //С�����־Ϊ1����С�����Ǹ�����
 else
  TM1637_writeData(0xc1, SEGData[Hour.ge]);
 TM1637_writeData(0xc2, SEGData[Min.shi]);
 TM1637_writeData(0xc3, SEGData[Min.ge]);
 TM1637_writeCammand(0x8a);    
}

/********************************************************************
* ���� :voidTM1637_start(void)
* ���� : start�ź�
* ���� : void
* ��� : ��
**************************************************************/
void TM1637_start(void)
{
 CLK = 1;
 DIO = 1;
 delay_140us();
 DIO = 0;
 delay_140us();
 CLK = 0;
 delay_140us();
}

/********************************************************************
* ���� :voidTM1637_stop(void)
* ���� : stop�ź�
* ���� : void
* ��� : ��
**************************************************************/
void TM1637_stop(void)
{
 CLK = 0;
 delay_140us();
 DIO = 0;
 delay_140us();
 CLK = 1;
 delay_140us();
 DIO = 1;
 delay_140us();
}

/********************************************************************
* ���� :voidTM1637_write1Bit(unsigned char mBit )
* ���� : д1bit
* ���� : unsigned char mBit
* ��� : ��
**************************************************************/
void TM1637_write1Bit(unsigned char mBit )
{
 CLK = 0;
 delay_140us();
 if(mBit)
  DIO = 1;
 else
  DIO = 0;
 delay_140us(); 
 CLK = 1;
 delay_140us();
}

/********************************************************************
* ���� :voidTM1637_write1Byte(unsigned char mByte)
* ���� : д1byte
* ���� : unsigned char mByte
* ��� : ��
**************************************************************/
void TM1637_write1Byte(unsigned char mByte)
{
 char loop = 0;
 for(loop = 0; loop < 8; loop++)
 {
  TM1637_write1Bit((mByte>>loop)&0x01); //ȡ�����λ 
 }
 CLK = 0;
 delay_140us();
 DIO = 1;
 delay_140us();
 CLK = 1;
 delay_140us();
 while(DIO == 1);  //���Ӧ��λ 
}

/********************************************************************
* ���� :voidTM1637_writeCammand(unsigned char mData)
* ���� : дָ��1byte
* ���� : unsigned char mData
* ��� : ��
**************************************************************/
void TM1637_writeCammand(unsigned char mData)
{
 TM1637_start();
 TM1637_write1Byte(mData);  //����
 TM1637_stop(); 
}

/********************************************************************
* ���� :voidTM1637_writeData(unsigned char addr, unsigned char mData)
* ���� : �̶���ַд����1byte
* ���� : unsigned char addr, unsigned char mData
* ��� : ��
**************************************************************/
void TM1637_writeData(unsigned char addr, unsigned char mData)
{
 TM1637_start();
 TM1637_write1Byte(addr);  //��ַ
 TM1637_write1Byte(mData);  //����
 TM1637_stop(); 
}

/********************************************************************
* ���� :voidtimer0_init()
* ���� : ��ʱ50ms��ʵ������������ָ��������ɵ���ʱ��ʵ��ʱ��϶�����50ms
* ���� : ��
* ��� : ��
**************************************************************/
void timer0_init(void)
{
 TMOD=0X01;
 TH0=(65535-50000)/256;
 TL0=(65535-50000)%256;
 ET0=1;
 EA=1;
 TR0=1; 
}      


void timer0_isr() interrupt 1
{
 TH0=(65535-50000)/256;  //50ms
 TL0=(65535-50000)%256; //
 countTime++;
}

void delay_140us(void)
{
    int i;
    for(i=0; i<20; i++)
      _nop_();
}

