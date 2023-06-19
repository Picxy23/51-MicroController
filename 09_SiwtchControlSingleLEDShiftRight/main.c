#include <REGX52.H>
#include <INTRINS.H>

void Delay(unsigned int xms);


void main()
{
	unsigned char LEDNum;
	P2 = ~0x01;


	while(1)
	{
		// Move right
		if (P3_0 == 0)
		{
			Delay(20);
			while (P3_0 == 0){}
			Delay(20);
			
			LEDNum ++;
			if (LEDNum >= 8){LEDNum = 0;}
			P2 = ~(0x01 << LEDNum); // Note take reverse to let LED light up.
		}
				// Move right
		if (P3_1 == 0)
		{
			Delay(20);
			while (P3_1 == 0){}
			Delay(20);
			
			if (LEDNum == 0){LEDNum = 7;} // This to avoid wrap around unsigned
			else {LEDNum --;}
			P2 = ~(0x01 << LEDNum); // Note take reverse to let LED light up.
		}
	}
	
	
}


void Delay(unsigned int xms)		//@11.0592MHz
{
	unsigned char i, j;
	
	while (xms --)
	{
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}