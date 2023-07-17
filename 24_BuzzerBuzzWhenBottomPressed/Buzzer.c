#include <REGX52.H>
#include <INTRINS.H>
#include "Delay.h"

sbit Buzzer = P2^5; //Buzzer IO port


/**
 * @brief Buzzer private delay function of 500us
 * @param None
 * @retval None
 */
void Buzzer_Delay500us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 227;
	while (--i);
}


/**
 * @brief Buzzer buzz for ms seconds
 * @param[in] ms Time of duration
 * @retval None
 */
void Buzzer_Time(unsigned int ms)
{
		unsigned int i;
		for (i = 0; i < ms * 2; i ++) // *3 to make 500us to 1ms
		{
			Buzzer = !Buzzer;
			Buzzer_Delay500us(); // 500us, 1000Hz
		}
}