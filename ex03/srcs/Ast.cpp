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
	std::queue<char> operandes;

	for (size_t i = 0; i < formula.size(); i++)
	{
		if (formula[i] == "0" || formula[i] == "1")
		{
			operandes.push(formula[i]);
		}
	}
}

Ast::Ast(Ast const &src)
{
	*this = src;
}

Ast::~Ast(void)
{
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

void Ast::setRoodNode(char value)
{
	if (value == "1" || value == "0")
	
}

//=============================================================================
// Exceptions
//=============================================================================


const char *InvalidFormulaException::what() const throw()
{
	return "The formula is invalid";
}
