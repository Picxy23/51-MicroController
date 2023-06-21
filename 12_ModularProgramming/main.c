#include <REGX52.H>
#include "Delay.h"
#include "Nixie.h"

void main()
{
	while(1)
	{
		Nixie(1, 3);
		Nixie(2, 2);
		Nixie(3, 1);
	}
}