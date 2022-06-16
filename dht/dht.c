#include <ioCC2530.h>
typedef unsigned int  uint;
typedef unsigned char  uchar;
#define DATA_PIN P0_4

uchar ucharFLAG,uchartemp;
uchar shidu_shi,shidu_ge,wendu_shi,wendu_ge=4;
uchar ucharT_data_H,ucharT_data_L,ucharRH_data_H,ucharRH_data_L,ucharcheckdata;
uchar ucharT_data_H_temp,ucharT_data_L_temp,ucharRH_data_H_temp,ucharRH_data_L_temp,ucharcheckdata_temp;
uchar ucharcomdata;

//延时函数
void Delay_us() //1 us
{
    asm("nop");
    asm("nop");
    //asm("nop");
    asm("nop");
}

void Delay_10us() //10 us
{
  Delay_us();
  Delay_us();
}

void Delay_ms(uint Time)//n ms延时
{
    unsigned char i;
    while(Time--)
    {
        for(i=0;i<100;i++)
            Delay_10us();
    }
}

void COM(void)
{
	uchar i;
	for(i=0;i<8;i++)
	{
		while(!DATA_PIN);
		Delay_10us();
		Delay_10us();
		Delay_10us();
		uchartemp=0;
		if(DATA_PIN)
			uchartemp=1;
		while(DATA_PIN);
		ucharcomdata<<=1;
		ucharcomdata|=uchartemp;
	}
}

void DHT11(void)
{
	P0DIR |= 0x10;
    DATA_PIN=0;
    Delay_ms(19);  //>18MS
    DATA_PIN=1; 
    P0DIR &= ~0x10; //重新配置IO口方向输�?    Delay_10us();
    Delay_10us();                        
    Delay_10us();
    Delay_10us();  
    if(!DATA_PIN)
	{
        while(!DATA_PIN);
        while(DATA_PIN); 
        COM();
        ucharRH_data_H_temp=ucharcomdata;
        COM();
        ucharRH_data_L_temp=ucharcomdata;
        COM();
        ucharT_data_H_temp=ucharcomdata;
        COM();
        ucharT_data_L_temp=ucharcomdata;
        COM();
        ucharcheckdata_temp=ucharcomdata;
        DATA_PIN=1; 
        uchartemp=(ucharT_data_H_temp+ucharT_data_L_temp+ucharRH_data_H_temp+ucharRH_data_L_temp);
        if(uchartemp==ucharcheckdata_temp)
        {
            ucharRH_data_H=ucharRH_data_H_temp;
            ucharRH_data_L=ucharRH_data_L_temp;
            ucharT_data_H=ucharT_data_H_temp;
            ucharT_data_L=ucharT_data_L_temp;
            ucharcheckdata=ucharcheckdata_temp;
        }
        wendu_shi=ucharT_data_H/10; 
        wendu_ge=ucharT_data_H%10;
        
        shidu_shi=ucharRH_data_H/10; 
        shidu_ge=ucharRH_data_H%10;        
    } 
    else //没用成功读取，返�?
    {
        wendu_shi=0; 
        wendu_ge=0;
        
        shidu_shi=0; 
        shidu_ge=0;  
    } 
    
    P0DIR |= 0x10; //IO口需要重新配�?
}