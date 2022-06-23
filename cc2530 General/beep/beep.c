#include <ioCC2530.h>

#define BEEP P0_0

typedef unsigned int uint;
typedef unsigned char uchar;

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

void main(void)
{
	beepInit();
	
}