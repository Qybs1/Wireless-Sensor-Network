#include <ioCC2530.h>
#include <string.h>
#include "uart.h"
#include "dht.h"

#define BEEP P0_0

void beepInit()
{
    //P0SEL &= 0xFE;    //1110 1100
    P0DIR |= 0x01;
    
    BEEP = 0;
}

void main(void)
{
    beepInit();
    Delay_ms(1000);
    uartInit();

    uchar temp[3]; 
    uchar humidity[3];   
    uchar strTemp[13]="Temperature:";
    uchar strHumidity[10]="Humidity:";

    while(1)
    {
        memset(temp,0,3);
        memset(humidity,0,3);

        DHT11();

        temp[0]=wendu_shi+0x30;
        temp[1]=wendu_ge+0x30;
        humidity[0]=shidu_shi+0x30;
        humidity[1]=shidu_ge+0x30;

        UartSendString(strTemp,12);
        UartSendString(temp,2);
        //UartSendString("   ", 3);
        UartSendString(strHumidity,9);
        UartSendString(humidity,2);
        UartSendString("\n", 1);

        Delay_ms(2000);
    }
}
