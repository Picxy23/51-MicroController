#include <REGX52.H>

void main()
{
//	P2 = 0xFE;
//	P2_0 = 0; Only accesss one register
	while(1)
		{
			if (P3_1 == 0 || P3_0 == 0)
			{
				P2_0 = 0; // On
			}
			else
			{
				P2_0 = 1; // OFF
			}
		}
}
