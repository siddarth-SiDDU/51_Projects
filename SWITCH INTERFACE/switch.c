#include<reg52.h>
sbit LED = P2^0;
sbit SWITCH = P3^3;

void delay_ms(unsigned int itime)
{
	unsigned int i,j;
	for(i = 0 ; i<itime ; i++)
	for (j=0 ; j<1000 ; j++);
	
}

void main (void)
{
	SWITCH = 1;
	
	while (1)
	{
		if (SWITCH == 0)
		{
			LED = 0;
			//delay_ms(100);
			LED = 1;
		}
		else
		{
			LED = 1;
		}
	
	}
}