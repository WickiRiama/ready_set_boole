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

void printEvaluation(std::string &values, bool result)
{
	std::cout << "|";
	for (size_t i = 0; i < values.size(); i++)
	{
		std::cout << " " << values[i] << " |";
	}
	std::cout << " " << result << " |" << std::endl;
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

void printLines(std::string &formula, std::string &variables, std::string &values, size_t i)
{
	if (i == variables.size())
	{
		std::string replacedFormula = formulaReplacement(formula, variables, values);
		Ast ast(replacedFormula);
		bool result = ast.evaluate();
		printEvaluation(values, result);
		return;
	}
	printLines(formula, variables, values, i + 1);
	values[i] = '1';
	printLines(formula, variables, values, i + 1);
	values[i] = '0';
}

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
