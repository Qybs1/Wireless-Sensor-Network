#include <ioCC2530.h>
#include "uart.h" 

void uartInit()
{
    CLKCONCMD &= ~0x40;      
    while(CLKCONSTA & 0x40); 
    CLKCONCMD &= ~0x47;      
    
    PERCFG = 0x00;           
    P0SEL  = 0x0c;             
    P2DIR &= ~0xC0;          
    
    U0CSR  |= 0x80;           
    U0GCR  |= 11;                  
    U0BAUD |= 216;           
    UTX0IF  = 0;              
    
}
   
void UartSendString(unsigned char *Data, int len) 
{
    int j; 
    for(j=0;j<len;j++) 
    { 
        U0DBUF = *Data++; 
        while(UTX0IF == 0); 
        UTX0IF = 0; 
    } 
}

