#include <iostream>

#include "negation_normal_form.h"

int main(int ac, char** av)
{
	if (ac != 2)
	{
		std::cerr << "Usage: ./nnf string" << std::endl;
		return 1;
	}

	std::string formula = av[1];
	// formula = "AB!!";

	negation_normal_form(formula);
}