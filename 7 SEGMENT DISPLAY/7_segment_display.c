#include <reg52.h>
void delay(unsigned int ms) 
{
    unsigned int i, j;
    for(i = 0; i < ms; i++)
		for(j = 0; j < 112; j++);
}

void main() {
    // Exact same common anode lookup values
    unsigned char ca_codes[] = {0xC0, 0xF9, 0x99, 0xF8, 0xC0 };	
		unsigned char cb_codes[] = {0xC0, 0xA4, 0x92, 0x80, 0xC0 };	
		unsigned char cc_codes[] = {0xC0, 0xB0, 0x82,	0x90, 0xC0 };	
		unsigned char count;
    while(1) 
				{
        for(count = 0; count < 5; count++) 
				{
            P0 = ca_codes[count]; 
						P1 = cb_codes[count]; 
						P2 = cc_codes[count];
					  delay(500);

        }
    }
}
