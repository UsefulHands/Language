#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexer.h"

typedef struct Parser {
    Token* tokens;
    int index;
} Parser;

void startParser(Token* tokens);

#endif