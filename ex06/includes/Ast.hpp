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

	std::string getFormula(Node *root) const;
	bool isComplete(Node *root) const;

	void setRootNode(char value);
	Node *addNode(Node *current_node, char value);
	void clearTree(Node *root);

public:
	Ast(std::string const &formula);
	Ast(Ast const &src);
	~Ast(void);

	Ast &operator=(Ast const &rhs);

	std::string getFormula(void) const;

//=============================================================================
// Evaluation
//=============================================================================

private:
	bool negation(bool b1) const;
	bool conjonction(bool b1, bool b2) const;
	bool disjunction(bool b1, bool b2) const;
	bool xDisjunction(bool b1, bool b2) const;
	bool mCondition(bool b1, bool b2) const;
	bool equivalence(bool b1, bool b2) const;
	bool evaluateNode(Node *node) const;

public:
	bool evaluate(void) const;

//=============================================================================
// Print
//=============================================================================

private:
	void printNodeRow(std::vector<Node *> &current_row, std::vector<Node *> &next_row, std::vector<int> &indexes) const;
	void printNodeBranch(int n_rows, std::vector<Node *> &current_row, std::vector<Node *> &next_row, std::vector<int> &indexes) const;

public:
	void printTree(void) const;

//=============================================================================
// Truth Table
//=============================================================================

private:
	void printHeader(void) const;
	void printHeader(std::ofstream &file) const;
	void printEvaluation(void) const;
	void printEvaluation(std::ofstream &file) const;

	void printLines(std::map<char, char>::iterator it);
	void printLines(std::map<char, char>::iterator it, std::ofstream &file);

public:
	void printTruthTable(void);
	void printTruthTable(std::ofstream &file);

//=============================================================================
// Negative Normal Form
//=============================================================================

private:
	Node *removeDoubleNegation(Node *negation);
	Node *removeDisjunctionNegation(Node *negation);
	Node *removeXDisjunctionNegation(Node *negation);
	Node *removeConjonctionNegation(Node *negation);
	Node *removeXDisjunction(Node *x_disjunction);
	void removeMaterialCondition(Node *m_condition);
	void removeEquivalence(Node *equivalence);
	Node *removeNegations(Node *root);
	void convert2NegationNormalForm(Node *root);

public:
	void convert2NegationNormalForm(void);

//=============================================================================
// Conjunctive Normal Form
//=============================================================================

private:
	void convert2CNN(Node *root);
	Node *moveUp(Node *conjunction);
	Node *newDisjunction(Node *parent, Node *a, Node *b) const;

public:
	void convert2CNN(void);

//=============================================================================
// Exception
//=============================================================================

public:


	class InvalidFormulaException : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};

};

#endif