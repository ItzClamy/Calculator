#include "Evaluator.h" 
#include <stdexcept>
#include <cmath> 
#include <iostream>

/* evalute: Evaluates a given expression tree representing a mathematical equation*/
double Evaluator::evaluate(const ExpressionNodePtr& root) {

	
	if (!root) {  //Checks for a null root node, which indicates an invalid expression
		throw std::runtime_error("Invalid expression tree");
	}

	switch (root->token.getType()) {  //Determine the operation or value represented by the current node

		case TokenType::Number: {
			return std::stod(root->token.getValue()); 
		}

		case TokenType::Addition: {
			if (!root->left || !root->right) {
				throw std::runtime_error("Invalid nodes for addition operation");
			}

			return evaluate(root->left) + evaluate(root->right); 
		}

		case TokenType::Subtraction: {
			if (!root->left || !root->right) {
				throw std::runtime_error("Invalid nodes for subtraction operation");
			}

			return evaluate(root->left) - evaluate(root->right);
		}

		case TokenType::Multiplication: {
			if (!root->left || !root->right) {
				throw std::runtime_error("Invalid nodes for multiplication operation");
			}

			return evaluate(root->left) * evaluate(root->right);
		}

		case TokenType::Division: {

			if (!root->left || !root->right) {
				throw std::runtime_error("Invalid nodes for division operation");
			}

			double divisor = evaluate(root->right);  // Stores the divisor value

			if (divisor == 0) {  // Ensures division by zero doesn't occur
				throw std::runtime_error("Division by zero");
			}

			return evaluate(root->left) / divisor;  // Return the quotient of the left child divided by the right child
		}

		case TokenType::Sqrt: {

			double value = evaluate(root->left); // Stores the value under the square root

			if (value < 0) { // Ensures the value is a non-negative number 
				throw std::runtime_error("Invalid input for square root");
			}

			return std::sqrt(value); 
		}

		case TokenType::Exponents: {

			double left_value = evaluate(root->left);  // Stores the base of the exponent
			double right_value = evaluate(root->right);  // Stores the exponent value

			return std::pow(left_value, right_value); 
		}

		case TokenType::Variable: {
			
			if (variables.find(root->token.getValue()) != variables.end()) {  // Checks if the variable has a defined value in our map
				return variables[root->token.getValue()]; 
			}
			else {
				throw std::runtime_error("Variable not defined: " + root->token.getValue());  // If not defined throws error
			}
		}

		default: {  // Throws error if it encounters an unexpected token type
			throw std::runtime_error("Unknown token type in the evaluator");
		}
	}

	return 0.0; 
}

/* setVariable: Sets (or updates) the value of the variable in the map*/
void Evaluator::setVariable(const std::string& name, double value) {
	variables[name] = value; 
}