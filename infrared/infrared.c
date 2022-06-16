#include <ioCC2530.h>

#define INFRARED P0_5
#define BEEP  P0_0
#define LED1 P1_0
typedef unsigned int uint;
typedef unsigned char uchar;

void beepInit()
{
	P0SEL &= ~0x1;	//1111 1110
	P0DIR |=  0x1;

	BEEP = 0;
}

void Delay(uint msec)
{
	uint i,j;
    
    for (i=0; i<msec; i++)
        for (j=0; j<535; j++);

}

void infraredInit()
{
	P0SEL &= ~0x20;		//0010 0000
	P0DIR &= ~0x20;		//0010 0000
	
	P1_1 = 0;
	P1_4 = 0;

}

void ledInit()
{
    P1SEL &= ~0x13;	//1110 1100
    P1DIR |=  0x13; //0001 0011

}

void main(void)
{
	beepInit();
    ledInit();
	infraredInit();

	while(1){
		if(INFRARED == 1){
			LED1 = 1;
		}else{
			LED1 = 0;
		}
	}
}