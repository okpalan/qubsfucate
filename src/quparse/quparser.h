#ifndef QUPARSER_H
#define QUPARSER_H

#include "qutokenizer.h"

// AST Node Types
typedef enum {
    AST_NODE_IDENTIFIER,
    AST_NODE_KEYWORD,
    AST_NODE_CONSTANT,
    AST_NODE_OPERATOR,
    AST_NODE_EXPRESSION,
    AST_NODE_STATEMENT,
    AST_NODE_UNKNOWN
} QuASTNodeType;

// AST Node Structure
typedef struct QuASTNode {
    QuASTNodeType type;
    char *value;
    struct QuASTNode *left;   // Left child (for expressions, etc.)
    struct QuASTNode *right;  // Right child (for binary operations, etc.)
} QuASTNode;

// Function prototypes
QuASTNode* Qu_parseExpression(QuToken **tokens, int *index);
QuASTNode* Qu_parseStatement(QuToken **tokens, int *index);
QuASTNode* Qu_parseProgram(QuToken **tokens, int *index);
void Qu_freeAST(QuASTNode *node);

#endif // QUPARSER_H
