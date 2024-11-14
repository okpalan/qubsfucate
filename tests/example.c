// main.c
#include <stdio.h>
#include <stdlib.h>
#include "qutokenizer.h"
#include "quparser.h"

int main() {
    const char *code = "int x = 42; return x;";  // Example code to parse
    QuToken *tokens[100];  // Array to hold tokens (ensure enough space for your input)
    int token_count = 0;

    // Tokenize the code
    Qu_tokenize(code, tokens, &token_count);

    // Parse the tokens into an AST
    int index = 0;
    QuASTNode *ast = Qu_parseProgram(tokens, &index);

    // Print the resulting AST (simple representation)
    printf("Parsed AST: %s\n", ast ? ast->value : "NULL");

    // Free memory
    Qu_freeAST(ast);
    for (int i = 0; i < token_count; i++) {
        Qu_freeToken(tokens[i]);
    }

    return 0;
}
