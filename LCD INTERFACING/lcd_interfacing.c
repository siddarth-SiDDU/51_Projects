#include <reg52.h>
#define DataBus P1
sbit RS = P2^0;
sbit EN = P2^1;


/* Function declarations */
void delay_ms(unsigned int itime);
void LCD_Init(void);
void LCD_WriteCommand(unsigned char cmd);
void LCD_WriteData(unsigned char dat);
void LCD_DisplayString(unsigned char *string_ptr);
	
/* Delay function */
void delay_ms(unsigned int itime)
{
    unsigned int i, j;
    for(i = 0; i < itime; i++)
    for(j = 0; j < 200; j++);
}

/* Send command to LCD */
void LCD_WriteCommand(unsigned char cmd)
{
    DataBus = cmd;
    RS = 0;                 
    EN = 1;
    delay_ms(1);
    EN = 0;
    delay_ms(2);
}


/* Send data to LCD */
void LCD_WriteData(unsigned char dat)
{
    DataBus = dat;
    RS = 1;                 
    EN = 1;
    delay_ms(1);
    EN = 0;
    delay_ms(2);
}


/* LCD initialization */
void LCD_Init(void)
{
    delay_ms(20);           // Power-up delay
    LCD_WriteCommand(0x38); // 8-bit mode, 2 lines, 5x7
    LCD_WriteCommand(0x0C); // Display ON, cursor OFF
    LCD_WriteCommand(0x01); // Clear display
    LCD_WriteCommand(0x06); // Cursor moves right
    LCD_WriteCommand(0x80); // First line, first position
    delay_ms(5);
}


/* Display string */
void LCD_DisplayString(unsigned char *string_ptr)
{
    while(*string_ptr)
    {
        LCD_WriteData(*string_ptr);
        string_ptr++;
    }
}


/* Main */
void main(void)
{
    LCD_Init();
    LCD_WriteCommand(0x80);
    LCD_DisplayString("WELCOME TO MY");
    LCD_WriteCommand(0xC0);
	LCD_DisplayString("  LINKEDIN :)  ");
    while(1);
}