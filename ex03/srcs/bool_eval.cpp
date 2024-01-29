#include <string>

#include "bool_eval.h"
#include "Ast.hpp"


bool eval_formula(std::string &formula)
{
	Ast ast(formula);
	ast.printTree();

	return true;
}

