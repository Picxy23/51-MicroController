#include <REGX52.H>
#include "Timer0.h"
#include "Key.h"
#include <INTRINS.H>

unsigned char KeyNumber, LEDMod;

void main()
{
	P2 = 0xFE;
	Timer0Init();
	while(1)
	{
		KeyNumber  = Key();
		if (KeyNumber)
		{
			if (KeyNumber == 1) // Mode can be 0 or 1
			{
				LEDMod ++;
				if (LEDMod >= 2)
					LEDMod = 0;
			}
			// Go to interrupt code
		}
	}
}



// When overflow flagged, jump to this
// When finished here, jump back
void Timer0_Routine(void) interrupt 1
{
	static unsigned int T0Count; // Static is not destroyed
	// Fix the initialization back
	TL0 = 0x66;		//Initial timer value
	TH0 = 0xFC;		//Initial timer value
	
	T0Count ++;
	if (T0Count >= 500) // 0.5s
	{
		T0Count = 0;
		if (LEDMod == 0){P2 = _crol_(P2, 1);}
		if (LEDMod == 1){P2 = _cror_(P2, 1);}
	}
}