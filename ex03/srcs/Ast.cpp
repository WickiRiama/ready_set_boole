#include <queue>
#include <iostream>
#include <cmath>

#include "Ast.hpp"

//=============================================================================
// Constructors
//=============================================================================

Ast::Ast(void)
{
}

Ast::Ast(std::string const &formula)
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
	// Check if tree is full !!!
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
	}
	return *this;
}

//=============================================================================
// Setters
//=============================================================================

void Ast::setRootNode(char value)
{
	this->_root_node = new Node(NULL, value);
}

//=============================================================================
// Methods
//=============================================================================

Node *Ast::addNode(Node *current_node, char value)
{
	if (!current_node)
	{
		throw InvalidFormulaException();
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
		if (current_row[node] && current_row[node]->getValue() != 'X')
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
			if (next_row[node * 2] && next_row[node * 2]->getValue() != 'X')
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

void Ast::printTree(void)
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

//=============================================================================
// Exceptions
//=============================================================================

const char *Ast::InvalidFormulaException::what() const throw()
{
	return "The formula is invalid";
}
