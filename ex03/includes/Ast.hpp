#ifndef AST_HPP
#define AST_HPP

#include <string>

#include "Node.hpp"

class Ast
{
private:
	Node *_root_node;

	Ast(void);
	void setRootNode(char value);

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
};

#endif