#include <queue>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>

#include "Ast.hpp"

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
