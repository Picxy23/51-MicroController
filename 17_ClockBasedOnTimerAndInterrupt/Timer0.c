#include <REGX52.H>

/**
 * @brief Initialization of Timer 0, 1ms
 * @param None
 * @retval None
 */
void Timer0Init()
{
	// Set up TMOD
	// x,x,x,x;  Gate, C/T, M1, M0
	// 0,0,0,0;  0,  , 0  , 0 , 1 
	// 0000 0001
		//TMOD = 0x01;
	TMOD = TMOD&0xF0; // Clear the low 4-bit of T Mode, high 4 stay same
	TMOD = TMOD|0X01; // Change low 4 to 0001
	
	// Set up TCON (Can be done by bit)
	TF0 = 0; // Clear the overflow flag
	TR0 = 1; // Allow the counter to work
	// No need to set up IE0 and IT0 because OR gate
	
	// Pulse Counter, how long to 1s
	// Counter allow 0 ~ 65535
	// Every 1us count +1
	// Max time can count is 65535us
	// Initialy we set counter 64535 => 1000us = 1ms
	// So
	
	TL0 = 0x66;		//Initial timer value
	TH0 = 0xFC;		//Initial timer value
	
	// Interupt
	ET0 = 1;
	EA = 1;
	PT0 = 0;
}


// Template for 1s
/*
// When overflow flagged, jump to this
// When finished here, jump back
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
		// Do Something
	}
}
*/