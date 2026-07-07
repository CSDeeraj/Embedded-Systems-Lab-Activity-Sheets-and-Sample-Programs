#include<LPC21xx.H>

void delay (void)
{
	int i;
	for (i=0;i<100000;i++);
}
int main(void)
{
	PINSEL2 = 0x00000000;
	IO1DIR = 0x01000000;
	while(1)
	{
		IO1SET=0x01000000;
		delay();
		IO1CLR = 0x01000000;
		delay();
	}
}
