#include <ioCC2530.h>

#define LED1 P1_0
#define LED2 P1_1
#define LED3 P1_4
#define BEEP P0_0

typedef unsigned int uint;
typedef unsigned char uchar;


void lightOnOrOff(uchar mode)
{
	LED1 = mode;
	LED2 = mode;
	LED3 = mode;
}

void beepInit()
{
	P0SEL &= ~0x1;	//1111 1110
	P0DIR |=  0x1;

	BEEP = 0;
}

void InitLed()
{
	P1SEL &= 0xEC;	//1110 1100
	P1DIR |= 0x11;	//0001 0001
	P1DIR 

	lightOnOrOff(0);
}


void Delay(uint msec)
{
	uint i,j;
    
    for (i=0; i<msec; i++)
        for (j=0; j<535; j++);

}

void main(void)
{
	uchar i;

	beepInit();
	InitLed();

	while(1){

		LED1 = !LED1;
		Delay(200);
		LED2 = !LED2;
		Delay(200);
		LED3 = !LED3;
		Delay(200);

		for (i = 0; i < 2; i++)
		{
			lightOnOrOff(1);
			Delay(200);
			lightOnOrOff(0);
			Delay(200);
		}

		Delay(500);
	}
}