#include <REGX52.H>

/**
 * @brief Initialization of Timer 0, 1ms
 * @param None
 * @retval None
 */
void Timer0_Init()
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
	TR0 = 0; // COUNTER NOT WORK
	// No need to set up IE0 and IT0 because OR gate
	
	// Pulse Counter, how long to 1s
	// Counter allow 0 ~ 65535
	// Every 1us count +1
	// Max time can count is 65535us
	// Initialy we set counter 64535 => 1000us = 1ms
	// So
	
	TL0 = 0;		//Initial timer value
	TH0 = 0;		//Initial timer value
}


void Timer0_SetCounter(unsigned int Value)
{
	TH0 = Value / 256;
	TL0 = Value % 256;
}

unsigned int Timer0_GetCounter()
{
	return (TH0 << 8) | TL0;
}

void Timer0_Run(unsigned char Flag)
{
	TR0 = Flag;
}