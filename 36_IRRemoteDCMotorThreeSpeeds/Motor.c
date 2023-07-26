#include <REGX52.H>
#include "Timer1.h"

sbit Motor = P1^0;

unsigned char Counter, Compare;

void Motor_Init()
{
	Timer1_Init();
}

void Motor_SetSpeed(unsigned char Speed)
{
	Compare = Speed;
}

void Timer1_Routine(void) interrupt 3 // Emter every 100us
{
	TL1 = 0x9C;		//Initial timer value
	TH1 = 0xFF;		//Initial timer value
	
	Counter ++;
	Counter %= 100; // Clear when arrving at 100, 0 ~ 99
	
	// Compare with Control to perform ON OFF 
	if (Counter < Compare) // Counter bigger ON for longer?
		Motor = 1;
	else
		Motor = 0;

}