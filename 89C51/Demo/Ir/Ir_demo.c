#include "Infrared.h"

sbit smg1=P2^2;
sbit smg2=P2^3;
sbit smg3=P2^4;//数码管IO
sbit k1=P3^1;

extern uchar Ir_Value[4];//调用外部局部变量加extern关键字

uchar code smgz[16]={
0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
//0、1、2、3、4、5、6、7、8、9、A、b、C、d、E、F的显示码
void display(uint rec_H,uint rec_L){
    uchar i;
    char smg[8]={-1,-1,-1,-1,-1,-1,-1,-1,};
        smg[0]=smgz[rec_L%16];
        smg[1]=smgz[(rec_L/16)%16];
        smg[2]=smgz[(rec_L/256)%16];
        smg[3]=smgz[(rec_L/4096)%16];

        smg[4]=smgz[rec_H%16];
        smg[5]=smgz[(rec_H/16)%16];
        smg[6]=smgz[(rec_H/256)%16];
        smg[7]=smgz[(rec_H/4096)%16];
    for (i = 0; i < 8; i++) {
        smg1=((i)&0x01);
        smg2=((i>>1)&0x01);
        smg3=((i>>2)&0x01);
        if (smg[i]==-1)
            P0 =0x00;
        else
            P0 =smg[i];//段码///这三行不可更改否则可能重影
        delay(100);                //延时
        P0 = 0x00;                //消隐
}
}
void main(){
    Ir_Init();
    while(1){
        display((Ir_Value[0]<<8)|(Ir_Value[1]),(Ir_Value[2]<<8)|(Ir_Value[3]));
        if (Ir_Value[2]==0x46)
        {
           P2=0x00;
        }else if (Ir_Value[2]==0x47)
        {
            P2=0xff;
        }
        if (k1==0)
        {
            delay(50);
            if (k1==0)
                IR_Send(0x40a180);
            while(k1==0);
        }
    }
}