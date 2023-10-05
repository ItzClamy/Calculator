#include "Tokenizer.h"
#include <iostream>
#include <stdexcept>
#include <cctype>

/* constructor */
Tokenizer::Tokenizer(const std::string& expression) : expression(expression), position(0) {}

/* tokenizer: Proccess the input expression and extracts all tokens in the correct order */
std::vector<Token> Tokenizer::tokenize() {
    std::vector<Token> tokens;

    Token token = next_token();
    while (token.getType() != TokenType::End) {
        tokens.push_back(token);
        token = next_token();
    }

    return tokens;
}

/* current_char: Returns the current character being processed in the expression */
char Tokenizer::current_char() {
    return expression[position];
}

/* advance: Moves to the next character in the expression string */
void Tokenizer::advance() {
    position++; 
}

/* next_token: Identifies the next token based on the current position in the expression*/
Token Tokenizer::next_token() {
    while (position < expression.size()) {
        char c = current_char(); 

        if (std::isspace(c)) {  // Skips whitespace
            advance(); 
            continue; 
        }
        else if (std::isdigit(c)) {  // Identify a numeric token
            return read_number(); 
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/'|| c == '^') {  // Identify an operator token
            return read_operator(); 
        }
        else if (std::isalpha(c)) {
            std::string name;

            // Gather all consecutive alphabetical characters
            while (std::isalpha(current_char())) {
                name.push_back(current_char());
                advance();
            }

            // Check if it's "sqrt" or a variable
            if (name == "sqrt") {
                return Token(TokenType::Sqrt, name);
            }
            else {
                return Token(TokenType::Variable, name);
            }
        }

        else if (c == '(' || c == ')') {  // Identify parenthesis tokens
            return read_parenthesis(); 
        }
        else {
            throw std::runtime_error("Invalid character encountered: " + std::string(1, c));
            advance(); 
            return Token(TokenType::Error, std::string(1, c)); 
        }
    }

    return Token(TokenType::End, "");   // Return an End token when the end of the expression is reached
}

/* read_number: Extracts a numeric token */
Token Tokenizer::read_number() {
    std::string number_str; 

    while (position < expression.size() && (std::isdigit(current_char()) || current_char() == '.')) {  // Accumulate characters that form the number
        number_str.push_back(current_char()); 
        advance(); 
    }

    TokenType token_type = TokenType::Number; 
    return Token(token_type, number_str); 
}

/* read_operator: Extracts an operator token */
Token Tokenizer::read_operator() {
    char c = current_char(); 
    advance(); 

    TokenType token_type; 
    switch (c) {
        case '+': 
            token_type = TokenType::Addition;
            break; 
        case '-': 
            token_type = TokenType::Subtraction; 
            break; 
        case '*': 
            token_type = TokenType::Multiplication; 
            break; 
        case '/': 
            token_type = TokenType::Division; 
            break; 
        case '^': 
            token_type = TokenType::Exponents; 
            break; 
        case '=': 
            token_type = TokenType::Equal; 
            break; 
        default:
            throw std::runtime_error("Invalid operator encountered");
            return Token(TokenType::Error, std::string(1, c));
    }
    return Token(token_type, std::string(1, c)); 
}

/* read_keyword: Extracts a keyword token, such as sqrt */
Token Tokenizer::read_keyword() {
    std::string keyword;

    while (std::isalpha(current_char())) {  // Accumulate characters that form the keyword
        keyword.push_back(current_char());
        advance();
    }

    if (keyword == "sqrt") {  // sqrt is the only one recognized at this moment
        return Token(TokenType::Sqrt, keyword);
    }
    else {
        throw std::runtime_error("Invalid keyword encountered");
        return Token(TokenType::Error, keyword);
    }
}


/* read_variable: Extracts a variable token */
Token Tokenizer::read_variable() {
    std::string variable_str; 

    if (!std::isalpha(current_char())) {
        throw std::runtime_error("Expected variable to start with a letter");
    }
    while (position < expression.size() && std::isalnum(current_char())) {
        variable_str.push_back(current_char()); 
        advance(); 
    }
 
    return Token(TokenType::Variable, variable_str);
}

/* read_parenthesis: extracts a parenthesis token */
Token Tokenizer::read_parenthesis() {
    char parenthesis = current_char();
    advance();

    TokenType token_type = TokenType::Error;  // Initialize token_type to a default value

    if (parenthesis == '(') {
        token_type = TokenType::OpenParenthesis;
    }
    else if (parenthesis == ')') {
        token_type = TokenType::CloseParenthesis;
    }
    else {
        throw std::runtime_error("Invalid parenthesis character encountered");
    }

    return Token(token_type, std::string(1, parenthesis));
}