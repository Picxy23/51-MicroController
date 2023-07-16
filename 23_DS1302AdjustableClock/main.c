#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Key.h"
#include "Timer0.h"

unsigned char KeyNum, MODE, TimeSetSelect, TimeSetFlashFlag;

/**
 * @brief Show time as is increase
 * @param None
 * @retval None
 */
void TimeShow()
{
	// Show Time
	DS1302_ReadTime(); // Bug
	LCD_ShowNum(1, 1, DS1302_Time[0], 2);
	LCD_ShowNum(1, 4, DS1302_Time[1], 2);
	LCD_ShowNum(1, 7, DS1302_Time[2], 2);
	LCD_ShowNum(2, 1, DS1302_Time[3], 2);
	LCD_ShowNum(2, 4, DS1302_Time[4], 2);
	LCD_ShowNum(2, 7, DS1302_Time[5], 2);
}

/**
 * @brief Set and Show time base on component selected
 * @param None
 * @retval None
 */
void TimeSet()
{
	// Select which to change
	if(KeyNum == 2)
	{
		TimeSetSelect ++;
		TimeSetSelect %= 6; // Another way of resetting 0 when overflow
	}
	// Increment
	if(KeyNum == 3)
	{
		DS1302_Time[TimeSetSelect] ++;
		// Fix overflow
		if (DS1302_Time[0] > 99) {DS1302_Time[0] = 0;} // Year
		if (DS1302_Time[1] > 12) {DS1302_Time[1] = 1;} // Month
		// Date Special check
			// Big Month
		if (DS1302_Time[1] == 1 || DS1302_Time[1] == 3 ||
			DS1302_Time[1] == 5 || DS1302_Time[1] == 7 ||
			DS1302_Time[1] == 8 || DS1302_Time[1] == 10 ||
			DS1302_Time[1] == 12)
		{
			if (DS1302_Time[2] > 31) {DS1302_Time[2] = 1;} 
		}
			// Small Month
		else if (DS1302_Time[1] == 4 || DS1302_Time[1] == 6 ||
				 DS1302_Time[1] == 9 || DS1302_Time[1] == 11)
		{
			if (DS1302_Time[2] > 30) {DS1302_Time[2] = 1;} 
		}
			// Feb
		else if (DS1302_Time[1] == 2)
		{
			if (DS1302_Time[0] % 4 == 0)
			{
				if (DS1302_Time[2] > 29) {DS1302_Time[2] = 1;}
			}
			else
			{
				if (DS1302_Time[2] > 28) {DS1302_Time[2] = 1;}
			}
		}

		if (DS1302_Time[3] > 23) {DS1302_Time[3] = 0;} // Hour
		if (DS1302_Time[4] > 59) {DS1302_Time[4] = 0;} // Minute
		if (DS1302_Time[5] > 59) {DS1302_Time[5] = 0;} // Second
	}
	if(KeyNum == 4)
	{
		DS1302_Time[TimeSetSelect] --;
		
		// Fix underflow
		if (DS1302_Time[0] < 0) {DS1302_Time[0] = 99;} // Year
		if (DS1302_Time[1] < 1) {DS1302_Time[1] = 12;} // Month
		// Date Special check
			// Big Month
		if (DS1302_Time[1] == 1 || DS1302_Time[1] == 3 ||
			DS1302_Time[1] == 5 || DS1302_Time[1] == 7 ||
			DS1302_Time[1] == 8 || DS1302_Time[1] == 10 ||
			DS1302_Time[1] == 12)
		{
			if (DS1302_Time[2] < 1) {DS1302_Time[2] = 31;} 
			if (DS1302_Time[2] > 31) {DS1302_Time[2] = 1;} // Need check overflow too
		}
			// Small Month
		else if (DS1302_Time[1] == 4 || DS1302_Time[1] == 6 ||
				 DS1302_Time[1] == 9 || DS1302_Time[1] == 11)
		{
			if (DS1302_Time[2] < 1) {DS1302_Time[2] = 30;} 
			if (DS1302_Time[2] > 30) {DS1302_Time[2] = 1;} // Need check overflow too
		}
			// Feb
		else if (DS1302_Time[1] == 2)
		{
			if (DS1302_Time[0] % 4 == 0)
			{
				if (DS1302_Time[2] < 1) {DS1302_Time[2] = 29;}
				if (DS1302_Time[2] > 29) {DS1302_Time[2] = 1;} // Need check overflow too BUG
			}
			else
			{
				if (DS1302_Time[2] < 1) {DS1302_Time[2] = 28;}
				if (DS1302_Time[2] > 28) {DS1302_Time[2] = 1;} // Need check overflow too
			}
		}

		if (DS1302_Time[3] < 0) {DS1302_Time[3] = 23;} // Hour
		if (DS1302_Time[4] < 0) {DS1302_Time[4] = 59;} // Minute
		if (DS1302_Time[5] < 0) {DS1302_Time[5] = 59;} // Second
	}
	
	
	// Refresh screen
		// Year
	if(TimeSetSelect == 0 && TimeSetFlashFlag == 1){LCD_ShowString(1, 1, "  ");} // Flash
	else{LCD_ShowNum(1, 1, DS1302_Time[0], 2);} // Show
		// Month
	if(TimeSetSelect == 1 && TimeSetFlashFlag == 1){LCD_ShowString(1, 4, "  ");} // Flash
	else{LCD_ShowNum(1, 4, DS1302_Time[1], 2);} // Show
		// Date
	if(TimeSetSelect == 2 && TimeSetFlashFlag == 1){LCD_ShowString(1, 7, "  ");} // Flash
	else{LCD_ShowNum(1, 7, DS1302_Time[2], 2);} // Show
	
	// Hour
	if(TimeSetSelect == 3 && TimeSetFlashFlag == 1){LCD_ShowString(2, 1, "  ");} // Flash
	else{LCD_ShowNum(2, 1, DS1302_Time[3], 2);} // Show
		// Minute
	if(TimeSetSelect == 4 && TimeSetFlashFlag == 1){LCD_ShowString(2, 4, "  ");} // Flash
	else{LCD_ShowNum(2, 4, DS1302_Time[4], 2);} // Show
		// Second
	if(TimeSetSelect == 5 && TimeSetFlashFlag == 1){LCD_ShowString(2, 7, "  ");} // Flash
	else{LCD_ShowNum(2, 7, DS1302_Time[5], 2);} // Show

	LCD_ShowNum(2, 10, TimeSetSelect, 2);
	LCD_ShowNum(2, 13, TimeSetFlashFlag, 2);
}

