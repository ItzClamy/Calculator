#include "Parser.h"
#include <stdexcept>
#include <iostream>

/* constructor: Initializes with a list of tokens and a set position to 0 */
Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), position(0) {};

/* parse: Parses the list of tokens and constructs a list of expression trees */
std::vector<ExpressionNodePtr> Parser::parse() {
	std::vector<ExpressionNodePtr> results;
	
	if (!is_primary(current_token()) && current_token().getType() != TokenType::Subtraction) {  // Checks for invalid tokens at start
		throw std::runtime_error("Unexpected token at the start: " + current_token().getValue());
	}

	check_parentheses_balance(); 

	while (position < tokens.size()) { 
		ExpressionNodePtr result; 

		if (peek(TokenType::Equal)) {   // Checks if the next token in the stream matches the "Equal" token
			result = parse_assignment();  //If there is an '=', we're dealing with an assignment statement 
		}
		else {
			result = parse_expression();  //If there is not an '=', we're dealing with an standard expression 
		}
		results.push_back(result); 
	}

	if (position != tokens.size()) {  // Ensure all tokens were processed
		throw std::runtime_error("Unexpected token at the end of input");
	}

	return results;
}

/* advance: Advances the position by one */
void Parser::advance() {
	if (position < tokens.size()) {
		position++;
	}
	else {
		throw std::runtime_error("Unexpected end of input");
	}
}

/* current_token: Returns the current token being processed*/
Token Parser::current_token() const {
	if (position < tokens.size()) {
		return tokens[position];
	}
	return Token(TokenType::CloseParenthesis, "");
}

/* parse_primary: Parses primary tokens such as numbers, parentheses, square roots, and negations*/
ExpressionNodePtr Parser::parse_primary() {
	Token token = current_token();
	advance();

	if (token.getType() == TokenType::Number) {
		return std::make_shared<ExpressionNode>(token);
	}
	else  if (token.getType() == TokenType::OpenParenthesis) {
		auto node = parse_expression();

		if (current_token().getType() != TokenType::CloseParenthesis) {
			throw std::runtime_error("Expected ')' but found: " + current_token().getValue());
		}
		advance();
		return node;
	}
	else if (token.getType() == TokenType::Sqrt) {
		return parse_sqrt();
	}
	else if (token.getType() == TokenType::Subtraction) {
		auto node = std::make_shared<ExpressionNode>(token); 
		node->left = parse_primary(); 
		node->left->parent = node; 
		return node; 
	}
	else if (token.getType() == TokenType::Variable) {				
		return std::make_shared<ExpressionNode>(token); 
	}
	else {
		throw std::runtime_error("Unexpected token: " + token.getValue());
	}

	return nullptr; 
}

/* Parses additive and subtractive operations */
ExpressionNodePtr Parser::parse_expression() {
	auto left = parse_term(); 

	while (current_token().getType() == TokenType::Addition || current_token().getType() == TokenType::Subtraction) {
		Token t = current_token(); 
		advance(); 

		auto right = parse_term(); 

		if (!left || !right) {
			throw std::runtime_error("Invalid binary operation");
		}

		auto node = std::make_shared<ExpressionNode>(t); 
		node->left = left; 
		node->right = right; 
		node->parent = node; 
		right->parent = node; 
		left = node; 
	}
	return left; 
}

/* parse_term: Parses multiplicative operations */
ExpressionNodePtr Parser::parse_term() {
	
	auto left = parse_factor();
	while (current_token().getType() == TokenType::Multiplication || current_token().getType() == TokenType::Division ||
		   is_primary(current_token())) {  // Handles implicit multiplication (Example: 2x, 2(3+5), etc..) 

		Token t = Token(TokenType::Multiplication, "*");

		if (!is_primary(current_token())) {
			t = current_token(); 
			advance(); 
		}

		auto right = parse_factor(); 

		if (!left || !right) {  
			throw std::runtime_error("Invalid binary operation");
		}

		auto node = std::make_shared<ExpressionNode>(t);
		node->left = left;
		node->right = right;
		left->parent = node;
		right->parent = node;
		left = node;
	}
	return left; 
}

