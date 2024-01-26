#include <string>

#include "bool_eval.h"



bool eval_formula(std::string &formula)
{
	// Operations :

	// uint32_t carry = (n >> 31) << 31;
	// uint32_t double_n = n << 1;

	// result = n ^ double_n;
	// result = result >> 1;
	// result = result | carry;

	return true;
}

// Convertisseur code Gray : https://www.dcode.fr/code-gray