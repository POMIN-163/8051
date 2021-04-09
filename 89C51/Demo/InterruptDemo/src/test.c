#include "reg51.h"
#define MODE_NUM 3 // 三种模式(灭、亮、闪)

sbit led = P2 ^ 0;
sbit key = P3 ^ 1;

void delay(unsigned int i) {
    unsigned int temp;
    while (i--)
        for (temp = 0; temp < 1000; temp++);
}

bit Scan_key(void) {
    if (key == 0){
        delay(200);
        if (key == 0)
            return 1;
    }
    return 0;
}

void main(void) {
    unsigned char mode = 0;
    bit temp = 0;
    while (1) {
        temp = Scan_key();
        if (temp) {
            if (mode >= MODE_NUM) mode = 0;// 重置模式(灭)
            else mode++;
            temp = 0;
        }
        switch (mode) {
            case 0 :// 常灭
                led = 1;
                break;
            case 1 :// 常亮
                led = 0;
                break;
            case 2 :// 闪烁
                led = 0;
                delay(1000);
                led = 1;
                delay(1000);
                break;
        }
    }
}
