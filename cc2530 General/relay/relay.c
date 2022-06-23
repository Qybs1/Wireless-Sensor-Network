#include <ioCC2530.h>

#define RELAY P1_3
#define BEEP  P0_0

typedef unsigned int uint;
typedef unsigned char uchar;

void beepInit()
{
	P0SEL &= 0xFE;	//1111 1110
	P0DIR |= 0x1;

	BEEP = 0;
}

void Delay(uint msec)
{
	uint i,j;
    
    for (i=0; i<msec; i++)
        for (j=0; j<535; j++);

}

void relayInit()
{
	P1SEL &= 0xF7;	//1111 0111
	P1DIR |= 0x1<<3;	//0000 1000
}

void main(void)
{
	beepInit();
	relayInit();

	while(1){

		RELAY = 1;
		Delay(500);
		RELAY = 0;
		Delay(500);
	}
}