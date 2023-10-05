#pragma once

#include <vector> 
#include "Token.h"
#include "Expression_node.h"
#include "Utility.h"

/*-----Parser.h------------------------------------------------
    The Parser class is engineered to transform a sequence of tokens into
    an Abstract Syntax Tree (AST), which represents the structure and
    hierarchy of the parsed mathematical expression.

    Core features and functions include:
        - Constructing an AST from a token list.
        - Producing a visual string representation of the AST.
        - Handling errors arising from unexpected tokens and unbalanced parentheses.

    Typical usage entails:
        1. Initializing the Parser with a list of tokens:
            std::vector<Token> tokens = {...}
        2. Generating the AST:
            auto root = parser.parse();
        3. Optionally, converting the AST to a visual string form:
            std::string treeView = parser.visualize_tree(root);

    A few considerations:
        - Parsing respects the inherent precedence of mathematical operations.
        - Any encountered unbalanced parentheses or unexpected tokens will trigger runtime exceptions.

----------------------------------------------------------------*/

class Parser {
private:
    std::vector<Token> tokens;  // Queue of tokens awaiting parsing.
    size_t position;            // Current index within the token queue.

    /* Fetches the current token, based on the parser's position. */
    Token current_token() const;

    /* Advances the internal counter to the subsequent token. */
    void advance();

    /* Various parsing functions, each handling different precedence levels and token structures. */
    ExpressionNodePtr parse_primary();
    ExpressionNodePtr parse_expression();
    ExpressionNodePtr parse_unary();
    ExpressionNodePtr parse_term();
    ExpressionNodePtr parse_sqrt();
    ExpressionNodePtr parse_factor();
    ExpressionNodePtr parse_assignment();

    /* Ensures parentheses are symmetrically balanced within the token sequence. */
    void check_parentheses_balance();

    /* Determines if a given token signifies a primary expression. */
    bool is_primary(const Token& token);

    /* Peeks at the upcoming token to see if it matches a specified type, without progressing the parser. */
    bool peek(TokenType type) const;

public:
    /* Constructor: Sets up the parser using a given list of tokens. */
    explicit Parser(const std::vector<Token>& tokens);

    /* Transforms the token list into a corresponding AST. */
    std::vector<ExpressionNodePtr> parse();

    /* Generates a visual string depiction of the given AST node and its descendants. */
    std::string visualize_tree(ExpressionNodePtr node);
};