#include <REGX52.H>
#include "OneWire.h"

#define DS18B20_SKIP_ROM			0xCC
#define DS18B20_CONVERT_T			0x44
#define DS18B20_READ_SCRATCHPAD		0xBE

void DS18B20_ConvertT()
{
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIP_ROM); 
	OneWire_SendByte(DS18B20_CONVERT_T); 
}

float DS18B20_ReadT()
{
	unsigned char TLSB, TMSB;
	int Temp = 0;
	float T = 0;
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIP_ROM); 
	OneWire_SendByte(DS18B20_READ_SCRATCHPAD);
	// Recieve info from SUB 
	TLSB = OneWire_RecieveByte();
	TMSB = OneWire_RecieveByte();
	
	Temp = (TMSB << 8) | TLSB; // Force convert 2 byte to signed int
	T = Temp/16.0; // Shift DATA left 4 times, 2^4 = 16,  check note
	
	return T;
}