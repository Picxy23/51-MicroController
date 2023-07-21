#include <REGX52.H>
#include <INTRINS.H>

sbit OneWire_DQ = P3^7;

unsigned char OneWire_Init()
{
	unsigned char i;
	unsigned char AckBit;
	OneWire_DQ = 1; // Make into 1 first
	
	// DOM pull down DQ and release
	OneWire_DQ = 0; // Enter Init
		
	// Delay 500us(480)
	_nop_();
	i = 227;
	while (--i);
	
	OneWire_DQ = 1;
	
	// SUB Pull DOwn And Release
	// Delay 70 us
	_nop_();
	i = 29;
	while (--i);
	
	AckBit = OneWire_DQ; // Store Ack
	
	// Delay 500us(480) till cycle complete
	_nop_();
	i = 227;
	while (--i);
	
	return AckBit;
}

void OneWire_SendBit(unsigned char Bit)
{
	unsigned char i;
	OneWire_DQ = 0; // Restore, Begin
	
	// Delay 14 us - 4 = 10 // Call function takes 4 us
	_nop_();
	i = 3;
	while (--i);
	
	// IF 
	OneWire_DQ = Bit; // Dependingon input, let go or not
	// Decide what to send
	
	// Delay 54us - 4 = 50
	_nop_();
	i = 22;
	while (--i);
	
	OneWire_DQ = 1;
}


unsigned char OneWire_RecieveBit()
{
	unsigned char Bit;
	unsigned char i;
	OneWire_DQ = 0; // Init
	
	// Delay 5us (9us)
	_nop_();
	i = 1;
	while (--i);
	
	OneWire_DQ = 1;
	
	// Delay 5us (9us)
	_nop_();
	i = 1;
	while (--i);
	
	// Read
	Bit = OneWire_DQ;
	
	// Delay 54us - 4 = 50
	_nop_();
	i = 22;
	while (--i);
	
	// OneWire_DQ = 1; SUB will do this
	
	return Bit;
}

void OneWire_SendByte(unsigned char Byte)
{
	unsigned char i;
	for (i = 0; i < 8; i ++)
	{
		OneWire_SendBit(Byte&(0x01 << i));
	}
}

unsigned char OneWire_RecieveByte()
{
		unsigned char i, Byte = 0x00;
	for (i = 0; i < 8; i ++)
	{
		if (OneWire_RecieveBit()){Byte |= (0x01 << i);}
	}
	
	return Byte;
}
