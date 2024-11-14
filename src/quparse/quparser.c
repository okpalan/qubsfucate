#include "quparser.h"
#include <stdlib.h>
#include <string.h>

// Helper function to create AST nodes
QuASTNode* Qu_createASTNode(QuASTNodeType type, const char *value) {
    QuASTNode *node = (QuASTNode*)malloc(sizeof(QuASTNode));
    node->type = type;
    node->value = strdup(value);  // Allocate memory for the value
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Parsing an expression (simplified for demonstration)
QuASTNode* Qu_parseExpression(QuToken **tokens, int *index) {
    if (tokens[*index]->type == TOKEN_IDENTIFIER || tokens[*index]->type == TOKEN_CONSTANT) {
        // Create a node for an identifier or constant
        QuASTNode *node = Qu_createASTNode(AST_NODE_EXPRESSION, tokens[*index]->value);
        (*index)++; // Move to the next token
        return node;
    }
    return NULL; // Handle errors or unexpected token types
}

// Parsing a statement (e.g., an expression or simple statement)
QuASTNode* Qu_parseStatement(QuToken **tokens, int *index) {
    QuASTNode *node = Qu_parseExpression(tokens, index);
    if (node != NULL) {
        return node;
    }
    return NULL; // Add more logic for statements
}

// Parsing the program as a whole (parse a list of statements)
QuASTNode* Qu_parseProgram(QuToken **tokens, int *index) {
    QuASTNode *root = NULL;
    while (tokens[*index] != NULL) {
        QuASTNode *stmt = Qu_parseStatement(tokens, index);
        if (stmt != NULL) {
            // For simplicity, link statements as a chain
            if (root == NULL) {
                root = stmt;
            } else {
                QuASTNode *last = root;
                while (last->right != NULL) {
                    last = last->right;
                }
                last->right = stmt;
            }
        }
    }
    return root;
}

// Free the memory allocated for the AST
void Qu_freeAST(QuASTNode *node) {
    if (node) {
        if (node->value) free(node->value);
        Qu_freeAST(node->left);
        Qu_freeAST(node->right);
        free(node);
    }
}
