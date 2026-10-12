#include <reg51.h>

// Pin definitions for LCD Control Pins
sbit RS = P3^5;
sbit EN = P3^6;

// Keypad Port Definition
#define KEYPAD_PORT P1

// Function Declarations
void delay_ms(unsigned int ms);
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data_out);
void lcd_init(void);
char keypad_scan(void);

// 4x4 Keypad Map Matrix
char code keymap[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

void main(void) {
    char key;
    lcd_init();               // Initialize 16x2 LCD
    
    // Display Initial Message
    lcd_cmd(0x80);            // Force cursor to 1st line, 1st position
    lcd_data('P'); lcd_data('r'); lcd_data('e'); lcd_data('s'); 
    lcd_data('s'); lcd_data(' '); lcd_data('K'); lcd_data('e'); lcd_data('y'); lcd_data(':');
    
    lcd_cmd(0xC0);            // Move cursor to 2nd line
    
    while(1) {
        key = keypad_scan();  // Scan keypad for keypress
        if(key != 0) {
            lcd_data(key);    // Display pressed key character on LCD
        }
    }
}

// Millisecond Delay Routine
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 120; j++);
}

// Send Command to LCD
void lcd_cmd(unsigned char cmd) {
    P2 = cmd;                 // Load command to Data Port (P2)
    RS = 0;                   // RS = 0 for Command
    EN = 1;                   // Pulse Enable high-to-low
    delay_ms(2);
    EN = 0;
}

// Send Data (Character) to LCD
void lcd_data(unsigned char data_out) {
    P2 = data_out;            // Load ASCII data to Data Port (P2)
    RS = 1;                   // RS = 1 for Data
    EN = 1;                   // Pulse Enable high-to-low
    delay_ms(2);
    EN = 0;
}

// Initialize LCD in 8-bit Mode
void lcd_init(void) {
    delay_ms(20);
    lcd_cmd(0x38);            // 8-bit mode, 2 lines, 5x7 matrix
    lcd_cmd(0x0C);            // Display ON, Cursor OFF
    lcd_cmd(0x06);            // Entry mode: Auto-increment cursor
    lcd_cmd(0x01);            // Clear display
    delay_ms(2);
}

// Scan Keypad for Pressed Keys
char keypad_scan(void) {
    unsigned char row, col;
    
    for(row = 0; row < 4; row++) {
        // Set all rows HIGH, then pull current scanning row LOW
        KEYPAD_PORT = 0xFF;
        KEYPAD_PORT &= ~(1 << row);
        
        // Read columns (P1.4 to P1.7)
        if((KEYPAD_PORT & 0xF0) != 0xF0) {
            delay_ms(20);     // Software debounce delay
            if((KEYPAD_PORT & 0xF0) != 0xF0) {
                // Determine column index
                if((KEYPAD_PORT & 0x10) == 0) col = 0;
                else if((KEYPAD_PORT & 0x20) == 0) col = 1;
                else if((KEYPAD_PORT & 0x40) == 0) col = 2;
                else if((KEYPAD_PORT & 0x80) == 0) col = 3;
                
                // Wait until key is released (prevents multiple prints)
                while((KEYPAD_PORT & 0xF0) != 0xF0);
                
                return keymap[row][col];
            }
        }
    }
    return 0;                 // Return 0 if no key is pressed
}