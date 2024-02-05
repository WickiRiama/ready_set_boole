#include <string>
#include <iostream>

#include "bool_eval.h"
#include "Ast.hpp"

bool eval_formula(std::string &formula)
{
	try
	{
		Ast ast(formula);
		ast.printTree();
	}
	catch (Ast::InvalidFormulaException &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return true;
}
