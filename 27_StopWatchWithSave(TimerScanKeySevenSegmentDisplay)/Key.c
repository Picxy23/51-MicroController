#include <REGX52.H>
#include "Delay.h"

unsigned char Key_KeyNumber;

unsigned char Key()
{
	unsigned char Temp = 0; // Need to have a temp variable to allow clearing bottomNum after release
	Temp = Key_KeyNumber;
	Key_KeyNumber = 0;
	return Temp;
}


unsigned char Key_GetState()
{
	unsigned char KeyNumber = 0;
	
	if (P3_1 == 0){KeyNumber = 1;}
	if (P3_0 == 0){KeyNumber = 2;}
	if (P3_2 == 0){KeyNumber = 3;}
	if (P3_3 == 0){KeyNumber = 4;}
	
	return KeyNumber;
} 

void Key_Loop()
{
	static unsigned char NowState, LastState;
	LastState = NowState; // Push last sate to correct var
	NowState = Key_GetState(); // Get current state
	
	// Release key 1 here
	if (LastState == 1 && NowState == 0) 
	{Key_KeyNumber = 1;}
	// Release key 2 here
	if (LastState == 2 && NowState == 0) 
	{Key_KeyNumber = 2;}
	// Release key 3 here
	if (LastState == 3 && NowState == 0) 
	{Key_KeyNumber = 3;}
	// Release key 4 here
	if (LastState == 4 && NowState == 0) 
	{Key_KeyNumber = 4;}
}