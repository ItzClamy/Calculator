#include "Expression_node.h"

/*
	Initializes the token, left, and right data members using an initializer list
		Accepts a single argument
			- Token (instance of the Token Class)
*/
ExpressionNode::ExpressionNode(const Token& token) : token(token), left(nullptr), right(nullptr), parent(nullptr) {}; 