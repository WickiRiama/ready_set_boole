#include <iostream>

#include "multiplier.h"

int main(int ac, char** av)
{
	if (ac != 3)
	{
		std::cerr << "Usage: ./multiplier uint1 uint2" << std::endl;
		return 1;
	}
	uint32_t a = static_cast<uint32_t>(atoi(av[1]));
	uint32_t b = static_cast<uint32_t>(atoi(av[2]));
	
	std::cout << multiplier(a, b) << std::endl;
}