#include <REGX52.H>
#include "Delay.h"

unsigned char NixieTable[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7c,0x39, 0x5E, 0x79, 0x71, 0x00, 0x40};

// Skip [0], match later code, show nothing
unsigned char Nixie_Buf[9] = {0, 16, 16, 16, 16, 16, 16, 16, 16}; // All 0


void Nixie_SetBuf(unsigned char Location, unsigned char Number)
{
	Nixie_Buf[Location] = Number;
}

void Nixie_Scan(unsigned char Location, unsigned char Number)
{
	P0 = 0x00; // Clear P0 register
	switch(Location)
	{
		case 1: P2_4 = 1; P2_3 = 1; P2_2 = 1; break;
		case 2: P2_4 = 1; P2_3 = 1; P2_2 = 0; break;
		case 3: P2_4 = 1; P2_3 = 0; P2_2 = 1; break;
		case 4: P2_4 = 1; P2_3 = 0; P2_2 = 0; break;
		case 5: P2_4 = 0; P2_3 = 1; P2_2 = 1; break;
		case 6: P2_4 = 0; P2_3 = 1; P2_2 = 0; break;
		case 7: P2_4 = 0; P2_3 = 0; P2_2 = 1; break;
		case 8: P2_4 = 0; P2_3 = 0; P2_2 = 0; break;		
	}
	P0 = NixieTable[Number];
	// Since we call this every 2ms in timer interrupt
	// This would act like as a 2ms delay here
}

void Nixie_Loop()
{
	// Loop from 1st to 8th display. with 2ms delay 
	static unsigned char i = 1;
	Nixie_Scan(i, Nixie_Buf[i]); // Turn on Nixie
	i ++;
	if (i >= 9){i = 1;} 
}
