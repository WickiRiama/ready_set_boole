#include "Ast.hpp"

void Ast::convert2CNN(void)
{
	this->convert2NegationNormalForm();
	this->convert2CNN(this->_root_node);
}

void Ast::convert2CNN(Node *root)
{
	if (!root || root->isLeaf())
	{
		return;
	}
	if (root->getValue() == '&')
	{
		Node *parent = root->getParent();
		if (parent && parent->getValue() == '|')
		{
			root = moveUp(root);;
			convert2CNN(root);
		}
	}
	else
	{
		convert2CNN(root->getLeftChild());
		convert2CNN(root->getRightChild());
	}
}

Node *Ast::newDisjunction(Node *parent, Node *a, Node *b) const
{
	Node *result = new Node(parent, '|');

	result->setLeftChild(a);
	result->setRightChild(b);

	return result;
}

Node *Ast::moveUp(Node *conjunction) 
{
	Node *disjunction = conjunction->getParent();

	Node *a;
	if (conjunction == disjunction->getLeftChild())
	{
		a = disjunction->getRightChild();
	}
	else
	{
		a = disjunction->getLeftChild();
	}
	Node *b = conjunction->getLeftChild();
	Node *c = conjunction->getRightChild();
	Node *a_copy = new Node(*a);

	disjunction->setValue('&');
	disjunction->setLeftChild(newDisjunction(disjunction, a_copy, b));
	disjunction->setRightChild(newDisjunction(disjunction, a, c));

	return disjunction;
}
