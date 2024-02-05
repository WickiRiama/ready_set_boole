#ifndef NODE_HPP
#define NODE_HPP

#include <string>

class Node
{
private:
	bool _is_root;
	bool _is_leaf;
	Node *_parent;
	Node *_left_child;
	Node *_right_child;
	char _value;


public:
	Node(void);
	Node(Node *parent, char value);
	Node(Node const &src);
	~Node(void);

	Node &operator=(Node const &rhs);

	bool isRoot(void) const;
	bool isLeaf(void) const;
	bool isComplete(void) const;
	Node *getParent(void);
	Node *getClosestIncompleteParent(void);
	Node *getLeftChild(void);
	Node *getRightChild(void);
	char getValue(void) const;
	int getMaxDepth(void) const;

	void setLeftChild(Node *left_child);
	void setRightChild(Node *right_child);
};

#endif