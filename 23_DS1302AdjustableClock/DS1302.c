#include <REGX52.H>

// Define Register
sbit DS1302_SCLK = P3^6;
sbit DS1302_IO = P3^4;
sbit DS1302_CE = P3^5;


// These Address are for write, conde in read has |= 0x01 to make them into read
#define DS1302_SECOND		0x80
#define DS1302_MINUTE		0x82
#define DS1302_HOUR			0x84
#define DS1302_DATE			0x86
#define DS1302_MONTH		0x88
#define DS1302_DAY			0x8A
#define DS1302_YEAR			0x8C
#define DS1302_WP			0x8E

unsigned char DS1302_Time[] = {23, 7, 16, 12, 59, 55, 7};

/**
 * @brief Initialize DS1302, put all Register to 0 
 * @param None
 * @retval None
 */
void DS1302_Init()
{
	DS1302_CE = 0;
	DS1302_SCLK = 0;
}


/**
 * @brief Write a Byte into the DS1302 based the time diagram
 * @param Command: Specify which register to write to
 * @param Data: Specify what to write
 * @retval None
 */
void DS1302_WriteByte(unsigned char Command, Data)
{
	unsigned char i;
	DS1302_CE = 1; // Enable
	
	// Input Byte Command
	for (i = 0; i < 8; i ++)
	{
	// Input one bit
	DS1302_IO = Command&(0x01<<i); // 0000 0001
	// Move Clock
	DS1302_SCLK = 1; // May need a dalay is Hz is high
	DS1302_SCLK = 0;
	}	
	
	
	// Input Byte Data
	for (i = 0; i < 8; i ++)
	{
	// Input one bit
	DS1302_IO = Data&(0x01<<i); // 0000 0001
	// Move Clock
	DS1302_SCLK = 1; // May need a dalay is Hz is high
	DS1302_SCLK = 0;
	}	
	
	DS1302_CE = 0; // Diable
}

/**
 * @brief Read a Byte of Data from DS1302
 * @param Command: Specify where the data should be read
 * @retval unsigned char: The Byte of data in DS1302
 */
unsigned char DS1302_ReadByte(unsigned char Command)
{
	// This has one less period
	unsigned char i, Data = 0x00;
	Command |= 0x01; // Make sure it is read
	DS1302_CE = 1; // Enable
	
	// Input Byte Command
	for (i = 0; i < 8; i ++)
	{
	// Input one bit
	DS1302_IO = Command&(0x01<<i); // 0000 0001
	// Move Clock
	DS1302_SCLK = 0; // !!!! This make clock end in middle of down up
	DS1302_SCLK = 1; 
	}
	
	// Give control to DS1302, Load Data in to return
	for (i = 0; i < 8; i ++)
	{
		DS1302_SCLK = 1; // Althuogh Doubled, this order make sense
		DS1302_SCLK = 0;
		if (DS1302_IO){Data = Data|(0x01<<i);}
	}
	
	DS1302_CE = 0; // Disable
	DS1302_IO = 0;
	return Data;
}

/**
 * @brief Set the tyme of DS1302 using the time array
 * @param None
 * @retval None
 */
void DS1302_SetTime()
{
	DS1302_WriteByte(DS1302_WP, 0x00); // Disable Write Protection
	DS1302_WriteByte(DS1302_YEAR, DS1302_Time[0]/10*16 + DS1302_Time[0]%10); // DEC to BCD
	DS1302_WriteByte(DS1302_MONTH, DS1302_Time[1]/10*16 + DS1302_Time[1]%10);
	DS1302_WriteByte(DS1302_DATE, DS1302_Time[2]/10*16 + DS1302_Time[2]%10);
	DS1302_WriteByte(DS1302_HOUR, DS1302_Time[3]/10*16 + DS1302_Time[3]%10);
	DS1302_WriteByte(DS1302_MINUTE, DS1302_Time[4]/10*16 + DS1302_Time[4]%10);
	DS1302_WriteByte(DS1302_SECOND, DS1302_Time[5]/10*16 + DS1302_Time[5]%10);
	DS1302_WriteByte(DS1302_DAY, DS1302_Time[6]/10*16 + DS1302_Time[6]%10);
	DS1302_WriteByte(DS1302_WP, 0x80); // Enable Write Protection
}

/**
 * @brief Read the time in BCD to DEC from DS1302 into the Time array
 * @param None
 * @retval None
 */
void DS1302_ReadTime()
{
	unsigned char Temp;
	Temp = DS1302_ReadByte(DS1302_YEAR);
	DS1302_Time[0] = Temp / 16 * 10 + Temp % 16; // BCD to DEC
	Temp = DS1302_ReadByte(DS1302_MONTH);
	DS1302_Time[1] = Temp / 16 * 10 + Temp % 16; 
	Temp = DS1302_ReadByte(DS1302_DATE);
	DS1302_Time[2] = Temp / 16 * 10 + Temp % 16; 
	Temp = DS1302_ReadByte(DS1302_HOUR);
	DS1302_Time[3] = Temp / 16 * 10 + Temp % 16; 
	Temp = DS1302_ReadByte(DS1302_MINUTE);
	DS1302_Time[4] = Temp / 16 * 10 + Temp % 16; 
	Temp = DS1302_ReadByte(DS1302_SECOND);
	DS1302_Time[5] = Temp / 16 * 10 + Temp % 16; 
	Temp = DS1302_ReadByte(DS1302_DAY);
	DS1302_Time[6] = Temp / 16 * 10 + Temp % 16; 
}