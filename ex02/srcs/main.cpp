#include <iostream>
#include <cmath>

#include "gray_code.h"

int bin_size(uint32_t n)
{
	int l = 1;

	while(n / 2)
	{
		l += 1;
		n = n / 2;
	}
	return l;
}

void print_bin(uint32_t n)
{
	int const l = bin_size(n);

	for (int i = l - 1; i >= 0; i--)
	{
		std::cout << (n >> i & 1);
	}
	std::cout << std::endl;
}

int main(int ac, char** av)
{
	if (ac != 2)
	{
		std::cerr << "Usage: ./gray_code uint1 uint2" << std::endl;
		return 1;
	}
	uint32_t n = static_cast<uint32_t>(atoi(av[1]));
	uint32_t gray_n = gray_code(n);

	std::cout << "Binary representation of " << n << " before change: ";
	print_bin(n);
	std::cout << "Binary representation of " << n << " after change: ";
	print_bin(gray_n);
	std::cout << "Decimal representation of " << n << " after change: " << gray_n << std::endl;
}