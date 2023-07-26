#include <REGX52.H>

void Int0_Init()
{
	// External Interrupt
	IT0 = 1; // GO down Trigger
	IE0 = 0; // Clear Intterrupt flag
	EX0 = 1; // Enable Single
	EA = 1; // Enable All
	PX0 = 1; // High Priority

}

/*
// Interrupt
void Int0_Routine() interrupt 0
{
	Num ++;
}
*/