#include "parser.h"
#include "../grammar/grammar.h"
#include <stdio.h>

void startParser(char* charBuffer, Token* tokens) {
    Parser parser;
    parser.tokens = tokens;
    parser.index = 0;
    int success = program(&parser);
    printf("\nCharBuffer:\n\n%s\n", charBuffer);
    printf("\nParser success: %d", success);
}

int getCurrIndex(Parser* parser) {
    return parser->index;
}

void restore(Parser* parser, int saved) {
    parser->index = saved;
}

Token advance(Parser* parser) {
    return parser->tokens[++parser->index];
}

Token retreat(Parser* parser) {
    return parser->tokens[--parser->index];
}

Token curr(Parser* parser) {
    return parser->tokens[parser->index];
}