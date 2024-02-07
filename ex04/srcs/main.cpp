#include <iostream>

#include "print_truth_table.h"

int main(int ac, char** av)
{
	if (ac != 2)
	{
		std::cerr << "Usage: ./ex04 string" << std::endl;
		return 1;
	}

	std::string formula = av[1];
	print_truth_table(formula);
}