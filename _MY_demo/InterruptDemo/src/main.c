#include "interrupt.h"
#include "intrins.h"
#include "init.h"
#include "main.h"

void delay_5us() {// 调用2us + 结束2us + nop 1us
    _nop_();
}
void delay_ms(uint x) {
    uint y = 0U; uchar z;
    for (y = 0U; y < x; y++) { // n * 1ms
        for (z = 0U; z < 200U; z++) // 1ms
				    delay_5us();
    }
}

void main() {
    Init_INT0();
    Init_INT1();
    Init_Timer0();
    Init_Timer1();
    while(1) {
        delay_ms(500);
    }
}

