#include <REGX52.H>
#include <INTRINS.H>

void Delay(unsigned int xms)		
{
	unsigned char i, j;

	while(xms --)
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
	while(1)
	{
		if (P3_1 == 0)
		{
			Delay(20); // Filter Ossilation
			while (P3_1 == 0){}
			Delay(20);
				
			P2_0 = ~P2_0; // Take Not
		}
	}
}