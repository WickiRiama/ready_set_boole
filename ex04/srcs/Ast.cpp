#include <queue>
#include <iostream>
#include <cmath>
#include <algorithm>

#include "Ast.hpp"

//=============================================================================
// Constructors
//=============================================================================

Ast::Ast(void)
{
}

Ast::Ast(std::string const &formula) : _operators("!&|^>=")
{
	Node *current_node;

	this->setRootNode(formula[formula.size() - 1]);
	current_node = this->_root_node;
	for (size_t i = formula.size() - 1; i > 0; i--)
	{
		try
		{
			current_node = this->addNode(current_node, formula[i - 1]);
		}
		catch (InvalidFormulaException &e)
		{
			clearTree(this->_root_node);
			throw e;
		}
	}
	if (!this->isComplete(this->_root_node))
	{
		clearTree(this->_root_node);
		throw InvalidFormulaException();
	}
}

Ast::Ast(Ast const &src)
{
	*this = src;
}

Ast::~Ast(void)
{
	clearTree(this->_root_node);
}

//=============================================================================
// Operators
//=============================================================================

Ast &Ast::operator=(Ast const &rhs)
{
	if (this != &rhs)
	{
		this->_root_node = rhs._root_node;
		this->_variables = rhs._variables;
		this->_operators = rhs._operators;
	}
	return *this;
}

//=============================================================================
// Setters
//=============================================================================

void Ast::setRootNode(char value)
{
	if (isalpha(value) && isupper(value))
	{
		this->_variables[value] = '0';
	}
	this->_root_node = new Node(NULL, value);
}

//=============================================================================
// Methods
//=============================================================================

Node *Ast::addNode(Node *current_node, char value)
{
	if (!current_node || current_node->isLeaf())
	{
		throw InvalidFormulaException();
	}

	if (isalpha(value) && isupper(value))
	{
		this->_variables[value] = '0';
	}
	Node *newNode = new Node(current_node, value);
	if (!current_node->getRightChild())
	{
		current_node->setRightChild(newNode);
		if (current_node->getValue() == '!')
		{
			Node *emptyNode = new Node();
			current_node->setLeftChild(emptyNode);
		}
	}
	else if (!current_node->getLeftChild())
	{
		current_node->setLeftChild(newNode);
	}
	if (newNode->isLeaf())
	{
		return current_node->getClosestIncompleteParent();
	}
	else
	{
		return newNode;
	}
}

void Ast::clearTree(Node *root)
{
	if (root)
	{
		clearTree(root->getRightChild());
		clearTree(root->getLeftChild());
	}
	delete root;
}

int countSpaces(int n_rows)
{
	int result = 0;
	for (int row = 0; row < n_rows; row++)
	{
		result += std::pow(2, (row + 1));
	}
	return result;
}

int countInnerSpaces(int n_rows)
{
	int result = 3;
	for (int row = 0; row < n_rows - 1; row++)
	{
		result += result * 2 + 1;
	}
	return result;
}

void Ast::printNodeRow(std::vector<Node *> &current_row, std::vector<Node *> &next_row, std::vector<int> &indexes) const
{
	int i = 0;
	for (size_t node = 0; node < current_row.size(); node++)
	{
		while (i < indexes[0])
		{
			std::cout << " ";
			i++;
		}
		if (current_row[node] && current_row[node]->getValue() != '@')
		{
			std::cout << current_row[node]->getValue();
			next_row.push_back(current_row[node]->getLeftChild());
			next_row.push_back(current_row[node]->getRightChild());
		}
		else
		{
			std::cout << " ";
			next_row.push_back(NULL);
			next_row.push_back(NULL);
		}
		indexes.push_back(i - 1);
		indexes.push_back(i + 1);
		indexes.erase(indexes.begin());
		i++;
	}
	std::cout << std::endl;
}

