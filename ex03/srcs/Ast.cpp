#include <queue>

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

//=============================================================================
// Exceptions
//=============================================================================

const char *Ast::InvalidFormulaException::what() const throw()
{
	return "The formula is invalid";
}
