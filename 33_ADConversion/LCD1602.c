#include <REGX52.H>
#include <INTRINS.H>

sbit LCD_RS = P2^6;
sbit LCD_RW = P2^5;
sbit LCD_E  = P2^7;
#define LCD_DataPort	P0

void LCD_Delay()		//@11.0592MHz, 1ms
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}


void LCD_WriteCommand(unsigned char Command)
{
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_DataPort = Command;
	LCD_E = 1;
	LCD_Delay();
	LCD_E = 0;
	LCD_Delay();
}

void LCD_WriteData(unsigned char Data)
{
	LCD_RS = 1; // Only Difference here
	LCD_RW = 0;
	LCD_DataPort = Data;
	LCD_E = 1;
	LCD_Delay();
	LCD_E = 0;
	LCD_Delay();
}

void LCD_Init()
{
	LCD_WriteCommand(0x38); // Mode: 8 Pins, 2 Rows, 5*7 Res
	LCD_WriteCommand(0x0C); // Display on, Cursor off, Flashing off
	LCD_WriteCommand(0x06); // After write, Display unchange, Pointer ++
	LCD_WriteCommand(0x01); // Clear screen
}


void LCD_SetCursor(unsigned char Line, unsigned char Column)
{
	if (Line == 1)
		LCD_WriteCommand((Column - 1)|0x80); // Display Address
	else
		LCD_WriteCommand((Column - 1)|0x80 + 0x40); // Display Address	
}

void LCD_ShowChar(unsigned char Line, unsigned char Column, unsigned char Char)
{
	// Set Location
	LCD_SetCursor(Line, Column);
	
	LCD_WriteData(Char);
}

void LCD_ShowString(unsigned char Line, unsigned char Column, unsigned char *String)
{
	unsigned char i;
	
	// Set Location
	LCD_SetCursor(Line, Column);
	
	for (i = 0; String[i] != '\0'; i ++)
	{
		LCD_WriteData(String[i]);	// Auto move to next spot by setting
	}
}

int LCD_Pow(int X, int Y)
{
//	unsigned int i;
//	int Result;
//	for (i = 0; i < Y; i ++)
//	{
//		Result *= X;
//	}
//	
//	return Result;
	
// Recursion for fun
	if (Y == 0)
		return 1;
	else if (Y == 1)
		return X;
	
	return X * LCD_Pow(X, Y - 1);
}

void LCD_ShowNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length)
{
	unsigned char i;
	
	// Set Location
	LCD_SetCursor(Line, Column);
	
	for (i = Length; i > 0; i --)
	{
		LCD_WriteData('0' + Number / LCD_Pow(10, i - 1) % 10); //See why on note
	}
}

void LCD_ShowSignedNum(unsigned char Line, unsigned char Column, int Number, unsigned char Length)
{
	unsigned char i;
	unsigned int Number1; // This is added for -Numbr might cause overflow int type
	// Set Location
	LCD_SetCursor(Line, Column);

	// Check +-
	if (Number >= 0)
	{
		LCD_WriteData('+');
		Number1 = Number;
	}
	else
	{
		LCD_WriteData('-');
		Number1 = -Number;
	}
	
	for (i = Length; i > 0; i --)
	{
		LCD_WriteData('0' + Number1 / LCD_Pow(10, i - 1) % 10); //See why on note
	}

}

void LCD_ShowHexNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length)
{
	unsigned char i;
	unsigned char SingleNumber;
	
	// Set Location
	LCD_SetCursor(Line, Column);
	
	for (i = Length; i > 0; i --)
	{
		SingleNumber = Number / LCD_Pow(16, i - 1) % 16;
		if (SingleNumber < 10)
		{
			LCD_WriteData('0' + SingleNumber); 
		}
		else
		{
			LCD_WriteData('A' + (SingleNumber % 10));
		}
	}
}

void LCD_ShowBinNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length)
{
	unsigned char i;
	
	// Set Location
	LCD_SetCursor(Line, Column);
	
	for (i = Length; i > 0; i --)
	{
		LCD_WriteData('0' + Number / LCD_Pow(2, i - 1) % 2); //See why on note
	}

}
