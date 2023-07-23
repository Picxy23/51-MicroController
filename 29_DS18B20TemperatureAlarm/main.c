#include <REGX52.H>
#include "LCD1602.h"
#include "DS18B20.h"
#include "Delay.h"
#include "AT24C02.h"
#include "Key.h"
#include "Timer0.h"


float T, TShow;
char TLow, THigh;
unsigned char KeyNum;

void main()
{
	DS18B20_ConvertT();
	Delay(1000);
	// Set Defalt LOW HIGH
	THigh = AT24C02_ReadByte(0);
	TLow = AT24C02_ReadByte(1);
	if (THigh > 125 || TLow < -55 || THigh <= TLow)
	{
		THigh = 20;
		TLow = 15;
	}
	
	LCD_Init();
	LCD_ShowString(1, 1, "T:");
	LCD_ShowString(2, 1, "TH:");
	LCD_ShowString(2, 9, "TL:");	
	LCD_ShowSignedNum(2, 4, THigh, 3);
	LCD_ShowSignedNum(2, 12, TLow, 3);
	Timer0_Init();
	
	while(1)
	{	
		KeyNum = Key();
		/*Read And Show Temp*/
		DS18B20_ConvertT();
		T = DS18B20_ReadT();
		
		// Show Sign
		if (T < 0)
		{
			LCD_ShowChar(1, 3, '-');
			TShow = -T;
		}
		else
		{
			LCD_ShowChar(1, 3, '+');
			TShow = T;
		}
		// Show Value
		LCD_ShowNum(1, 4, TShow, 3);
		LCD_ShowChar(1, 7, '.');
		LCD_ShowNum(1, 8, (unsigned long)(TShow*100)%100, 2);
		
		/*MinMax Temp Decide and Display*/
		if (KeyNum)
		{
			if (KeyNum == 1) {THigh ++; if(THigh > 125){THigh = 125;}} // Check Max
			if (KeyNum == 2) {THigh --; if(THigh <= TLow){THigh ++;}} // Bigger than Min, redo
			if (KeyNum == 3) {TLow ++;  if(TLow >= THigh){TLow --;}} // Smaller than Max, redo
			if (KeyNum == 4) {TLow --;  if(TLow < -55){TLow = -55;}} // Check Min	
			// Display update
			LCD_ShowSignedNum(2, 4, THigh, 3);
			LCD_ShowSignedNum(2, 12, TLow, 3);
			
			// Save to AT24C02
			AT24C02_WriteByte(0, THigh);
			Delay(5);
			AT24C02_WriteByte(1, TLow);
			Delay(5);
		}
		
		/*Show Warning*/
		if (T > THigh)
		{
			LCD_ShowString(1, 13, "OV:H");
		}
		else if (T < TLow)
		{
			LCD_ShowString(1, 13, "OV:L");
		}
		else
		{
			LCD_ShowString(1, 13, "    ");
		}
		
	}
}

void Timer0_Routine(void) interrupt 1
{
	static unsigned int T0Count; // Static is not destroyed
	// Fix the initialization back
	TL0 = 0x66;		//Initial timer value
	TH0 = 0xFC;		//Initial timer value
	
	T0Count ++;
	if (T0Count >= 20) // 20ms per
	{
		T0Count = 0;
		Key_Loop();
	}
}