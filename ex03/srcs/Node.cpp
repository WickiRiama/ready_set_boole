#include "Node.hpp"

//=============================================================================
// Constructors
//=============================================================================

Node::Node(void)
{
}

Node::Node(Node *parent, char value) : _parent(_parent), _left_child(NULL), _right_child(NULL), _value(value)
{
	this->_is_root = !parent;
	this->_is_leaf = (value == '0' || value == '1');
}

Node::Node(Node const &src)
{
	*this = src;
}

Node::~Node(void)
{
}

//=============================================================================
// Operators
//=============================================================================

Node &Node::operator=(Node const &rhs)
{
	if (this != &rhs)
	{
		this->_is_root = rhs._is_root;
		this->_is_leaf = rhs._is_leaf;
		this->_parent = rhs._parent;
		this->_left_child = rhs._left_child;
		this->_right_child = rhs._right_child;
		this->_value = rhs._value;
	}
}

//=============================================================================
// Getters
//=============================================================================

bool Node::isRoot(void) const
{
	return this->_is_root;
}

bool Node::isLeaf(void) const
{
	return this->_is_leaf;
}

Node *Node::getParent(void)
{
	return this->_parent;
}

Node *Node::getLeftChild(void)
{
	return this->_left_child;
}

Node *Node::getRightChild(void)
{
	return this->_right_child;
}

//=============================================================================
// Setters
//=============================================================================

void Node::setLeftChild(Node *left_child)
{
	this->_left_child = left_child;
}

void Node::setRightChild(Node *right_child)
{
	this->_right_child = right_child;
}
