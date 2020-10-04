#include "LCD1602.h"

void main()
{
    uchar i, arr[] = "123456789";//LCD1602-  -POMIN                        LCD1602-  -POMIN";// 0-40第一行,41-80第二行

    LcdInit();
    for ( i = 0; i < sizeof(arr)/sizeof(char)-1; i++)
    {
        LcdWriteData(arr[i]);
    }
    while (1);
}
