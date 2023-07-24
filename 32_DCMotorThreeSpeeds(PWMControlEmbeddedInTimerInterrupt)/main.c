#include <REGX52.H>
#include "Key.h"
#include "Delay.h"
#include "Timer0.h"
#include "Nixie.h"

sbit Motor = P1^0;

unsigned char KeyNum, Speed;

unsigned char Counter, Compare;

void main()
{
	Timer0_Init();
	Compare = 5;
	while(1)
	{
		KeyNum = Key();
		if (KeyNum == 1)
		{
			Speed ++;
			Speed %= 4;
			if (Speed == 0) Compare = 0;
			if (Speed == 1) Compare = 50;
			if (Speed == 2) Compare = 75;
			if (Speed == 3) Compare = 100;
		}
		Nixie(1, Speed);			
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
		Motor = 1;
	else
		Motor = 0;

}