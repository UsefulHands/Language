#include "grammar.h"
#include "../lexer/lexer.h"

int paramList(Parser* parser) {
    Token token = parser->tokens[parser->index];
    if(token.category.type != TOKEN_IDENTIFIER) return 0;
    parser->index++;
    token = parser->tokens[parser->index];
    while(1) {
        if(token.category.type == TOKEN_PUNCTUATION 
            && token.category.subType == PUNCTUATION_COMMA) {
            parser->index++;
            token = parser->tokens[parser->index]; 
            if(token.category.type != TOKEN_IDENTIFIER) {
                return 0;
            }
            parser->index++;
            token = parser->tokens[parser->index];
        } else {
            break;
        }
    }
    return 1;
}