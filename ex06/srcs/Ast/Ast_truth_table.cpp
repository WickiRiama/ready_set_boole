#include <queue>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>

#include "Ast.hpp"

void Ast::printHeader(void) const
{
	std::cout << "|";
	for (std::map<char, char>::const_iterator it = _variables.begin(); it != _variables.end(); it++)
	{
		std::cout << " " << it->first << " |";
	}
	std::cout << " = |" << std::endl;
	std::cout << "|";
	for (size_t i = 0; i <= _variables.size(); i++)
	{
		std::cout << "---|";
	}
	std::cout << std::endl;
}

void Ast::printHeader(std::ofstream &file) const
{
	file << "|";
	for (std::map<char, char>::const_iterator it = _variables.begin(); it != _variables.end(); it++)
	{
		file << " " << it->first << " |";
	}
	file << " = |" << std::endl;
	file << "|";
	for (size_t i = 0; i <= _variables.size(); i++)
	{
		file << "---|";
	}
	file << std::endl;
}

void Ast::printEvaluation(void) const
{
	std::cout << "|";
	for (std::map<char, char>::const_iterator it = _variables.begin(); it != _variables.end(); it++)
	{
		std::cout << " " << it->second << " |";
	}
	std::cout << " " << this->evaluate() << " |" << std::endl;
}

void Ast::printEvaluation(std::ofstream &file) const
{
	file << "|";
	for (std::map<char, char>::const_iterator it = _variables.begin(); it != _variables.end(); it++)
	{
		file << " " << it->second << " |";
	}
	file << " " << this->evaluate() << " |" << std::endl;
}

void Ast::printLines(std::map<char, char>::iterator it)
{
	if (it == _variables.end())
	{
		printEvaluation();
		return;
	}
	std::map<char, char>::iterator next_it = it;
	next_it++;
	printLines(next_it);
	it->second = '1';
	printLines(next_it);
	it->second = '0';
}

void Ast::printLines(std::map<char, char>::iterator it, std::ofstream &file)
{
	if (it == _variables.end())
	{
		printEvaluation(file);
		return;
	}
	std::map<char, char>::iterator next_it = it;
	next_it++;
	printLines(next_it, file);
	it->second = '1';
	printLines(next_it, file);
	it->second = '0';
}

void Ast::printTruthTable(void)
{
	this->printHeader();
	std::map<char, char>::iterator it = _variables.begin();
	this->printLines(it);
}

void Ast::printTruthTable(std::ofstream &file)
{
	this->printHeader(file);
	std::map<char, char>::iterator it = _variables.begin();
	this->printLines(it, file);
}
