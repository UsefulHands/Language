#include "parser.h"

void startParser(Token* tokens) {
    Parser parser;
    parser.tokens = tokens;
    parser.index = 0;
    //program will be the main function of the grammar.
    //program(&parser);
}