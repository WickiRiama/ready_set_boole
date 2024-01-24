#include <iostream>

#include "gray_code.h"

uint32_t gray_code(uint32_t n)
{
	// Operations :

	// uint32_t carry = (n >> 31) << 31;
	// uint32_t double_n = n << 1;

	// result = n ^ double_n;
	// result = result >> 1;
	// result = result | carry;

	return ((n ^ (n << 1)) >> 1) | (n & (1 << 31));
}

// Convertisseur code Gray : https://www.dcode.fr/code-gray