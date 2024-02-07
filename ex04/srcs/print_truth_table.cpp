#include <string>
#include <map>
#include <iostream>

#include "print_truth_table.h"
#include "Ast.hpp"

std::map<char, bool> setVariables(std::string &formula)
{
	std::map<char, bool> newMap;
	for (size_t i = 0; i < formula.size(); i++)
	{
		if (isalpha(formula[i]) && isupper(formula[i]))
		{
			newMap[formula[i]] = 0;
		}
	}
	return newMap;
}

void print_truth_table(std::string &formula)
{
	std::map<char, bool> variables = setVariables(formula);

	for (std::map<char, bool>::iterator it = variables.begin(); it != variables.end(); it++)
	{
		std::cout << "[" << it->first << ": " << it->second << "] ";
	}
	std::cout << std::endl;

}
