#include <REGX52.H>

sbit LED = P2^0;

void Delay(unsigned int t)
{
	while(t --);
}


void main()
{
	unsigned char Time, i;
	while(1)
	{
		// Go Light
		for (Time = 0; Time < 100; Time ++) // Brightness changes every time
		{
			for (i = 0; i < 20; i ++) // Every Brightness run for 20 times
			{
				LED = 0; // On
				Delay(Time);
				
				LED = 1;
				Delay(100 - Time); // Off, 100 - makesure period is same

			}
		}
		// Go Dim
		for (Time = 100; Time > 0; Time --) // Brightness changes every time
		{
			for (i = 0; i < 20; i ++) // Every Brightness run for 20 times
			{
				LED = 0; // On
				Delay(Time);
				
				LED = 1;
				Delay(100 - Time); // Off, 100 - makesure period is same

			}
		}
		
	}
}