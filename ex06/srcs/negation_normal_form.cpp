#include <iostream>

#include "Ast.hpp"

std::string negation_normal_form(std::string &formula)
{
	try
	{
		Ast ast(formula);
		ast.convert2NegationNormalForm();
		return ast.getFormula();
	}
	catch(const Ast::InvalidFormulaException& e)
	{
		std::cerr << e.what() << '\n';
		return "Error";
	}
}
