#include <LPC21xx.H>
void delay(void)
{
    int i;
    for(i=0; i<250000; i++);
}
// Segment patterns for common cathode display, bits = P0.0(a) to P0.7(dp)
unsigned char digit[10] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};
int main(void)
{
    unsigned char i;

    PINSEL0 = 0x00000000;   // P0.0 - P0.7 as GPIO
    IO0DIR  = 0x000000FF;   // P0.0 - P0.7 as output

    while(1)
    {
        for(i=0; i<10; i++)
        {
            IO0PIN = digit[i];   // Send segment pattern
            delay();
        }
    }
}