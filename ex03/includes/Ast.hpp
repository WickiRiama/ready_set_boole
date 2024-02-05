#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>

#include "Node.hpp"

class Ast
{
private:
	Node *_root_node;

	Ast(void);
	void setRootNode(char value);
	Node *addNode(Node *current_node, char value);
	void clearTree(Node *root);
	void printNodeRow(std::vector<Node *> &current_row, std::vector<Node *> &next_row, std::vector<int> &indexes) const;
	void printNodeBranch(int n_rows, std::vector<Node *> &current_row, std::vector<Node *> &next_row, std::vector<int> &indexes) const;

public:
	Ast(std::string const &formula);
	Ast(Ast const &src);
	~Ast(void);

	Ast &operator=(Ast const &rhs);

	class InvalidFormulaException : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};

	void printTree(void) const;
	bool isComplete(Node *root) const;
};

#endif