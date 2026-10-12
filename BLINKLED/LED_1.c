#include<reg52.h>

void delay_ms(unsigned int itime)
{
	unsigned int i,j;
	for(i = 0 ; i<itime ; i++)
	for (j=0 ; j<1000 ; j++);
	
}

void main (void)
{
	unsigned char i;
	while(1)
	{
	{
		for(i=0 ; i<10 ; i++)
		
			P0 = 0xFF;
			delay_ms(50);
			P0 = 0x00;
			delay_ms(50);
		}
			delay_ms(10);
		
		for(i=0 ; i<10 ; i++)
		{
			P0 = 0xAA;
			delay_ms(50);
			P0 = 0x55;
			delay_ms(50);
		}
			delay_ms(10);
		
		for(i=0 ; i<10 ; i++)
		{
			P0 = 0x55;
			delay_ms(50);
			P0 = 0xAA;
			delay_ms(50);
		}
			delay_ms(10);
		
		for(i=0 ; i<10 ; i++)
		{
			P0 = 0xF0;
			delay_ms(50);
			P0 = 0x0F;
			delay_ms(50);
		}
			delay_ms(10);
	}
}
