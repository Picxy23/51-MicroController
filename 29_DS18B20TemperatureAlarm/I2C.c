#include <REGX52.H>

sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;

/**
 * @brief I2C Begin
 * @param None 
 * @retval None
 */
void I2C_Start()
{
	// Refer to note
	I2C_SDA = 1; // SDA can be 1/0, so make sure it is 1
	I2C_SCL = 1; // End of every sentence is 0 so need to manual set 1
	
	I2C_SDA = 0; 
	I2C_SCL = 0;

}

/**
 * @brief I2C Stop
 * @param None
 * @retval None
 */
void I2C_Stop()
{
	// Refer to note
	I2C_SDA = 0; // SDA can be 1/0, so make sure it is 0
	// No need to set SCL because every word ends with 0 SCL
	
	I2C_SCL = 1;
	I2C_SDA = 1; 
	
}

/**
 * @brief I2C Send one byte to sub
 * @param[in] Byte Byte to be send
 * @retval None
 */
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	
	for (i = 0; i < 8; i ++)
	{
		// Write one bit
		I2C_SDA = Byte&(0x80 >> i);
	
		I2C_SCL = 1;
		// No need delay, max is 1000 kHz
		// Write time is 5ms, however
		I2C_SCL = 0;
	}
}

/**
 * @brief I2C recieve one byte from sub
 * @param None
 * @retval Byte the byte recieved by dom
 */
unsigned char I2C_RecieveByte()
{
	unsigned char Byte = 0x00;
	unsigned char i;
	I2C_SDA = 1; // dom release I2C
	
	for (i = 0; i < 8; i ++)
	{
		// Read one bit
		I2C_SCL = 1;
		if(I2C_SDA){Byte|=(0x80 >> i);}
		I2C_SCL = 0;
	}
	return Byte;
}

/**
 * @brief I2C Send Send Aknowledgment
 * @param[in] What to send, 0/1, yes(0) or no(1)
 * @retval None
 */
void I2C_SendAck(unsigned char AckBit)
{
	I2C_SDA = AckBit;
	
	I2C_SCL = 1;
	I2C_SCL = 0;
}

/**
 * @brief I2C dom recieve Aknowledgment from sub
 * @param None 
 * @retval AckBit Aknowledment sent by sub
 */
unsigned char I2C_RecieveAck()
{
	unsigned char AckBit;
	I2C_SDA = 1; // Master release
	
	// Recieve from sub
	I2C_SCL = 1;
	AckBit = I2C_SDA; // one bit to 8bit conversion
	I2C_SCL = 0;
	
	return AckBit;
}