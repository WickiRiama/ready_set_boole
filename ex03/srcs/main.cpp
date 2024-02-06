#include <iostream>
#include <cmath>

#include "bool_eval.h"

int main(int ac, char** av)
{
	if (ac != 2)
	{
		std::cerr << "Usage: ./bool_eval string" << std::endl;
		return 1;
	}

	std::string formula = av[1];
	std::cout << std::boolalpha << eval_formula(formula) << std::endl;
}