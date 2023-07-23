#ifndef __ONEWIRE_H__
#define __ONEWIRE_H__

unsigned char OneWire_Init();
void OneWire_SendBit(unsigned char Bit);
unsigned char OneWire_RecieveBit();
void OneWire_SendByte(unsigned char Byte);
unsigned char OneWire_RecieveByte();

#endif
 