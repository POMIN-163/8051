#include"reg51.h"
typedef unsigned char u8;
typedef unsigned int u16;
sbit led1=P2^0;
sbit led2=P2^1;
void delay(u16 i){
		while(i--);
}
void main(){
		while(1){
			led1=0,led2=1;
			delay(50000);
			led1=1;led2=0;
			delay(50000);
		}
}