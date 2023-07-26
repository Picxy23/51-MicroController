#include <REGX52.H>
#include "Timer0.h"
#include "Int0.h"

unsigned int IR_Time;
unsigned char IR_State;
// 0 FREE Mode, Recieve Down -> State 1
// 1 SEARCHING for START/REPEAT, Start Timer -> State 2/3
// 2 START, Decode Information 32 bits
	// 32 Times Read Information -> Data (With Pointer) -> Chceck -> Data Flag -> State 0
// 3 REPEAT, Set Flag -> State 0

unsigned char IR_Data[4]; // 4 represent 32 bits
unsigned char IR_pData; // Position

unsigned char IR_DataFlag; // Finish Flag
unsigned char IR_RepeatFlag; 

unsigned char IR_Address;
unsigned char IR_Command;

void IR_Init()
{
	Timer0_Init();
	Int0_Init();
}

unsigned char IR_GetDataFlag()
{
	if (IR_DataFlag)
	{
		IR_DataFlag = 0;
		return 1;
	}
	
	return 0;
}

unsigned char IR_GetRepeatFlag()
{
	if (IR_RepeatFlag)
	{
		IR_RepeatFlag = 0;
		return 1;
	}
	return 0;
}

unsigned char IR_GetAddress()
{
	return IR_Address;
}

unsigned char IR_GetCommand()
{
	return IR_Command;
}

// Interrupt, Detected Down
void Int0_Routine() interrupt 0
{
	// Free Mode
	if (IR_State == 0) 
	{
		Timer0_SetCounter(0);
		Timer0_Run(1);
		IR_State = 1;
	}
	// SEARCHING for START/REPEAT
	else if(IR_State == 1)
	{
		IR_Time = Timer0_GetCounter();
		Timer0_SetCounter(0);
		
		// START Signal
		if(IR_Time > 12442 - 500 && IR_Time < 12442 + 500) 
		{
			IR_State = 2;
		}
		// REPEAT Signal
		else if (IR_Time > 10368 - 500 && IR_Time < 10368 + 500)
		{
			IR_RepeatFlag = 1;
			Timer0_Run(0); // Stop Timer
			IR_State = 0; // FREE
		}
		// ERROR
		else
		{
			IR_State = 1; // SEARCHING for START/REPEAT
		}
	}
	// START Signal -READ DATA
	else if(IR_State == 2)
	{
		// Take Time Out And Clear
		IR_Time = Timer0_GetCounter();
		Timer0_SetCounter(0);
		
		// 0
		if(IR_Time > 1032 - 500 && IR_Time < 1032 + 500) 
		{
			// Clear this to 0
			// IR_pData / 8 select which item in Array
			// IR_pData % 8 Select Bit in item
			IR_Data[IR_pData / 8] &= ~(0x01 << IR_pData % 8);
			IR_pData ++;
		}
		// 1
		else if(IR_Time > 2074 - 500 && IR_Time < 2074 + 500) 
		{
			// Clear this to 0
			// IR_pData / 8 select which item in Array
			// IR_pData % 8 Select Bit in item
			IR_Data[IR_pData / 8] |= (0x01 << IR_pData % 8);
			IR_pData ++;
		}
		// ERROE
		else
		{
			IR_pData = 0;
			IR_State = 1;
		}
		// Finish Collecting
		if (IR_pData >= 32)
		{
			IR_pData = 0;
			// Verify Data
			if ((IR_Data[0] == ~IR_Data[1]) && (IR_Data[2] == ~IR_Data[3]))
			{
				IR_Address = IR_Data[0];
				IR_Command = IR_Data[2];
				IR_DataFlag = 1;
			}
			Timer0_Run(0);
			IR_State = 0; // Return to Idle
		}
	}
}
