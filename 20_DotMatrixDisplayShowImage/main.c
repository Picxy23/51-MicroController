#include <REGX52.H>
#include "Delay.h"

sbit RCK = P3^5; // RCLK
sbit SCK = P3^6; // SCLK
sbit SER = P3^4;
#define MATRIX_LED_PORT		P0


/**
 * @brief 74HC595 Write A Byte
 * @param Byte to be written
 * @retval None
 */
void _74HC595_WriteByte(unsigned char Byte)
{
	unsigned char i;
	for (i = 0; i < 8; i ++)
	{
		SER = Byte&(0x80>>i); // Not Zero then One & 1000 000, move 1 to right, devide by 2
		SCK = 1; // Move
		SCK = 0; // Reset
	}
	RCK = 1; RCK = 0; // Shift data into ports
}


/**
 * @brief LED Matrix show onw column of data
 * @param Column: column to be selected, range 0 - 7
 * @param Data: What to show on that column, Range 0 - 255, 1 is on 0 is off
 * @retval None
 */
void MatrixLED_ShowColumn(unsigned char Column, Data)
{
	_74HC595_WriteByte(Data);
	// First Column is 0
	MATRIX_LED_PORT = ~(0x80 >> Column); // Use this to determine which column
	Delay(1);
	MATRIX_LED_PORT = 0xFF; // Clear to prevent shading
}

void main()
{
	SCK = 0; // Initially this is zero
	RCK = 0;
	while(1)
	{
		MatrixLED_ShowColumn(0, 0x3C);
		MatrixLED_ShowColumn(1, 0x42);
		MatrixLED_ShowColumn(2, 0xA9);
		MatrixLED_ShowColumn(3, 0x85);
		MatrixLED_ShowColumn(4, 0x85);
		MatrixLED_ShowColumn(5, 0xA9);
		MatrixLED_ShowColumn(6, 0x42);
		MatrixLED_ShowColumn(7, 0x3C);
	}
}
