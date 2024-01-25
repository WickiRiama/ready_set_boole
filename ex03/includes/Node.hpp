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
	std::string _value;

	Node(void);

public:
	Node(Node *parent, std::string value);
	Node(Node const &src);
	~Node(void);

	Node &operator=(Node const &rhs);

	bool isRoot(void) const;
	bool isLeaf(void) const;
	Node *getParent(void);
	Node *getLeftChild(void);
	Node *getRightChild(void);

	void setLeftChild(Node *left_child);
	void setRightChild(Node *right_child);
};

#endif