#include <reg52.h>

// Define our push button switch on Port 3, Pin 2
sbit button = P3^3; 

void delay(unsigned int ms) {
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 112; j++);
}

// Single Master Common Anode Array for Digits 0-9
unsigned char ca_display[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void main() {
    unsigned char hundreds = 0;
    unsigned char tens = 0;
    unsigned char units = 0;
	
	// 3. Wait here until you release the button (prevents rapid auto-running)
while(button == 0) {
    // Refresh Port 0 first to force its open-drain pins to settle
    P0 = ca_display[units];    
    P1 = ca_display[tens];     
    P2 = ca_display[hundreds]; 
}


    // Ensure the button pin is configured as an input pin (set to 1)
    button = 1;

    while(1) {
        // Continuously refresh displays with current values
        P0 = ca_display[hundreds]; 
        P1 = ca_display[tens];     
        P2 = ca_display[units];    
        
        // Check if the button is pressed (goes LOW)
        if (button == 0) {
            delay(20); // 1. Debounce delay: wait for mechanical contact bounce to settle
            
            if (button == 0) { // Double check if it's still pressed
                
                // 2. Increment counting arithmetic logic
                units++;
                if(units > 9) {
                    units = 0;
                    tens++;
                    if(tens > 9) {
                        tens = 0;
                        hundreds++;
                        if(hundreds > 9) {
                            hundreds = 0; 
                        }
                    }
                }
                
                // 3. Wait here until you release the button (prevents rapid auto-running)
                while(button == 0) {
                    // Keep keeping the displays lit while holding down the button
                    P2 = ca_display[hundreds]; 
                    P1 = ca_display[tens];     
                    P0 = ca_display[units];
                }
                
                delay(20); // Small delay after release to prevent release bounce
            }
        }
    }
}
