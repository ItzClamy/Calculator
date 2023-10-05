#pragma once
#include <memory>
#include "Token.h"
/*-------ExpressionNode.h-------------------------------------------------
    This header file defines the building blocks for the expression tree.
    It describes an expression node, which consists of a token (representing
    a value or operation) and points to child nodes for binary operations.      

    Key functionalities include:
        - A constructor: Initializes an expression node with a specific token.
        - Token: Holds the value or operation this node represents.
        - Left and Right: Pointers to left and right child nodes.
        - Parent: Pointer to the parent node. This can be useful for certain
                  tree-manipulation algorithms.

    The ExpressionNodePtr is a typedef for a shared pointer to an ExpressionNode.
    Using shared pointers simplifies memory management for the tree structure.

----------------------------------------------------------------------------*/

class ExpressionNode; 
using ExpressionNodePtr = std::shared_ptr<ExpressionNode>;  // Define a shared pointer to ExpressionNode for easier management.

class ExpressionNode {
public: 
    Token token;                   // The value or operation this node represents.
    ExpressionNodePtr left;        // Pointer to the left child node.
    ExpressionNodePtr right;       // Pointer to the right child node.
    ExpressionNodePtr parent;      // Pointer to the parent node.

    /* Constructor: Initializes an expression node with a specific token. */
    explicit ExpressionNode(const Token& token);
};