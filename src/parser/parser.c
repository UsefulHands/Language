#include "parser.h"
#include "../grammar/grammar.h"
#include <stdio.h>

int startParser(char* charBuffer, Token* tokens) {
    Parser parser;
    parser.tokens = tokens;
    parser.index = 0;
    int success = programPar(&parser);
    printf("\nParser success: %d", success);
    return success;
}

int getCurrIndexPar(Parser* parser) {
    return parser->index;
}

void restorePar(Parser* parser, int saved) {
    parser->index = saved;
}

Token advancePar(Parser* parser) {
    return parser->tokens[++parser->index];
}

Token retreatPar(Parser* parser) {
    return parser->tokens[--parser->index];
}

Token currPar(Parser* parser) {
    return parser->tokens[parser->index];
}