#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexer.h"

typedef struct Parser {
    Token* tokens;
    int index;
} Parser;

void startParser(char* charBuffer, Token* tokens);

int getCurrIndex(Parser* parser);
void restore(Parser* parser, int saved);
Token advance(Parser* parser);
Token retreat(Parser* parser);
Token curr(Parser* parser);

#endif