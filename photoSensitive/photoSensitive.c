#include <ioCC2530.h>
#include <string.h>

#define BEEP P0_0
#define led1 P1_0
#define led2 P1_1
#define ADCCON3_EREF (0x2<<6)
#define ADCCON3_EVID_512rate (0x3<<4)
#define ADCCON3_ECH (0x6<<0)


typedef unsigned int uint;
typedef unsigned char uchar;
typedef signed short  int16;
typedef unsigned short  uint16;

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
    P0SEL  |=  0x0C;	//0000 1100
    P2DIR  &= ~0xC0;	//1000 0000

    U0UCR   =  0x00;

    U0CSR  |=  0x80;
    U0GCR  |=  11;
    U0BAUD |=  216;		//baud115200

    UTX0IF  =  0;
}


void uartSendString(char *data, int count)
{
	uint i;

	for(i = 0;i < count; i++)
	{
		U0DBUF = *data++;
		while(UTX0IF == 0);
		UTX0IF = 0;
	}
	U0DBUF = 0x0A;                   //è¾“å‡ºæ¢è¡�?   
	while(UTX0IF == 0);
    UTX0IF = 0;

}

uint16 readPhotoSensitive(void)
{
	uint16 reading;

	reading = 0;

	ADCCFG  |= 0x40;
	ADCCON3  = ADCCON3_ECH|ADCCON3_EREF|ADCCON3_EVID_512rate;
	ADCCON1 |= 0x40;
	
	while (!(ADCCON1 & 0x80));
	ADCCFG  &= (0x40 ^ 0xFF);

	reading  = ADCL;
	reading |= (int16)(ADCH << 8);
	reading >>= 2;

	return (reading);
}

void main(void)
{
	beepInit();
	clockInit();
	uartInit();

	char datas[12] = '\0';

	uint16 temp;

	while(1)
	{
		temp = readPhotoSensitive();
	
		datas[0] = temp / 100+'0';
		datas[1] = temp /10%10 +'0';
		datas[2] = temp % 10+'0';
		datas[3] = '\r';
		datas[4] = '\n';

		uartSendString(datas,5);

		deLay(2000);
	}
}

