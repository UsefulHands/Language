#ifndef LEXER_H
#define LEXER_H

typedef enum TokenType {
    TOKEN_EOF,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_OPERATOR,
    TOKEN_KEYWORD,
    TOKEN_PUNCTUATION,
    TOKEN_NULL,
    TOKEN_INVALID,
} TokenType;

typedef struct Token {
    int type;
    char* value;
} Token;

Token* getTokens(char* sentence, int* tokenCount);

#endif