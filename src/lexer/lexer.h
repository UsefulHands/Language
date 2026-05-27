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

typedef enum Keyword {
    KEYWORD_WHILE,
    KEYWORD_IF,
    KEYWORD_RETURN,
    KEYWORD_TRUE,
    KEYWORD_FALSE,
    KEYWORD_NULL,
    KEYWORD_AND,
    KEYWORD_OR,
    KEYWORD_NOT,
    KEYWORD_METHOD,
    KEYWORD_NUMBER,
    KEYWORD_STRING,
    KEYWORD_BOOL,
    KEYWORD_BREAK,
} Keyword;

typedef enum Operator {
    OPERATOR_PLUS,
    OPERATOR_MINUS,
    OPERATOR_MULTI,
    OPERATOR_DIVIDE,
    OPERATOR_GREATER_T,
    OPERATOR_LESSER_T,
    OPERATOR_ASSIGN,
    OPERATOR_EQUALS,
    OPERATOR_NOT_EQU,
    OPERATOR_EQU_GREATER_T,
    OPERATOR_EQU_LESSER_T
} Operator;

typedef enum Punctuation {
    PUNCTUATION_BRACES_OPEN,
    PUNCTUATION_BRACES_CLOSED,
    PUNCTUATION_PARENTH_OPEN,
    PUNCTUATION_PARENTH_CLOSED,
    PUNCTUATION_SQUARE_B_OPEN,
    PUNCTUATION_SQUARE_B_CLOSED,
    PUNCTUATION_SEMICOLON,
    PUNCTUATION_COMMA,
    PUNCTUATION_DOT
} Punctuation;

extern char* tokenTypeAsString[];

typedef struct TokenCategory {
    TokenType type;
    int subType;
} TokenCategory;

typedef struct Token {
    TokenCategory category;
    char* value;
} Token;

// private
Token* getTokens(char* sentence, int* tokenCount); // I am keeping this for testers.
// public
Token* loadTokensFromBuffer(char* charBuffer, int* tokenCount);

#endif