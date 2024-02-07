#include <string>
#include <iostream>
#include <algorithm>

#include "print_truth_table.h"
#include "Ast.hpp"

std::string setVariables(std::string &formula)
{
	std::string variables;
	for (size_t i = 0; i < formula.size(); i++)
	{
		if (isalpha(formula[i]) && isupper(formula[i]) && variables.find(formula[i]) == std::string::npos)
		{
			variables += formula[i];
		}
	}
	sort(variables.begin(), variables.end());
	return variables;
}

void printHeader(std::string const &variables)
{
	std::cout << "|";
	for (size_t i = 0; i < variables.size(); i++)
	{
		std::cout << " " << variables[i] << " |";
	}
	std::cout << " = |" << std::endl;
	std::cout << "|";
	for (size_t i = 0; i <= variables.size(); i++)
	{
		std::cout << "---|";
	}
	std::cout << std::endl;
}

void print_truth_table(std::string &formula)
{
	std::string variables = setVariables(formula);
	if (variables.size() == 0)
	{
		std::cerr << "The formula is invalid" << std::endl;
		return;
	}

	printHeader(variables);
}
