#include <REGX52.H>
#include "LCD1602.h"
#include "DS18B20.h"
#include "Delay.h"

float T;

void main()
{
	LCD_Init();
	
	// Make sure no default value show, taking time to setup
	DS18B20_ConvertT();
	Delay(1000);
	
	LCD_ShowString(1, 1, "Temperature");

	while(1)
	{
		DS18B20_ConvertT();
		T = DS18B20_ReadT();
		// Take float Apart
		// Show sign
		if (T < 0) 
		{
			LCD_ShowChar(2, 1, '-');
			T = -T; // Make into positive
		}
		else 
		{LCD_ShowChar(2, 1, '+');}
		// Show Num
		LCD_ShowNum(2, 2, T, 3); //AUto lost float part
		LCD_ShowChar(2, 5, '.');
		LCD_ShowNum(2, 6, ((unsigned long)(T*10000))%10000, 4); // Get floating point gone first, change to long then mod
		// Cannnot % a float
	}
}