#include <iostream>

#include "adder.h"
#include "multiplier.h"

uint32_t multiplier(uint32_t a, uint32_t b)
{
	uint32_t result = 0;
	
	for (int i = 0; i < 32; i++)
	{
		if (b >> i & 1)
		{
			result = adder(result, a << i);
		}
	}
	return result;
}
