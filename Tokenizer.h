#include <string>
#include <vector>
#include "Token.h"
#include "Utility.h"
#pragma once

/*-------Tokenizer.h-----------------------------------------------------
    The Tokenizer class is pivotal in the conversion of a mathematical
    expression string into its constituent tokens. This tokenized form
    facilitates subsequent parsing and evaluation.

    Principal features encompass:
        - Initialization: Constructs the Tokenizer with a specific input expression.
        - Token Generation: Decomposes the input expression into individual tokens.
        - Character Reading: Recognizes individual characters or tokens from the expression.

    Specifically, the Tokenizer:
        - Derives numbers, operators, keywords (like sqrt), variables, and parenthesis tokens.
        - Keeps a running tab on its position within the expression string.

    Generally used in the preliminary stages of an expression evaluation pipeline to
    prepare the input for further processing.
------------------------------------------------------------------------*/

class Tokenizer {
private:
    std::string expression;      // The mathematical expression to be tokenized.
    size_t position;             // Tracker of the current position within the expression.

    /* Helper functions for internal operation. */ 
    char current_char();         // Retrieves the character at the current index.
    void advance();              // Steps forward to the subsequent character.

    /* Dedicated functions for identifying different types of tokens. */
    Token next_token();          // Fetches the subsequent token from the expression.
    Token read_number();         // Isolates and returns a numeric token.
    Token read_operator();       // Isolates and returns an operator token.
    Token read_keyword();        // Isolates and returns a keyword token.
    Token read_variable();       // Isolates and returns a variable token.
    Token read_parenthesis();    // Isolates and returns a parenthesis token.

public:
    /* Constructor : Preps the tokenizer with a designated expression string. */ 
    explicit Tokenizer(const std::string& expression);

    /* Main function : Decomposes the expression into a list of tokens. */
    std::vector<Token> tokenize();
};