void main()
{
	LCD_Init();
	DS1302_Init();
	Timer0Init();
	LCD_ShowString(1, 1, "  -  -  ");
	LCD_ShowString(2, 1, "  :  :  ");
	DS1302_SetTime();

	while(1)
	{
		// Read Key and Switch Mode when Pressed first bottom
		KeyNum = Key();
		if (KeyNum == 1)
		{
			if (MODE == 0) {MODE = 1; TimeSetSelect = 0;} // Do this so start from beginning
			else if(MODE == 1) {MODE = 0; DS1302_SetTime();} // Set Time on Exit
		}
		switch (MODE)
		{
			case 0: TimeShow(); break;
			case 1: TimeSet(); break;
		}
	}
}


/**
 * @brief Interupt timer switch between 0 and1 in 1 sec for flagging flashing rate
 * @param None
 * @retval None
 */
void Timer0_Routine(void) interrupt 1
{
	static unsigned int T0Count; // Static is not destroyed
	// Fix the initialization back
	TL0 = 0x66;		//Initial timer value
	TH0 = 0xFC;		//Initial timer value
	
	T0Count ++;
	if (T0Count >= 500) // 1s
	{
		T0Count = 0;
		TimeSetFlashFlag = !TimeSetFlashFlag; // Flip flashing flag 0, 1
	}
}