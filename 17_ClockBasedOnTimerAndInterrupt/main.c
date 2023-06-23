#include <REGX52.H>
#include "Timer0.h"
#include "LCD1602.h"
#include "Delay.h"

unsigned char Sec, Min, Hour;

void main()
{
	LCD_Init();
	Timer0Init();
	LCD_ShowString(1, 1, "Clock:");
	LCD_ShowString(2, 3, ":");
	LCD_ShowString(2, 6, ":");
	while(1)
	{
		LCD_ShowNum(2, 1, Hour, 2);
		LCD_ShowNum(2, 4, Min, 2);
		LCD_ShowNum(2, 7, Sec, 2);
	}
}



void Timer0_Routine(void) interrupt 1
{
	static unsigned int T0Count; // Static is not destroyed
	// Fix the initialization back
	TL0 = 0x66;		//Initial timer value
	TH0 = 0xFC;		//Initial timer value
	
	T0Count ++;
	if (T0Count >= 1000) // 1s
	{
		T0Count = 0;
		Sec ++;
		if (Sec >= 60)
		{
			Sec = 0;
			Min ++;
			if (Min >= 60)
			{
				Min = 0;
				Hour ++;
				if (Hour >= 24)
				{
					Hour = 0;
				}
			}
		}

	}
}