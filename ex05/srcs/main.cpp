#include <iostream>
#include <fstream>

#include "negation_normal_form.h"
#include "Ast.hpp"

int main(int ac, char** av)
{
	if (ac != 2)
	{
		std::cerr << "Usage: ./nnf string" << std::endl;
		return 1;
	}

	std::string formula = av[1];
	// formula = "AB!!";

	Ast ast(formula);
	ast.printTree();
	std::ofstream first_file("before.txt", std::ios::out | std::ios::trunc);
	if (first_file.is_open())
		ast.printTruthTable(first_file);
	first_file.close();

	negation_normal_form(formula);
}