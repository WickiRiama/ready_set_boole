#include <iostream>
#include <fstream>

#include "negation_normal_form.h"
#include "Ast.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Usage: ./nnf string" << std::endl;
		return 1;
	}

	std::string formula = av[1];
	formula = "AB^!";

	try
	{
		Ast ast(formula);
		ast.printTree();
		std::ofstream first_file("before.txt", std::ios::out | std::ios::trunc);
		if (first_file.is_open())
			ast.printTruthTable(first_file);
		first_file.close();

		std::string new_formula = negation_normal_form(formula);
		std::cout << new_formula << std::endl;

		Ast new_ast(new_formula);
		new_ast.printTree();
		std::ofstream second_file("after.txt", std::ios::out | std::ios::trunc);
		if (second_file.is_open())
			new_ast.printTruthTable(second_file);
		second_file.close();

	}
	catch (const Ast::InvalidFormulaException &e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
}