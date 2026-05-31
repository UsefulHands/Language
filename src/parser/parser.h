#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexer.h"

typedef struct Parser {
    Token* tokens;
    int index;
} Parser;

int startParser(char* charBuffer, Token* tokens);

int getCurrIndexPar(Parser* parser);
void restorePar(Parser* parser, int saved);
Token advancePar(Parser* parser);
Token retreatPar(Parser* parser);
Token currPar(Parser* parser);

#endif