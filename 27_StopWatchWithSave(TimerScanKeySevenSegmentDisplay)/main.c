#include <REGX52.H>
#include "Timer0.h"
#include "Key.h"
#include "Nixie.h"
#include "Delay.h"
#include "AT24C02.h"

unsigned char KeyNum;
unsigned char Min, Sec, MiniSec;
unsigned char RunFlag;

void main()
{
	Timer0_Init();
	while(1)
	{
		// Get key		
		KeyNum = Key();
		// Start/stop
		if (KeyNum == 1)
		{RunFlag = !RunFlag;}
		// Reset
		if (KeyNum == 2)
		{
			Min = 0;
			Sec = 0;
			MiniSec = 0;
		}
		// Save to AT24C02
		if (KeyNum == 3)
		{
			AT24C02_WriteByte(0, Min);
			Delay(5);
			AT24C02_WriteByte(1, Sec);
			Delay(5);
			AT24C02_WriteByte(2, MiniSec);
			Delay(5);
		}
		// Read From AT24C02
		if (KeyNum == 4)
		{
			Min = AT24C02_ReadByte(0);
			Sec = AT24C02_ReadByte(1);
			MiniSec = AT24C02_ReadByte(2);
		}
		
		Nixie_SetBuf(1, Min/10);
		Nixie_SetBuf(2, Min%10);
		Nixie_SetBuf(3, 17);
		
		Nixie_SetBuf(4, Sec/10);
		Nixie_SetBuf(5, Sec%10);
		Nixie_SetBuf(6, 17);
		
		Nixie_SetBuf(7, MiniSec/10);
		Nixie_SetBuf(8, MiniSec%10);
	}
}

void Sec_Loop()
{
	if (RunFlag)
	{
		MiniSec ++;
		if (MiniSec >= 100)
		{
			MiniSec = 0;
			Sec ++;
			if (Sec >= 60)
			{
				Sec = 0;
				Min ++;
			}
			if (Min >= 60)
			{
				Min = 0;
			}
		}
	}
}


// When overflow flagged, jump to this
// When finished here, jump back
void Timer0_Routine(void) interrupt 1
{
	static unsigned int T0Count1, T0Count2, T0Count3; // Static is not destroyed
	// Fix the initialization back
	TL0 = 0x66;		//Initial timer value
	TH0 = 0xFC;		//Initial timer value
	
	// For Key
	T0Count1 ++;
	if (T0Count1 >= 20) // 20ms per
	{
		T0Count1 = 0;
		Key_Loop();
	}
	
	// For Nixie
	T0Count2 ++;
	if (T0Count2 >= 2) // 2ms per
	{
		T0Count2 = 0;
		Nixie_Loop();
	}
	
	// For MiniSec
	T0Count3 ++;
	if (T0Count3 >= 10) // 10ms per
	{
		T0Count3 = 0;
		Sec_Loop();
	}
	
	
}