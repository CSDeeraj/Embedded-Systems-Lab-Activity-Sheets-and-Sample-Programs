#include <LPC21xx.H>
void delay (void)
{
	int i;
	for (i=0; i<100000; i++);
}
int main(void)
{
	unsigned int sw;
	PINSEL0 = 0x00000000;
	IO0DIR = 0x00000001;
	IO0CLR = 0x00000001;
	while(1)
    {
		 sw = IO0PIN & 0x00000002;   // Read P0.1
			if(sw == 0x00000002)
				IO0CLR = 0x00000001;
			else
				IO0SET = 0x00000001;
			delay();
		}
	}