void Ast::printNodeBranch(int n_rows, std::vector<Node *> &current_row, std::vector<Node *> &next_row, std::vector<int> &indexes) const
{
	int i;
	int extern_spaces = countSpaces(n_rows);
	while (indexes[0] > extern_spaces)
	{
		i = 0;
		for (size_t node = 0; node < current_row.size(); node++)
		{
			while (i < indexes[0])
			{
				std::cout << " ";
				i++;
			}
			if (next_row[node * 2] && next_row[node * 2]->getValue() != '@')
				std::cout << "/";
			else
				std::cout << " ";
			indexes.push_back(i - 1);
			indexes.erase(indexes.begin());
			i++;
			while (i < indexes[0])
			{
				std::cout << " ";
				i++;
			}
			if (next_row[node * 2 + 1])
				std::cout << "\\";
			else
				std::cout << " ";
			indexes.push_back(i + 1);
			indexes.erase(indexes.begin());
			i++;
		}
		std::cout << std::endl;
	}
}

void Ast::printTree(void) const
{
	if (!this->_root_node)
	{
		std::cout << "Empty tree" << std::endl;
		return;
	}
	int n_rows = this->_root_node->getMaxDepth();
	std::vector<Node *> current_row;
	std::vector<Node *> next_row;
	std::vector<int> indexes = {countSpaces(n_rows)};

	current_row.push_back(this->_root_node);
	for (int i = 0; i <= n_rows; i++)
	{
		next_row.clear();
		printNodeRow(current_row, next_row, indexes);
		printNodeBranch(n_rows - i - 1, current_row, next_row, indexes);
		current_row = next_row;
	}
}

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

void Ast::printEvaluation(void) const
{
	std::cout << "|";
	for (std::map<char, char>::const_iterator it = _variables.begin(); it != _variables.end(); it++)
	{
		std::cout << " " << it->second << " |";
	}
	std::cout << " " << this->evaluate() << " |" << std::endl;
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

void Ast::printTruthTable(void)
{
	this->printHeader();
	std::map<char, char>::iterator it = _variables.begin();
	this->printLines(it);
}

bool Ast::isComplete(Node *root) const
{
	if (!root)
	{
		return false;
	}
	if (root->isLeaf())
	{
		return true;
	}
	return (this->isComplete(root->getLeftChild()) && this->isComplete(root->getRightChild()));
}

//=============================================================================
// Evaluation Methods
//=============================================================================

bool Ast::negation(bool b1) const
{
	return (!b1);
}

bool Ast::conjonction(bool b1, bool b2) const
{
	return (b1 && b2);
}

bool Ast::disjunction(bool b1, bool b2) const
{
	return (b1 || b2);
}

bool Ast::xDisjunction(bool b1, bool b2) const
{
	return (b1 != b2);
}

bool Ast::mCondition(bool b1, bool b2) const
{
	return (!(b1 && !b2));
}

bool Ast::equivalence(bool b1, bool b2) const
{
	return (b1 == b2);
}

bool Ast::evaluateNode(Node *node) const
{
	char c = node->getValue();
	if (isalpha(c) && isupper(c))
		c = _variables.at(node->getValue());
	switch (c)
	{
	case '0':
		return false;
		break;
	case '1':
		return true;
		break;
	case '!':
		return negation(evaluateNode(node->getRightChild()));
		break;
	case '&':
		return conjonction(evaluateNode(node->getLeftChild()), evaluateNode(node->getRightChild()));
		break;
	case '|':
		return disjunction(evaluateNode(node->getLeftChild()), evaluateNode(node->getRightChild()));
		break;
	case '^':
		return xDisjunction(evaluateNode(node->getLeftChild()), evaluateNode(node->getRightChild()));
		break;
	case '>':
		return mCondition(evaluateNode(node->getLeftChild()), evaluateNode(node->getRightChild()));
		break;
	case '=':
		return equivalence(evaluateNode(node->getLeftChild()), evaluateNode(node->getRightChild()));
		break;

	default:
		throw InvalidFormulaException();
		break;
	}
}

bool Ast::evaluate(void) const
{
	try
	{
		return evaluateNode(this->_root_node);
	}
	catch (const InvalidFormulaException &e)
	{
		throw e;
	}
}

//=============================================================================
// Exceptions
//=============================================================================

const char *Ast::InvalidFormulaException::what() const throw()
{
	return "The formula is invalid";
}
