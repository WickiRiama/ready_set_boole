#include <string>
#include <iostream>
#include <algorithm>

#include "print_truth_table.h"
#include "Ast.hpp"

void print_truth_table(std::string &formula)
{
	try
	{
		Ast ast(formula);
		ast.printTruthTable();
		// printLines(formula, variables, values, 0);
	}
	catch (const Ast::InvalidFormulaException &e)
	{
		std::cerr << e.what() << std::endl;
	}
}
