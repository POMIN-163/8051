#include <reg51.h>   	//51��Ƭ��ͷ�ļ�
#include <intrins.h>	//�����ƺ�����
#include <math.h>			//��ѧ���㺯��ͷ�ļ�
#include <jichu.h>		//�Զ���ͷ�ļ�
char key;							//�����ֵ
uchar smg[];
void delay(uint x){		//�ӳٺ���1ms����
	uint i,j;
	for(i=0;i<x;i++)
		for(j=0;j<112;j++);
}
void delay1(uint y){		//�ӳٺ���10us����
	while(y--);
}
void main(){						//���������
	echar key;
	while(1){
		order();
	}
}