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
 * @brief MatrixLED Initialization
 * @param None
 * @retval None
 */
void MatrixLED_Init()
{
	SCK = 0; // Initially this is zero
	RCK = 0;
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
