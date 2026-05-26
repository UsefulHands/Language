#include "lexer.h"
#include "../sourceBuffer/sourceBuffer.h"
#include <string.h>
#include <stdlib.h>

char* tokenTypeAsString[] = {
    "TOKEN_EOF",
    "TOKEN_IDENTIFIER",
    "TOKEN_NUMBER",
    "TOKEN_STRING",
    "TOKEN_OPERATOR",
    "TOKEN_KEYWORD",
    "TOKEN_PUNCTUATION",
    "TOKEN_NULL",
    "TOKEN_INVALID",
};

typedef struct KeywordMap {
    char* word;
    Keyword keyword;
} KeywordMap;

KeywordMap keywordMap[] = {
    {"while", KEYWORD_WHILE},
    {"if", KEYWORD_IF},
    {"return", KEYWORD_RETURN},
    {"true", KEYWORD_TRUE},
    {"false", KEYWORD_FALSE},
    {"null", KEYWORD_NULL},
    {"and", KEYWORD_AND},
    {"or", KEYWORD_OR},
    {"not", KEYWORD_NOT},
    {"method", KEYWORD_METHOD},
    {"number", KEYWORD_NUMBER},
    {"break", KEYWORD_BREAK},
};

int keywordMapSize = sizeof(keywordMap) / sizeof(keywordMap[0]);

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
    {"]", PUNCTUATION_SQUARE_B_CLOSED},
    {";", PUNCTUATION_SEMICOLON},
    {",", PUNCTUATION_COMMA},
    {".", PUNCTUATION_DOT},
};

int punctuationMapSize = sizeof(punctuationMap) / sizeof(punctuationMap[0]);

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

TokenCategory getTokenCategory(char* token) {
    TokenCategory category;
    category.type = TOKEN_INVALID;
    category.subType = -1;
    if(token == NULL) {
        category.type = TOKEN_NULL;
        return category;
    }
    int len = strlen(token);
    if(len == 0) {
        category.type = TOKEN_EOF;
        return category;
    }
    if(len >= 2 && token[0] == '"' && token[len - 1] == '"') {
        category.type = TOKEN_STRING;
        return category;
    } else if(isValidNumber(token) != 0) {
        category.type = TOKEN_NUMBER;
        return category;
    }
    for(int i = 0; i < keywordMapSize; i++) {
        if(strcmp(keywordMap[i].word, token) == 0) {
            category.type = TOKEN_KEYWORD;
            category.subType = keywordMap[i].keyword;
            return category;
        }
    }
    if(isValidIdentifier(token) != 0) {
        category.type = TOKEN_IDENTIFIER;
        return category;
    }
    for(int i = 0; i < operatorMapSize; i++) {
        if(strcmp(operatorMap[i].word, token) == 0) {
            category.type = TOKEN_OPERATOR;
            category.subType = operatorMap[i].operator;
            return category;
        }
    }
    for(int i = 0; i < punctuationMapSize; i++) {
        if(strcmp(punctuationMap[i].word, token) == 0) {
            category.type = TOKEN_PUNCTUATION;
            category.subType = punctuationMap[i].punctuation;
            return category;
        }
    } 
    return category;
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
        while(sentence[i] == ' ' || sentence[i] == '\n' || sentence[i] == '\r') i++;
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
                while(sentence[i] != ' ' && sentence[i] != '\0' && sentence[i] != '\n' && sentence[i] != '\r') {
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
            TokenCategory category = getTokenCategory(token);
            tokens[*tokenCount].category = category;
            tokens[*tokenCount].value = token;
            (*tokenCount)++;
        }
    }
    tokens = realloc(tokens, sizeof(Token) * (*tokenCount + 1));
    return tokens;
}

Token* loadTokensFromBuffer(char* charBuffer, int* tokenCount) {
    if(charBuffer == NULL) return NULL;
    Token* tokens = getTokens(charBuffer, tokenCount);
    return tokens;
}