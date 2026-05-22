#include "lexer.h"
#include <string.h>
#include <stdlib.h>

typedef enum Keyword {
    KEYWORD_FOR,
    KEYWORD_WHILE,
    KEYWORD_IF,
    KEYWORD_RETURN,
} Keyword;

typedef struct KeywordMap {
    char* word;
    Keyword keyword;
} KeywordMap;

KeywordMap keywordMap[] = {
    {"for", KEYWORD_FOR},
    {"while", KEYWORD_WHILE},
    {"if", KEYWORD_IF},
    {"return", KEYWORD_RETURN}
};

int keywordMapSize = sizeof(keywordMap) / sizeof(keywordMap[0]);

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

typedef struct OperatorMap {
    char* word;
    Operator operator;
} OperatorMap;

OperatorMap operatorMap[] = {
    {"+", OPERATOR_PLUS},
    {"-", OPERATOR_MINUS},
    {"*", OPERATOR_MULTI},
    {"/", OPERATOR_DIVIDE},
    {">", OPERATOR_GREATER_T},
    {"<", OPERATOR_LESSER_T},
    {"=", OPERATOR_ASSIGN},
    {"==", OPERATOR_EQUALS},
    {"!=", OPERATOR_NOT_EQU},
    {">=", OPERATOR_EQU_GREATER_T},
    {"<=", OPERATOR_EQU_LESSER_T},
};

int operatorMapSize = sizeof(operatorMap) / sizeof(operatorMap[0]);

typedef enum Punctuation {
    PUNCTUATION_BRACES_OPEN,
    PUNCTUATION_BRACES_CLOSED,
    PUNCTUATION_PARENTH_OPEN,
    PUNCTUATION_PARENTH_CLOSED,
    PUNCTUATION_SQUARE_B_OPEN,
    PUNCTUATION_SUQARE_B_CLOSED,
    PUNCTUATION_SEMICOLON,
    PUNCTUATION_COMMA,
} Punctuation;

typedef struct PunctuationMap {
    char* word;
    Punctuation punctuation;
} PunctuationMap;

PunctuationMap punctuationMap[] = {
    {"{", PUNCTUATION_BRACES_OPEN},
    {"}", PUNCTUATION_BRACES_CLOSED},
    {"(", PUNCTUATION_PARENTH_OPEN},
    {")", PUNCTUATION_PARENTH_CLOSED},
    {"[", PUNCTUATION_SQUARE_B_OPEN},
    {"]", PUNCTUATION_SUQARE_B_CLOSED},
    {";", PUNCTUATION_SEMICOLON},
    {",", PUNCTUATION_COMMA},
};

int punctuationMapSize = sizeof(punctuationMap) / sizeof(punctuationMap[0]);

int getTokenCount(char* sentence) {
    if(sentence == NULL) return 0;
    int result = 0;
    int i = 0;
    while(sentence[i] != '\0'){
        while(sentence[i] == ' ') {
            i++;
        }
        if(sentence[i] == '\0'){
            break;
        }
        while(sentence[i] != ' ' && sentence[i] != '\0') {
            i++;
        }
        result++;
    }
    return result;
}

int isValidIdentifier(char* token) {
    if(token == NULL) return 0;
    int len = strlen(token);
    if (len == 0) return 0;
    if(!((token[0] >= 'a' && token[0] <= 'z') || (token[0] >= 'A' && token[0] <= 'Z'))) return 0;
    for(int i = 1; i < len; i++){
        if(!((token[i] >= 'a' && token[i] <= 'z') || (token[i] >= 'A' && token[i] <= 'Z') || (token[i] >= '0' && token[i] <= '9'))) return 0;
    }
    return 1;
}

int isValidNumber(char* token){
    if(token == NULL) return 0;
    int len = strlen(token);
    if (len == 0) return 0;
    if(!((token[0] >= '0' && token[0] <= '9') || ( len >= 2 && (token[0] == '+' || token[0] == '-')))) return 0;
    for(int i = 1; i < len; i++) {
        if(!(token[i] >= '0' && token[i] <= '9')) return 0;
    }
    return 1;
}

TokenType getTokenType(char* token) {
    if(token == NULL) return TOKEN_NULL;
    int len = strlen(token);
    if(len == 0) return TOKEN_EOF;
    if(len >= 2 && token[0] == '"' && token[len - 1] == '"') return TOKEN_STRING;
    if(isValidNumber(token) != 0) return TOKEN_NUMBER;
    for(int i = 0; i < keywordMapSize; i++) {
        if(strcmp(keywordMap[i].word, token) == 0) return TOKEN_KEYWORD;
    }
    if(isValidIdentifier(token) != 0) return TOKEN_IDENTIFIER;
    for(int i = 0; i < operatorMapSize; i++) {
        if(strcmp(operatorMap[i].word, token) == 0) return TOKEN_OPERATOR;
    }
    for(int i = 0; i < punctuationMapSize; i++) {
        if(strcmp(punctuationMap[i].word, token) == 0) return TOKEN_PUNCTUATION;
    }    
    return TOKEN_INVALID;
}

// int tokenCount = 0;
// getTokens(..., &tokenCount);
// To get token count, I am passing a reference of tokenCount assigned 0.
Token* getTokens(char* sentence, int* tokenCount) {
    if(sentence == NULL) return NULL;
    int capacity = 4;
    Token* tokens = malloc(sizeof(Token) * capacity);
    int i = 0;
    while(sentence[i] != '\0') {
        while(sentence[i] == ' ') i++;
        if(sentence[i] == '\0') break;
        if(sentence[i] != ' ' && sentence[i] != '\0') {
            int currentTokenLen = 0;
            int currentTokenStartIndex = i;
            int isOperator = 0;
            int isPunctuation = 0;
            if(
                ((sentence[i] == '+' || sentence[i] == '-') && (sentence[i + 1] < '0' || sentence[i + 1] > '9'))
                || sentence[i] == '*'
                || sentence[i] == '/'
                || sentence[i] == '='
                || sentence[i] == '!'
                || sentence[i] == '>'
                || sentence[i] == '<'
            ) {
                currentTokenLen = 1;
                isOperator = 1;
                i++;
                if(sentence[i] == '=') {
                    currentTokenLen = 2;
                    i++;
                }
            }
            if(
                sentence[i] == '{' 
                || sentence[i] == '}' 
                || sentence[i] == '(' 
                || sentence[i] == ')' 
                || sentence[i] == '[' 
                || sentence[i] == ']'  
                || sentence[i] == ';'
                || sentence[i] == ','
            ) {
                currentTokenLen = 1;
                isPunctuation = 1;
                i++;
            }
            if(isOperator == 0 && isPunctuation == 0) {
                while(sentence[i] != ' ' && sentence[i] != '\0') {
                    currentTokenLen++;
                    i++;
                }
            }
            char* token = malloc(sizeof(char) * (currentTokenLen + 1));
            for(int j = 0; j < currentTokenLen; j++) {
                token[j] = sentence[currentTokenStartIndex + j];
            }
            token[currentTokenLen] = '\0';
            if(*tokenCount >= capacity) {
                capacity *= 2;
                tokens = realloc(tokens, sizeof(Token) * capacity);
            }
            tokens[*tokenCount].type = getTokenType(token);
            tokens[*tokenCount].value = token;
            (*tokenCount)++;
        }
    }
    tokens = realloc(tokens, sizeof(Token) * (*tokenCount + 1));
    return tokens;
}