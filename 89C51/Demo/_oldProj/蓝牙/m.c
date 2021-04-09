#include<reg52.h> 

#define uchar unsigned char 
#define uint unsigned int 
uchar flag,busy; 
uchar a; 
uchar receiveData; 
sbit Relay1=P2^0; 
sbit Relay2=P2^1; 
void SendString(uchar *s); 
void SendData(uchar date); 
void UsartConfiguration();
void main() 
{ 
	Relay1=1; 
	Relay2=1; 
	UsartConfiguration(); 	
	SendString("cdef"); 
while(1) 
{ 
	if(flag==1) 
		{ 
			SendData(a); 
			flag=0; 
			switch(a) 
			{	case 0xcc:Relay1=1;Relay2=1;break; 
				case 0xdd:Relay1=0;Relay2=1;break; 
				case 0xee:Relay1=1;Relay2=0;break; 
				case 0xff:Relay1=0;Relay2=0;break; 
			}
		}
}	
}
void UsartConfiguration() 
{ 
	SCON=0X50;  
	TMOD=0X20; 
	PCON=0X80;  
	TH1=0XF9; 
	TL1=0XF9; 
	ES=1; 
	EA=1; 
	TR1=1; 
} 
void SendString(uchar *s) 
{ 
	while(*s)
		{
			SendData(*s++); 
		} 
} 
void SendData(uchar date) 
	{ 
		while (busy); 
		busy=1; 
		SBUF=date; 
	}
void Usart() interrupt 4 
{ 
	TH1=0XF9; 
	TL1=0XF9; 
	if (RI) 
	{ 
		RI = 0;
		a=SBUF;
		flag=1;
	}
	if(TI)
		{
		TI=0;
		busy=0;
		}
}