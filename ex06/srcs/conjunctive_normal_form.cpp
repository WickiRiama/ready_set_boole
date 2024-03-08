#include <iostream>

#include "Ast.hpp"

std::string conjunctive_normal_form(std::string &formula)
{
	try
	{
		Ast ast(formula);
		return "test";
	}
	catch(const Ast::InvalidFormulaException& e)
	{
		std::cerr << e.what() << '\n';
		return "Error";
	}
}
