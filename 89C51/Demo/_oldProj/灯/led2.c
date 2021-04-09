#include "reg51.h"
sbit led1=P2;
void led(){
	led1=0x55;
}
void main()
{
	while(1){
		led();	
	}
}