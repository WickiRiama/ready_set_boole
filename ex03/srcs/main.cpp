#include <iostream>
#include <cmath>

#include "bool_eval.h"

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