/* parse_sqrt: Parses square root operations */
ExpressionNodePtr Parser::parse_sqrt() {
	auto node = std::make_shared<ExpressionNode>(Token(TokenType::Sqrt, "sqrt")); 
	node->left = parse_primary(); 
	node->left->parent = node; 
	return node; 
}

/* parse_factor: Parses exponentation*/
ExpressionNodePtr Parser::parse_factor() {
	auto left = parse_unary();

	while (current_token().getType() == TokenType::Exponents) {
		Token t = current_token();
		advance();

		auto right = parse_factor(); //Recursively call parse_factor to ensure the correct right-associativity of exponentiation

		if (!left || !right) { 
			throw std::runtime_error("Invalid binary operation in exponentation");
		}

		auto node = std::make_shared<ExpressionNode>(t); 
		node->left = left; 
		node->right = right; 
		left->parent = node; 
		right->parent = node; 
		return node; 
	}
	return left; 
}

/* parse_assignment: Parses assignment expressions, by handling the assignment operations ensuring the correct order
				of operations when evaluating the LHS and the RHS*/
ExpressionNodePtr Parser::parse_assignment() {
	auto left = parse_expression(); 

	if (current_token().getType() == TokenType::Equal) {

		if (left->token.getType() != TokenType::Variable) {
			throw std::runtime_error("Invalid left-hand side in assignment.");
		}
		advance();

		auto right = parse_expression();

		auto node = std::make_shared<ExpressionNode>(Token(TokenType::Equal, "="));
		node->left = left;
		node->right = right;
		left->parent = node;
		right->parent = node;

		return node;
	}
	return left; 
	
}

/* parse_unary: Parses unary operations (negation) */
ExpressionNodePtr Parser::parse_unary() {
	if (current_token().getType() == TokenType::Subtraction) {
		advance(); 

		auto operand = parse_primary(); 
		if (!operand) {
			throw std::runtime_error("Invalid unary operation: missing operand after '-'");
		}

		auto node = std::make_shared<ExpressionNode>(Token(TokenType::Multiplication, "*")); 
		node->left = std::make_shared<ExpressionNode>(Token(TokenType::Number, "-1")); 
		node->right = operand; 
		node->left->parent = node; 
		node->right->parent = node; 

		return node; 
	}
	return parse_primary(); 
}

/* visualize_tree: Converts the expression tree into a visual string representation */
std::string Parser::visualize_tree(ExpressionNodePtr node) {
	if (!node) return ""; 

	std::string result = node->token.getValue(); 

	if (node->left || node->right) {
		result += " (" + visualize_tree(node->left) + ", " + visualize_tree(node->right) + ")"; 
	}	

	return result; 
}

/* check_parentheses: Checks for balanced parentheses in a list of tokens */
void Parser::check_parentheses_balance() {
	int count = 0; 

	for (const auto& token : tokens) {
		if (token.getType() == TokenType::OpenParenthesis) {
			count++; 
		}
		else if (token.getType() == TokenType::CloseParenthesis) {
			count--; 
		}

		if (count < 0) {
			throw std::runtime_error("Expected ')' before matching '('");
		}
	}

	if (count != 0) {
		throw std::runtime_error("Mismatched parentheses");
	}
}

/* is_primary: Checks if a token represents a primary expression*/
bool Parser::is_primary(const Token& token) {
	return token.getType() == TokenType::Number || token.getType() == TokenType::OpenParenthesis || 
		   token.getType() == TokenType::Variable || token.getType() == TokenType::Sqrt; 
}

/* peak: Peeks ahead to see if the next token in the list matches the given type without advancing the parser*/
bool Parser::peek(TokenType type) const {
	if (position < tokens.size()) {
		return tokens[position].getType() == type; 
	}
	else {
		return false; 
	}
}