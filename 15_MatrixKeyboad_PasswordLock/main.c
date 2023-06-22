#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"

unsigned char KeyNum;
unsigned int Password, Count;

void main()
{
	// S1 - S10 are 1 - 9 - 0
	// S11 Confirm
	// S12 Cancel
	LCD_Init();
	LCD_ShowString(1, 1, "Password:");
	while(1)
	{
		KeyNum = MatrixKey();
		if (KeyNum) // Without this every loop will be refreshed to 0
		{
			if (KeyNum <= 10 && Count < 4) // If S1 - S10, recieve one digit input
			{
				Password *= 10; // Shift up for next digit
				Password += KeyNum % 10; // Convert to single digit, add to password
				Count ++; // Count times
			}
			
			if (KeyNum == 11) // S11, confirm, check with password
			{
				if (Password == 2345) //Correct
				{
					LCD_ShowString(1, 14, "OK ");
					Password = 0; //Reset
					Count = 0;
				}
				else
				{
					LCD_ShowString(1, 14, "ERR");
					Password = 0;
					Count = 0;
				}
			}
			
			if (KeyNum == 12)
			{
					Password = 0;
					Count = 0;
			}
			
			LCD_ShowNum(2, 1, Password, 4); // Refresh Screen
		}
	}
}