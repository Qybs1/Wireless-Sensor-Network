#include <ioCC2530.h>
#include <string.h>

#define BEEP P0_0
#define led1 P1_0
#define led2 P1_1

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
        for (j=0; j<1060; j++);
}

void clockInit(void)
{
	CLKCONCMD &= ~0x40;
	while(CLKCONSTA & 0x40);
	CLKCONCMD &= ~0x47;
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
    IEN0 = IEN1 = IEN2 = 0x00;
}


void uartSendString(char *data, int count)
{
	uint i;

	for(i = 0;i < count; i++){
		U0DBUF = *data++;
		while(UTX0IF == 0);
		UTX0IF = 0;
	}
	
	U0DBUF = 0x0A;                   //输出换行
    while(UTX0IF == 0);
    UTX0IF = 0;
}

void InitT3(void)
{
    T3CCTL0 = 0x44;       
    T3CC0 = 0xFA;         
    T3CTL |= 0x9A;       
    IEN1 |= 0x08;     
    IEN0 |= 0x80;          
}


void adcInit(void)
{
	P1DIR = 0x03; //P1 控制 LED
	led1 = 1;
	led2 = 1; //�?LED
	
	ADCH 	&= 0x00;
	ADCCON3  = 0xBF;
	ADCCON1  = 0X30;
	ADCCON1 |= 0x40;
}

void main(void)
{
	beepInit();
	clockInit();
	uartInit();
	adcInit();
	InitT3();

	unsigned short reading;
	float num;
	char datas[12] = {0};



	ADCCON3=0xbf;
	while(1)
	{
		if(ADCCON1 > 0x80)
		{
			led1 = 0;
			reading  = ADCL;
			reading |= ADCH << 8;
			reading >>= 2;
			ADCCON1 |= 0x40;

			num = (float)(reading)*3.3/8192;
			sprintf(datas,"get%.02fV",num);
			uartSendString(datas,12);
			deLay(1000);
			led1 = 1; 
			deLay(1000);
		}
	}
}

