#include <reg51.h>   	//51单片机头文件
#include <intrins.h>	//左右移函数等
#include <math.h>			//数学运算函数头文件
#include <jichu.h>		//自定义头文件
char key;							//定义键值
uchar smg[];
void delay(uint x){		//延迟函数1ms左右
	uint i,j;
	for(i=0;i<x;i++)
		for(j=0;j<112;j++);
}
void delay1(uint y){		//延迟函数10us左右
	while(y--);
}
void main(){						//主函数入口
	echar key;
	while(1){
		order();
	}
}