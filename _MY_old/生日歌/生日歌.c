#include<reg52.h>
#include<intrins.h>

#define uchar unsigned char 
#define uint unsigned int

sbit SPK = P2^5;

uchar tone_h;                //����
uchar tone_l;                //����
uint note = 1;                //����
uchar beat;                        //����


uchar code chuzhi[3][16]={  //������Ӧ�ļ�����ֵ
         0xff,0xff,//ռ0λ 
         0xf8,0x8c,//��1  
         0xf9,0x5b,//  2                 
         0xfa,0x15,//  3                 
         0xfa,0x67,//  4                 
         0xfb,0x04,//  5                 
         0xfb,0x90,//  6                 
         0xfc,0x0c,//��7
        
         0xff,0xff,//ռ0λ 
         0xfc,0x44,//��1   
         0xfc,0xac,//  2
         0xfd,0x09,//  3
         0xfd,0x34,//  4
         0xfd,0x82,//  5
         0xfd,0xc8,//  6
         0xfe,0x06,//��7   
        
         0xff,0xff,//ռ0λ 
         0xfe,0x22,//��1                           
         0xfe,0x56,//        2                
         0xfe,0x85,//        3                
         0xfe,0x9a,//        4                
         0xfe,0xc1,//        5                
         0xfe,0xe4,//        6                
         0xff,0x03 //��7                             
        };        

//****** �������� ****** ��λ������ ��ʮλ�����и��� ��Ӧ 0 1 2��ǧ��λ������ 1~16
uint code test2[] = {        120, //���� ��ʱδ�õ�
        401,402,403,404,405,406,407,
        611,612,613,614,615,616,617,
        821,822,823,824,825,826,827,
        0xffff        //0xffff��ʾ��β
};

//****** ���տ��� ******
uint code test[] = { 120,
        205,205,406,405,411,807,
        205,205,406,405,412,811,
        205,205,415,413,411,407,406,
        314,114,413,411,413,812,
        305,105,406,405,411,807,
        305,105,406,405,412,811,
        305,105,415,413,411,
        407,406,314,114,413,411,412,811,410,
        0xffff        
};

        
void delayms(uint ms)          /*ms ����1ʱ����ʱ1ms ����2ʱ����ʱ2ms���Դ�����*/
{        
        uchar a,b,c;                                   //+3
        while(ms--)
    {
         for(c=1;c>0;c--)                        //         1+2 = 3
        for(b=142;b>0;b--)                  //        1*( 1+142*2)) = 285        
            for(a=2;a>0;a--);        //         142*(1+2*2) = 710
        }
}

void delay125ms(uint pai)  //��ʱ ��*125ms ���������� 
{
    uchar a,b,c;
        while(pai--)
        {
        for(c=239;c>0;c--)
                for(b=104;b>0;b--)
                        for(a=1;a>0;a--);
        }
}
void timer0() interrupt 1
{
        TH0 = tone_h;
        TL0 = tone_l;
        SPK = ~SPK;
}


void timer_init()
{
        EA = 1;
        ET0 = 1;
        PT0 = 1;
        TMOD = 0x11;
        TH0 = 255;
        TL0 = 255;
}
void main()
{        
        timer_init();
        note = 1;
        
        while(1)
        {        
                if(test[note] == 0xffff)
                {        
                        note = 1;
                }                
                if(test[note]%10 != 0)        //������Ϊ0 ������Ϊ0ʱ��ʾ�����������н��ġ�
                {
                        tone_h = TH0 = chuzhi[test[note]%100/10][(test[note]%10)*2 ];                //������λ ����ά���� ��1ά��ʾ���и������ڶ�ά��ʾ������
                        tone_l = TL0 = chuzhi[test[note]%100/10][(test[note]%10)*2 + 1];        //������λ
                        TR0 = 1;
                }
                delay125ms(test[note]/100);        //����
                TR0 = 0;
                delayms(30);
                note++;                                                //��һ������
                
        }
        
}
 