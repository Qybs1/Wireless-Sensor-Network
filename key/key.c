#include <ioCC2530.h>

#define KEY   P0_1
#define BEEP  P0_0
#define LED1  P1_0
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

void keyInit()
{
	P0SEL &= ~0x2;		//1111 1101
	P0DIR &= ~0x2;		//1111 1101
	P0INP &= ~0x2;	

}

void ledInit()
{
    P1SEL &= ~0x13;	//1110 1100
    P1DIR |=  0x11; //0001 0011
    
    P1_0 = 0;
	P1_4 = 0;
}

uchar keyScan(void)
{
	if(KEY == 0){

		Delay(100);
		if(KEY == 0){
			while(!KEY);
			return 1;
		}
	}

	return 0;

}

void main(void)
{
	beepInit();
    ledInit();
	keyInit();

	while(1){
		if(keyScan()){
			LED1 = ~LED1;	
		}
	}
}