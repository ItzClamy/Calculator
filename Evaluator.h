#pragma once
#include "Expression_node.h" 
#include "Utility.h"
#include <string>
#include <unordered_map>
#include <iostream> 

/* Enumerates the sides of an equation for better clarity and readability. */
enum class EquationSide {
	Left,
	Right
};

/*------Evaluator.h------------------------------------------------------------
	The Evaluator class stands as the core mechanism for evaluating mathematical
	expressions, which are internally represented as trees of ExpressionNodes.

	In cases where expressions contain variable terms, the Evaluator will refer to
	a provided map (variableMap) to retrieve their corresponding numeric values.

	Key functionalities and operations include:
		- Constructor: Facilitates instantiation with or without a given variable map.
		- evaluate: Computes the value of the given expression tree.
		- setVariable: Incorporates or updates a variable's value within the internal map.

	For instance, given an expression like "x + 3" and a map {x: 2}, the evaluator
	would compute the result as 5.

----------------------------------------------------------------------------*/

class Evaluator {

private:
	/* This map serves as a repository of variable names (as strings) and their
	   corresponding numeric values. When an expression evaluation encounters a
	   variable, this map is consulted to retrieve the variable's value. */
	std::unordered_map<std::string, double>& variables;

public:

	/* Default constructor. Useful when no variable map is provided initially. */
	Evaluator() = default;

	/* Primary constructor: Accepts a map of variables, enabling their reference
	   during expression evaluation. */
	Evaluator(std::unordered_map<std::string, double>& variables) : variables(variables) {};

	/* Conducts the evaluation of a given expression tree, starting from its root node.
	   If the evaluation stumbles upon a variable, its value is sourced from the variableMap.
	   Finally, the resultant value of the entire expression is returned. */
	double evaluate(const ExpressionNodePtr& root);

	/* Assigns or updates a variable's value within the internal map. */
	void setVariable(const std::string& name, double value);
};