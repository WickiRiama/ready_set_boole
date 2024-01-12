#include <iostream>

#include "adder.h"

uint32_t adder(uint32_t a, uint32_t b)
{
	uint32_t result = 0;
	uint32_t tmp;
	uint32_t tmp_a;
	uint32_t tmp_b;
	uint32_t carry = 0;
	
	for (int i = 0; i < 32; i++)
	{
		tmp_a = a >> i & 1;
		tmp_b = b >> i & 1;

		tmp = tmp_a ^ tmp_b ^ carry;
		result = result ^ (tmp<<i);

		if (carry == 1)
			carry = tmp_a | tmp_b;
		else
			carry = tmp_a & tmp_b;
	}
	if (carry == 1)
		std::cerr << "Warning: overflow" << std::endl;
	return result;
}
