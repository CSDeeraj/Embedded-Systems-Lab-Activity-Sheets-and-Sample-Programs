#include <LPC21xx.H>
#define RS 0x00000001 // P0.0->RS
#define RW 0x00000002 // P0.1->RW
#define EN 0x00000004 // P0.2->EN
void delay(unsigned int t)
{
    unsigned int i;
    for(i=0; i<t; i++);
}
void lcd_cmd(unsigned char cmd)
{
    IO1PIN = (IO1PIN & 0x00FFFFFF) | (cmd << 24); // Send command to P1.24-P1.31
    IO0CLR = RS;   // RS = 0 for command
    IO0CLR = RW;   // RW = 0 for write
    IO0SET = EN;
    delay(1000);
    IO0CLR = EN;
    delay(5000);
}
void lcd_data(unsigned char data)
{
    IO1PIN = (IO1PIN & 0x00FFFFFF) | (data << 24); //Send data to P1.24-P1.31
    IO0SET = RS; // RS =1 for data
    IO0CLR = RW;
    IO0SET = EN;
    delay(1000);
    IO0CLR = EN;
    delay(5000);
}
void lcd_init(void)
{
    lcd_cmd(0x38); //8 bit mode, 2 line, 5x7 font
    lcd_cmd(0x0C);  //Display ON, cursor OFF
    lcd_cmd(0x01); //Clear display
    delay(5000);
    lcd_cmd(0x06); //Entry mode: increment cursor
    lcd_cmd(0x80); //cursor to first line
}
void lcd_string(char *str)
{
    while(*str)
    {
      lcd_data(*str);
      str++;
    }
}
int main(void)
{
    PINSEL0 = 0x00000000;
    PINSEL2 = 0x00000000;
    IO0DIR = RS | RW | EN; //P0.0, P0.1, P0.2 as output
    IO1DIR = 0xFF000000; //P1.24 - P1.31 as output (data lines)
    lcd_init();
    lcd_cmd(0x80);              // Line 1, position 0
		lcd_string("Hey Guys It's ME");
		lcd_cmd(0xC0);              // Line 2, position 0 - 0xC0 is second-line address
		lcd_string("CSE24106 Deeru");

    while(1);
}