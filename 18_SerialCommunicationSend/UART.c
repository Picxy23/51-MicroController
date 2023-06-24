#include <REGX52.H>

/**
 * @brief COM Initialization
 * @param None
 * @retval None
 */
void UART_Init()
{
	// Serical Control
	SCON = 0x40;
	// Power
	PCON |= 0x80; // Double B rate(For acdcuracy)
	
	// Timer 1
	// Set up TMOD
	TMOD = TMOD&0x0F; 
	TMOD = TMOD|0X20;  // 8 bit auto reload
	
	TR1 = 1;
	TL1 = 0xF4;		//Initial timer value
	TH1 = 0xF4;		//Set reload value
	
	// Interupt
	ET1 = 0;
}


/**
 * @brief Send Byte to Computer Side
 * @param Byte to be send
 * @retval None
 */
void UART_SendByte(unsigned char Byte)
{
	SBUF = Byte; // Put suff into buffer
	while (TI == 0){} // Wait for flag
	TI = 0;
}