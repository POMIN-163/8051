#include "DS18B20.h"

uchar code smgz[]={//显示0~F,-的值
    0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
    0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,
    0x40
};
void delay(uint x){
    while(x--);
}
void display(uint rec,bit dec){// 数码管显示dec表示正负
    uchar i;
    char smg[8]={-1,-1,-1,-1,-1,-1,-1,-1,};
    if (dec)
        smg[4] = 16;//负号
    else
        smg[4] = -1;
    smg[0] = (rec)%10;
    smg[1] = (rec)/10%10;
    smg[2] = (rec/100)%10;
    smg[3] = (rec/1000)%10;
    for (i = 0; i < 8; i++){
        smg1=((i)&0x01);
        smg2=((i>>1)&0x01);
        smg3=((i>>2)&0x01);
        if (i==2){
            P0 = smgz[smg[i]]+0x80;
        }else if (smg[i]==-1)
            P0 = 0x00;
        else
            P0 = smgz[smg[i]];   //段码///这三行不可更改否则可能重影
        delay(100);                //延时
        P0 = 0x00;                //消隐
    }
}
void main(){
    uint result;
    while (1){
        result = DS18B20_Result();
//display(result);
        if ((result>>11)==0x00){//判断正负
            result = result * 0.0625 * 100;
            display(result,0);
        }else{
            result -= 1;
            result = ~result;//为负则执行数据还原
            result = result * 0.0625 * 100;
            display(result,1);
        }
    }
}