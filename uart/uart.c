#include <ioCC2530.h>
#include <string.h>

#define BEEP P0_0

typedef unsigned int uint;
typedef unsigned char uchar;

#define UART0_RX    1
#define UART0_TX    2
#define SIZE       51

char RxBuf;
char UartState;
uchar count;
char RxData[SIZE];

void beepInit()
{
	P0SEL &= 0xFE;	//1110 1100
	P0DIR |= 0x1;
	
	BEEP = 0;
}

void deLay(uint msec)
{
	uint i,j;
    
    for (i=0; i<msec; i++)
        for (j=0; j<535; j++);
}

void uartInit(void)
{
    PERCFG  =  0x00;
    P0SEL   =  0x0C;	//0000 0110
    P2DIR  &= ~0xC0;	//1000 0000

    U0UCR   =  0x00;

    U0CSR  |=  0x80;
    U0GCR  |=  11;
    U0BAUD |=  216;		//baud115200

    UTX0IF  =  0;
    U0CSR  |=  0x40;
    IEN0   |=  0x84;	//1000 0100
}

void uartSendString(char *data, int count)
{
	uint i;

	for(i = 0;i < count; i++){
		U0DBUF = *data++;
		while(UTX0IF == 0);
		UTX0IF = 0;
	}

}
/****************************************************************************
* Name: UART0_ISR(void) Serial port interrupt handling function 
* Description: When the receive interrupt is generated on serial port 0, the received data is saved in RxBuf
****************************************************************************/
#pragma vector = URX0_VECTOR 
__interrupt void UART0_ISR(void) 
{ 
    URX0IF = 0;       //Clear interrupt flag
    RxBuf = U0DBUF;                           
}

void main(void)
{
	beepInit();

	CLKCONCMD &= ~0x40;
	while(CLKCONSTA & 0x40);
	CLKCONCMD &= ~0x47;

	uartInit();
	UartState = UART0_RX;
	memset(RxData, 0, SIZE);

   	while(1){
   		if(UartState == UART0_RX){
   			if(RxBuf != 0){
   				if((RxBuf != '#') && (count < 50))
   					RxData[count++] = RxBuf;
   				else{
   					if (count > 50)
   					{
   						count = 0;
   						memset(RxData, 0, SIZE);
   					}
   					else{
   						UartState = UART0_TX;
   					}
   				}
   				RxBuf = 0;

   			}
   		}
   		if (UartState == UART0_TX)
   		{
   			U0CSR &= ~0x40;
   			uartSendString(RxData,count);
   			U0CSR |=  0x40;
   			UartState = UART0_RX;
   			count = 0;
   			memset(RxData, 0, SIZE);
   		}

   	}
}