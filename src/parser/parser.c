#include "parser.h"

void startParser(Token* tokens) {
    Parser parser;
    parser.tokens = tokens;
    parser.index = 0;
    //program will be the main function of the grammar.
    //program(&parser);
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