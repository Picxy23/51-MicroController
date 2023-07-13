#include <REGX52.H>

/**
 * @brief COM Initialization
 * @param None
 * @retval None
 */
void UART_Init()
{
	// Serical Control
	SCON = 0x50; //// Emable recieve
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
	
	//// Turn Interrupt on
	EA = 1;
	ES = 1;
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
	TI = 0; // Reset TI
}



// Use interrupt and retain data use in Main.c
/**
 * @brief Recieve Byte from Computer Side
 * @param None
 * @retval None
 */
//void UART_Routine() interrupt 4
//{
//	if(RI == 1)
//	{
//		P2 = ~SBUF;
//		UART_SendByte(SBUF);
//		RI = 0; // reset RI 
//	}
//}
