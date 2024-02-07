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

std::string formulaReplacement(std::string &formula, std::string &variables, std::string &values)
{
	std::string newFormula(formula);
	for (size_t i = 0; i < variables.size(); i++)
	{
		std::replace(newFormula.begin(), newFormula.end(), variables[i], values[i]);
	}
	return newFormula;
}

void setLine(std::string &formula, std::string &variables, std::string &values, size_t i)
{
	if (i == variables.size())
	{
		std::string replacedFormula = formulaReplacement(formula, variables, values);
		std::cout << replacedFormula << std::endl;
		// evaluate formula
		// print
		return ;
	}
	setLine(formula, variables, values, i + 1);
	values[i] = '1';
	setLine(formula, variables, values, i + 1);
	values[i] = '0';

	return ;
}

void print_truth_table(std::string &formula)
{
	std::string variables = setVariables(formula);
	std::string values(variables.size(), '0');

	setLine(formula, variables, values, 0);
	if (variables.size() == 0)
	{
		std::cerr << "The formula is invalid" << std::endl;
		return;
	}

	printHeader(variables);
}
