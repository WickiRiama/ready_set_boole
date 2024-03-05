#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>
#include <map>

#include "Node.hpp"

class Ast
{
private:
	Node *_root_node;
	std::map<char, char> _variables;
	std::string _operators;

	Ast(void);
	void setRootNode(char value);

	Node *addNode(Node *current_node, char value);
	void clearTree(Node *root);
	void printNodeRow(std::vector<Node *> &current_row, std::vector<Node *> &next_row, std::vector<int> &indexes) const;
	void printNodeBranch(int n_rows, std::vector<Node *> &current_row, std::vector<Node *> &next_row, std::vector<int> &indexes) const;
	void printHeader(void) const;
	void printEvaluation(void) const;
	void printLines(std::map<char, char>::iterator it);
	bool isComplete(Node *root) const;

	bool negation(bool b1) const;
	bool conjonction(bool b1, bool b2) const;
	bool disjunction(bool b1, bool b2) const;
	bool xDisjunction(bool b1, bool b2) const;
	bool mCondition(bool b1, bool b2) const;
	bool equivalence(bool b1, bool b2) const;
	bool evaluateNode(Node *node) const;

	void removeDoubleNegation(Node *negation);
	void removeDisjunctionNegation(Node *negation);
	void removeConjonctionNegation(Node *negation);
	void removeMaterialCondition(Node *m_condition);
	void removeEquivalence(Node *equivalence);
	void convert2NegationNormalForm(Node *root);

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
	void printTruthTable(void);
	bool evaluate(void) const;
	void convert2NegationNormalForm(void);
};

#endif