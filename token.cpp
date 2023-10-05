#include "Token.h"

/* constructor */
Token::Token(TokenType type, const std::string& value) : type(type), value(value) {}

/* getType: Returns the type of token */
TokenType Token::getType() const {
    return type;
}

/* getValue: Returns the value of the token */
const std::string& Token::getValue() const {
    return value;
}