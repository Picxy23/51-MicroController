#include <REGX52.H>
#include <INTRINS.H>

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


void main()
{
	unsigned char LEDNum = 0; // unsigned char of 0 has value 0x0
	while(1)
	{
		if (P3_1 == 0)
		{
			Delay(20);
			while(P3_1 == 0){}
			Delay(20);
				
			LEDNum ++;				
			// 1111 1111
			// 0000 0000
			P2 = ~LEDNum;
		}	
	}
}