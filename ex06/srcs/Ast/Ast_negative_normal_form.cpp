#include <queue>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>

#include "Ast.hpp"

Node *Ast::removeDoubleNegation(Node *negation)
{
	Node *parent = negation->getParent();
	Node *newChild = negation->getRightChild()->getRightChild();

	if (!parent)
	{
		this->_root_node = newChild;
		newChild->setParent(NULL);
	}
	else if (parent->getLeftChild() == negation)
	{
		parent->setLeftChild(newChild);
	}
	else
	{
		parent->setRightChild(newChild);
	}
	negation->getRightChild()->setRightChild(NULL);
	clearTree(negation);
	return newChild;
}

Node *Ast::removeDisjunctionNegation(Node *negation)
{
	Node *parent = negation->getParent();
	Node *disjunction = negation->getRightChild();
	Node *left_child = disjunction->getLeftChild();
	Node *right_child = disjunction->getRightChild();

	if (!parent)
	{
		this->_root_node = disjunction;
		this->_root_node->setParent(NULL);
	}
	else if (parent->getLeftChild() == negation)
	{
		parent->setLeftChild(disjunction);
	}
	else
	{
		parent->setRightChild(disjunction);
	}

	disjunction->setValue('&');
	disjunction->setLeftChild(NULL);
	disjunction->setRightChild(NULL);
	addNode(disjunction, '!');
	addNode(disjunction, '!');
	disjunction->getLeftChild()->setRightChild(left_child);
	disjunction->getRightChild()->setRightChild(right_child);

	negation->setRightChild(NULL);
	clearTree(negation);

	return disjunction;
}

Node *Ast::removeXDisjunctionNegation(Node *negation)
{
	Node *parent = negation->getParent();
	Node *x_disjunction = negation->getRightChild();

	if (!parent)
	{
		this->_root_node = x_disjunction;
		this->_root_node->setParent(NULL);
	}
	else if (parent->getLeftChild() == negation)
	{
		parent->setLeftChild(x_disjunction);
	}
	else
	{
		parent->setRightChild(x_disjunction);
	}

	x_disjunction->setValue('=');
	removeEquivalence(x_disjunction);

	negation->setRightChild(NULL);
	clearTree(negation);

	return x_disjunction;
}

Node *Ast::removeConjonctionNegation(Node *negation)
{
	Node *parent = negation->getParent();
	Node *conjonction = negation->getRightChild();
	Node *left_child = conjonction->getLeftChild();
	Node *right_child = conjonction->getRightChild();

	if (!parent)
	{
		this->_root_node = conjonction;
		this->_root_node->setParent(NULL);
	}
	else if (parent->getLeftChild() == negation)
	{
		parent->setLeftChild(conjonction);
	}
	else
	{
		parent->setRightChild(conjonction);
	}

	conjonction->setValue('|');
	conjonction->setLeftChild(NULL);
	conjonction->setRightChild(NULL);
	addNode(conjonction, '!');
	addNode(conjonction, '!');
	conjonction->getLeftChild()->setRightChild(left_child);
	conjonction->getRightChild()->setRightChild(right_child);

	negation->setRightChild(NULL);
	clearTree(negation);

	return conjonction;
}

void Ast::removeMaterialCondition(Node *m_condition)
{
	Node *left_child = m_condition->getLeftChild();
	Node *negation;

	m_condition->setValue('|');
	m_condition->setLeftChild(NULL);
	negation = addNode(m_condition, '!');
	negation->setRightChild(left_child);
}

void Ast::removeEquivalence(Node *equivalence)
{
	Node *left_child = equivalence->getLeftChild();
	Node *right_child = equivalence->getRightChild();
	Node *new_right;
	Node *new_left;

	equivalence->setValue('&');
	equivalence->setLeftChild(NULL);
	equivalence->setRightChild(NULL);

	new_right = addNode(equivalence, '>');
	new_right->setLeftChild(right_child);
	new_right->setRightChild(left_child);

	new_left = addNode(equivalence, '>');
	new_left->setLeftChild(new Node(*left_child));
	new_left->setRightChild(new Node(*right_child));

	removeMaterialCondition(new_right);
	removeMaterialCondition(new_left);
}

Node *Ast::removeXDisjunction(Node *x_disjunction)
{
	Node *parent = x_disjunction->getParent();
	Node *negation = new Node(parent, '!');
	negation->setLeftChild(new Node());

	if (!parent)
	{
		this->_root_node = negation;
	}
	else if (parent->getLeftChild() == x_disjunction)
	{
		parent->setLeftChild(negation);
	}
	else
	{
		parent->setRightChild(negation);
	}
	negation->setRightChild(x_disjunction);
	x_disjunction->setParent(negation);
	x_disjunction->setValue('=');

	return negation;
}

bool isXDisjunction(Node *root)
{
	return (root && root->getValue() == '^');
}

bool isValidNegation(Node *root)
{
	return (root && root->getValue() == '!' && isupper(root->getRightChild()->getValue()));
}

Node *Ast::removeNegations(Node *root)
{
	while (isXDisjunction(root) || (root->getValue() == '!' && !isValidNegation(root)))
	{
		if (root->getValue() == '^')
			root = removeXDisjunction(root);
		else if (root->getRightChild()->getValue() == '!')
			root = removeDoubleNegation(root);
		else if (root->getRightChild()->getValue() == '|')
			root = removeDisjunctionNegation(root);
		else if (root->getRightChild()->getValue() == '&')
			root = removeConjonctionNegation(root);
		else if (root->getRightChild()->getValue() == '>')
		{
			removeMaterialCondition(root->getRightChild());
			root = removeDisjunctionNegation(root);
		}
		else if (root->getRightChild()->getValue() == '=')
		{
			removeEquivalence(root->getRightChild());
			root = removeConjonctionNegation(root);
		}
		else if (root->getRightChild()->getValue() == '^')
			root = removeXDisjunctionNegation(root);
	}
	return root;
}

void Ast::convert2NegationNormalForm(Node *root)
{
	if (!root || root->isLeaf())
		return;

	root = removeNegations(root);
	if (root->getValue() == '>')
		removeMaterialCondition(root);
	else if (root->getValue() == '=')
		removeEquivalence(root);
	else if (root->getValue() == '^')
		removeXDisjunction(root);

	convert2NegationNormalForm(root->getLeftChild());
	convert2NegationNormalForm(root->getRightChild());
}

void Ast::convert2NegationNormalForm(void)
{
	convert2NegationNormalForm(this->_root_node);
}
