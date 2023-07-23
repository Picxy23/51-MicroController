#include <REGX52.H>
#include "I2C.h"

// Writec Address
#define AT24C02_ADDRESS		0xA0


/**
 * @brief Write a byte into AT24C02
 * @param[in] WordAddress Where to write
 * @param[in] Data What to write
 * @retval None
 */
void AT24C02_WriteByte(unsigned char WordAddress, Data)
{
	I2C_Start();
	
	I2C_SendByte(AT24C02_ADDRESS);
	I2C_RecieveAck();
	
	I2C_SendByte(WordAddress);
	I2C_RecieveAck();
	
	I2C_SendByte(Data);
	I2C_RecieveAck();
	
	I2C_Stop();
}


/**
 * @brief Read a byte from AT24C02
 * @param[in] WordAddress Where to get data from
 * @retval Data Data retrieved
 */
unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
	unsigned char Data;
	
	// Send info
	I2C_Start();
	
	I2C_SendByte(AT24C02_ADDRESS);
	I2C_RecieveAck();
	
	I2C_SendByte(WordAddress);
	I2C_RecieveAck();
	
	// Second Part
	I2C_Start();
	
	I2C_SendByte(AT24C02_ADDRESS|0x01); // Recieving Address
	I2C_RecieveAck();
	
	Data = I2C_RecieveByte();
	I2C_SendAck(1); //Dont send anymore
	
	I2C_Stop();
	
	return Data;
}