#include <queue>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>

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
	if (this->_root_node && this->_root_node->getValue() == '!')
	{
		Node *emptyNode = new Node();
		this->_root_node->setLeftChild(emptyNode);
	}
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
// Getters
//=============================================================================

std::string Ast::getFormula(void) const
{
	std::string result = getFormula(this->_root_node);
	reverse(result.begin(), result.end());
	return result;
}

std::string Ast::getFormula(Node *root) const
{
	if (!root || root->getValue() == '@')
	{
		return "";
	}

	std::string result = "";
	result += root->getValue();
	result += getFormula(root->getRightChild());
	result += getFormula(root->getLeftChild());
	return result;
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
	if (value == '!')
	{
		Node *emptyNode = new Node();
		newNode->setLeftChild(emptyNode);
	}
	if (!current_node->getRightChild())
	{
		current_node->setRightChild(newNode);
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
// Exceptions
//=============================================================================

const char *Ast::InvalidFormulaException::what() const throw()
{
	return "The formula is invalid";
}
