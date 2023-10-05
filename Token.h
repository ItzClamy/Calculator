#pragma once
#include <string>

/*------Token.h----------------------------------------------------------
    This header file introduces the Token entity, a foundational unit
    employed throughout the program for representation and processing
    of mathematical constructs.

    Key components:
        - Enumeration of various token types (e.g., operators, numbers, functions).
        - Token class to encapsulate type and value of individual tokens.

    Core functionalities:
        - Initialization: Constructs a token with a specified type and value.
        - Type Retrieval: Offers insight into the category or kind of a token.
        - Value Access: Yields the precise textual representation or content of the token.

    The Token plays an instrumental role in stages of lexical analysis and parsing,
    providing a structured way to comprehend and manipulate expressions.
--------------------------------------------------------------------------*/

enum class TokenType
{
    Number,            // Numeric literals.
    Addition,          // Addition operator ('+').
    Subtraction,       // Subtraction operator ('-').
    Multiplication,    // Multiplication operator ('*').
    Division,          // Division operator ('/').
    Exponents,         // Exponentiation operator ('^').
    OpenParenthesis,   // Opening parenthesis ('(').
    CloseParenthesis,  // Closing parenthesis (')').
    Sqrt,              // Square root function/operator.
    Equal,             // Equality operator ('=').
    Variable,          // Variable identifiers.
    Error,             // Signifier for tokenization anomalies.
    End                // Termination symbol in input.
};

class Token {
public:
    // Constructor: Initializes a token with designated type and value.
    Token(TokenType type, const std::string& value);

    // Accessor methods to glean token attributes.
    TokenType getType() const;           // Fetches the token's type.
    const std::string& getValue() const; // Retrieves the token's value.

private:
    TokenType type;      // Categorization of the token.
    std::string value;   // Textual representation or content of the token.
};
