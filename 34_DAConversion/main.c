#include <REGX52.H>
#include "Key.h"
#include "Delay.h"
#include "Timer0.h"
#include "Nixie.h"

sbit DA = P2^1;

unsigned char Counter, Compare;
unsigned char i;

void main()
{
	Timer0_Init();
	Compare = 5;
	while(1)
	{
		for (i = 0; i < 100; i ++)
		{
			Compare = i;
			Delay(10);
		}
		for (i = 100; i > 0; i --)
		{
			Compare = i;
			Delay(10);			
		}
	}
}

void Timer0_Routine(void) interrupt 1 // Emter every 100us
{
	TL0 = 0x9C;		//Initial timer value
	TH0 = 0xFF;		//Initial timer value
	
	Counter ++;
	Counter %= 100; // Clear when arrving at 100, 0 ~ 99
	
	// Compare with Control to perform ON OFF 
	if (Counter < Compare) // Counter bigger ON for longer?
		DA = 1;
	else
		DA = 0;

}