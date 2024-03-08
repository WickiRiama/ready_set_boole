#include <queue>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>

#include "Ast.hpp"

int countSpaces(int n_rows)
{
	int result = 0;
	for (int row = 0; row < n_rows; row++)
	{
		result += std::pow(2, (row + 1));
	}
	return result;
}

int countInnerSpaces(int n_rows)
{
	int result = 3;
	for (int row = 0; row < n_rows - 1; row++)
	{
		result += result * 2 + 1;
	}
	return result;
}

void Ast::printNodeRow(std::vector<Node *> &current_row, std::vector<Node *> &next_row, std::vector<int> &indexes) const
{
	int i = 0;
	for (size_t node = 0; node < current_row.size(); node++)
	{
		while (i < indexes[0])
		{
			std::cout << " ";
			i++;
		}
		if (current_row[node] && current_row[node]->getValue() != '@')
		{
			std::cout << current_row[node]->getValue();
			next_row.push_back(current_row[node]->getLeftChild());
			next_row.push_back(current_row[node]->getRightChild());
		}
		else
		{
			std::cout << " ";
			next_row.push_back(NULL);
			next_row.push_back(NULL);
		}
		indexes.push_back(i - 1);
		indexes.push_back(i + 1);
		indexes.erase(indexes.begin());
		i++;
	}
	std::cout << std::endl;
}

void Ast::printNodeBranch(int n_rows, std::vector<Node *> &current_row, std::vector<Node *> &next_row, std::vector<int> &indexes) const
{
	int i;
	int extern_spaces = countSpaces(n_rows);
	while (indexes[0] > extern_spaces)
	{
		i = 0;
		for (size_t node = 0; node < current_row.size(); node++)
		{
			while (i < indexes[0])
			{
				std::cout << " ";
				i++;
			}
			if (next_row[node * 2] && next_row[node * 2]->getValue() != '@')
				std::cout << "/";
			else
				std::cout << " ";
			indexes.push_back(i - 1);
			indexes.erase(indexes.begin());
			i++;
			while (i < indexes[0])
			{
				std::cout << " ";
				i++;
			}
			if (next_row[node * 2 + 1])
				std::cout << "\\";
			else
				std::cout << " ";
			indexes.push_back(i + 1);
			indexes.erase(indexes.begin());
			i++;
		}
		std::cout << std::endl;
	}
}

void Ast::printTree(void) const
{
	if (!this->_root_node)
	{
		std::cout << "Empty tree" << std::endl;
		return;
	}
	int n_rows = this->_root_node->getMaxDepth();
	std::vector<Node *> current_row;
	std::vector<Node *> next_row;
	std::vector<int> indexes = {countSpaces(n_rows)};

	current_row.push_back(this->_root_node);
	for (int i = 0; i <= n_rows; i++)
	{
		next_row.clear();
		printNodeRow(current_row, next_row, indexes);
		printNodeBranch(n_rows - i - 1, current_row, next_row, indexes);
		current_row = next_row;
	}
}
