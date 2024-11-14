#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "qutokenizer.h"

#define MAX_TOKEN_LENGTH 100

typedef enum {
    TOKEN_IDENTIFIER = 0,
    TOKEN_KEYWORD = 1,
    TOKEN_CONSTANT = 2,
    TOKEN_STRING_LITERAL = 3,
    TOKEN_OPERATOR = 4,
    TOKEN_PUNCTUATOR = 5,
    TOKEN_PREPROCESSOR = 6,
    TOKEN_UNKNOWN = 7
} QuTokenType;

typedef struct {
    QuTokenType type;
    char *value;
} QuToken;

// Function prototypes with updated naming convention
QuToken *Qu_createToken(QuTokenType type, const char *value);
void Qu_freeToken(QuToken *token);
int Qu_isKeyword(const char *word);
void Qu_tokenize(const char *code);

// Function definitions
QuToken *Qu_createToken(QuTokenType type, const char *value) {
    QuToken *token = (QuToken *)malloc(sizeof(QuToken));
    token->type = type;
    token->value = (char *)malloc(strlen(value) + 1);
    strcpy(token->value, value);
    return token;
}

void Qu_freeToken(QuToken *token) {
    if (token) {
        free(token->value);
        free(token);
    }
}

int Qu_isKeyword(const char *word) {
    const char *keywords[] = {"int", "return", "void", "if", "else", "while", "for", "break", "continue"};
    int num_keywords = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void Qu_tokenize(const char *code) {
    const char *delimiters = " \t\n\r;(){}[]";
    char buffer[MAX_TOKEN_LENGTH];
    int buffer_index = 0;
    QuTokenType current_type = TOKEN_UNKNOWN;

    for (int i = 0; code[i] != '\0'; i++) {
        char c = code[i];
        if (strncmp(buffer, "#include", 8) == 0 && (buffer_index == 8)) {
            buffer[buffer_index] = '\0';
            QuToken *token = Qu_createToken(TOKEN_PREPROCESSOR, buffer);
            printf("Token: Type=%d, Value=%s\n", token->type, token->value);
            Qu_freeToken(token);
            buffer_index = 0;
            current_type = TOKEN_UNKNOWN;
        }

        // Handle punctuation and preprocessor separately
        if (c == '#') {
            if (buffer_index > 0) { // Output current buffer as token if not empty
                buffer[buffer_index] = '\0';
                QuToken *token = Qu_createToken(current_type, buffer);
                printf("Token: Type=%d, Value=%s\n", token->type, token->value);
                Qu_freeToken(token);
                buffer_index = 0;
            }
            // Start a new preprocessor token
            current_type = TOKEN_PREPROCESSOR;
            buffer[buffer_index++] = c;
        } else if (c == '<' || c == '>') { 
            if (buffer_index > 0) { // Output current buffer as token if not empty
                buffer[buffer_index] = '\0';
                QuToken *token = Qu_createToken(current_type, buffer);
                printf("Token: Type=%d, Value=%s\n", token->type, token->value);
                Qu_freeToken(token);
                buffer_index = 0;
            }
            // Treat `<` and `>` as separate tokens
            QuToken *token = Qu_createToken(TOKEN_PUNCTUATOR, (c == '<') ? "<" : ">");
            printf("Token: Type=%d, Value=%s\n", token->type, token->value);
            Qu_freeToken(token);
            current_type = TOKEN_UNKNOWN;
        } else if (c == '(' || c == ')' || c == '{' || c == '}') {
            if (buffer_index > 0) {
                buffer[buffer_index] = '\0';
                QuToken *token = Qu_createToken(current_type, buffer);
                printf("Token: Type=%d, Value=%s\n", token->type, token->value);
                Qu_freeToken(token);
                buffer_index = 0;
            }
            char punct[2] = {c, '\0'};
            QuToken *token = Qu_createToken(TOKEN_PUNCTUATOR, punct);
            printf("Token: Type=%d, Value=%s\n", token->type, token->value);
            Qu_freeToken(token);
            current_type = TOKEN_UNKNOWN;
        } else if (strchr(delimiters, c)) {
            if (buffer_index > 0) {
                buffer[buffer_index] = '\0';
                if (Qu_isKeyword(buffer)) {
                    current_type = TOKEN_KEYWORD;
                } else if (isdigit(buffer[0])) {
                    current_type = TOKEN_CONSTANT;
                } else {
                    current_type = TOKEN_IDENTIFIER;
                }
                QuToken *token = Qu_createToken(current_type, buffer);
                printf("Token: Type=%d, Value=%s\n", token->type, token->value);
                Qu_freeToken(token);
                buffer_index = 0;
            }
            current_type = TOKEN_UNKNOWN;
        } else {
            buffer[buffer_index++] = c;
            if (isalpha(c) || c == '_') {
                current_type = TOKEN_IDENTIFIER;
            } else if (isdigit(c)) {
                current_type = TOKEN_CONSTANT;
            } else {
                current_type = TOKEN_UNKNOWN;
            }
        }
    }

    if (buffer_index > 0) {
        buffer[buffer_index] = '\0';
        if (Qu_isKeyword(buffer)) {
            current_type = TOKEN_KEYWORD;
        } else if (isdigit(buffer[0])) {
            current_type = TOKEN_CONSTANT;
        } else {
            current_type = TOKEN_IDENTIFIER;
        }
        QuToken *token = Qu_createToken(current_type, buffer);
        printf("Token: Type=%d, Value=%s\n", token->type, token->value);
        Qu_freeToken(token);
    }
}

