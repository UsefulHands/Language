#include "grammar.h"
#include "../lexer/lexer.h"

int program(Parser* parser) {
    while (stmt(parser));
    if(curr(parser).category.type == TOKEN_EOF) {
        advance(parser);
        return 1;
    } return 0;
}

int stmt(Parser* parser) {
    int startIndex = getCurrIndex(parser);
    if(declaration(parser) == 1) return 1;
    restore(parser, startIndex);
    if(expr(parser) == 1) {
        if(
            curr(parser).category.type == TOKEN_PUNCTUATION
            && curr(parser).category.subType == PUNCTUATION_SEMICOLON
        ) {
            advance(parser);
            return 1;
        }
    }
    restore(parser, startIndex);
    if(whileSTMT(parser) == 1) return 1;
    restore(parser, startIndex);
    if(ifSTMT(parser) == 1) return 1;
    restore(parser, startIndex);
    if(returnSTMT(parser) == 1) return 1;
    restore(parser, startIndex);
    if(breakSTMT(parser) == 1) return 1;
    restore(parser, startIndex);
    if(blockSTMT(parser) == 1) return 1;
    restore(parser, startIndex);
    if(methodSTMT(parser) == 1) return 1;
    return 0;
}

int declaration(Parser* parser) {
    if(typeSpec(parser) != 1) return 0;
    if(curr(parser).category.type != TOKEN_IDENTIFIER) return 0;
    advance(parser);
    if(
        curr(parser).category.type != TOKEN_OPERATOR
        || curr(parser).category.subType != OPERATOR_ASSIGN
    ) return 0;
    advance(parser);
    if(expr(parser) != 1) return 0;
    if(
        curr(parser).category.type != TOKEN_PUNCTUATION
        || curr(parser).category.subType != PUNCTUATION_SEMICOLON
    ) return 0;
    advance(parser);
    return 1;
}

int typeSpec(Parser* parser) {
    if(curr(parser).category.type != TOKEN_KEYWORD) return 0;
    if(
        curr(parser).category.subType != KEYWORD_NUMBER
        && curr(parser).category.subType != KEYWORD_STRING
        && curr(parser).category.subType != KEYWORD_BOOL
    ) return 0;
    advance(parser);
    return 1;
}

int expr(Parser* parser) {
    if(assignment(parser) == 1) return 1;
    return 0;
}

int assignment(Parser* parser) {
    int saved = getCurrIndex(parser);
    if (curr(parser).category.type == TOKEN_IDENTIFIER) {
        advance(parser);
        if (
            curr(parser).category.type == TOKEN_OPERATOR
            && curr(parser).category.subType == OPERATOR_ASSIGN
        ) {
            advance(parser);
            if (assignment(parser) == 1) return 1;
        }
    }
    restore(parser, saved);
    if (logicOr(parser) == 1) return 1;
    return 0;
}

int logicOr(Parser* parser) {
    if(logicAnd(parser) != 1) return 0;
    while(1) {
        if(
            curr(parser).category.type == TOKEN_KEYWORD
            && curr(parser).category.subType == KEYWORD_OR
        ) advance(parser);
        else break;
        if(logicAnd(parser) != 1) return 0;
    }
    return 1;
}

int logicAnd(Parser* parser) {
    if(equality(parser) != 1) return 0;
    while(1) {
        if(
            curr(parser).category.type == TOKEN_KEYWORD
            && curr(parser).category.subType == KEYWORD_AND
        ) advance(parser);
        else break;
        if(equality(parser) != 1) return 0;
    }
    return 1;
}

int equality(Parser* parser) {
    if(comparison(parser) != 1) return 0;
    while(1) {
        if(
            curr(parser).category.type == TOKEN_OPERATOR
            && (
                curr(parser).category.subType == OPERATOR_EQUALS 
                || curr(parser).category.subType == OPERATOR_NOT_EQU    
                )
        ) advance(parser);
        else break;
        if(comparison(parser) != 1) return 0;
    }
    return 1;
}

int comparison(Parser* parser) {
    if(term(parser) != 1) return 0;
    while(1) {
        if(
            curr(parser).category.type == TOKEN_OPERATOR
            && (
                curr(parser).category.subType == OPERATOR_GREATER_T 
                || curr(parser).category.subType == OPERATOR_LESSER_T
                || curr(parser).category.subType == OPERATOR_EQU_GREATER_T
                || curr(parser).category.subType == OPERATOR_EQU_LESSER_T    
                )
        ) advance(parser);
        else break;
        if(term(parser) != 1) return 0;
    }
    return 1;
}

int term(Parser* parser) {
    if(factor(parser) != 1) return 0;
    while(1) {
        if(
            curr(parser).category.type == TOKEN_OPERATOR
            && (
                curr(parser).category.subType == OPERATOR_PLUS 
                || curr(parser).category.subType == OPERATOR_MINUS    
                )
        ) advance(parser);
        else break;
        if(factor(parser) != 1) return 0;
    }
    return 1;
}

int factor(Parser* parser) {
    if(unary(parser) != 1) return 0;
    while(1) {
        if(
            curr(parser).category.type == TOKEN_OPERATOR
            && (
                curr(parser).category.subType == OPERATOR_MULTI 
                || curr(parser).category.subType == OPERATOR_DIVIDE    
                )
        ) advance(parser);
        else break;
        if(unary(parser) != 1) return 0;
    }
    return 1;
}

int unary(Parser* parser) {
    if(
        curr(parser).category.type == TOKEN_KEYWORD
        && curr(parser).category.subType == KEYWORD_NOT
    ) {
        advance(parser);
        return unary(parser);
    }
    return primary(parser);
}

int primary(Parser* parser) {
    if(curr(parser).category.type == TOKEN_NUMBER) {
        advance(parser);
        return 1;
    }
    if(curr(parser).category.type == TOKEN_STRING) {
        advance(parser);
        return 1;
    }
    if(curr(parser).category.type == TOKEN_IDENTIFIER) {
        advance(parser);
        while(1) {
            if(
                curr(parser).category.type == TOKEN_PUNCTUATION
                && curr(parser).category.subType == PUNCTUATION_DOT
            ) {
                advance(parser);
                if(curr(parser).category.type == TOKEN_IDENTIFIER) {
                    advance(parser);
                } 
                else return 0;
            }
            else break;
        }
        if(
            curr(parser).category.type == TOKEN_PUNCTUATION
            && curr(parser).category.subType == PUNCTUATION_SQUARE_B_OPEN
        ) {
            advance(parser);
            if(expr(parser) == 0) return 0;
            if(
                curr(parser).category.type == TOKEN_PUNCTUATION
                && curr(parser).category.subType == PUNCTUATION_SQUARE_B_CLOSED
            ) advance(parser);
            else return 0;
        }
        return 1;
    }
    if(
        curr(parser).category.type == TOKEN_KEYWORD
        && (
            curr(parser).category.subType == KEYWORD_TRUE
            || curr(parser).category.subType == KEYWORD_FALSE
            || curr(parser).category.subType == KEYWORD_NULL
        )
    ) {
        advance(parser);
        return 1;
    }
    if(
        curr(parser).category.type == TOKEN_PUNCTUATION
        && curr(parser).category.subType == PUNCTUATION_PARENTH_OPEN
    ) {
        advance(parser);
        if(expr(parser) == 0) return 0;
        if(
            curr(parser).category.type == TOKEN_PUNCTUATION
            && curr(parser).category.subType == PUNCTUATION_PARENTH_CLOSED
        ) {
            advance(parser);
            return 1;
        }
    }
    return 0;
}

int whileSTMT(Parser* parser) {
    if(
        curr(parser).category.type != TOKEN_KEYWORD
        || curr(parser).category.subType != KEYWORD_WHILE
    ) return 0;
    advance(parser);
    if(
        curr(parser).category.type != TOKEN_PUNCTUATION
        || curr(parser).category.subType != PUNCTUATION_PARENTH_OPEN
    ) return 0;
    advance(parser);
    if(expr(parser) == 0) return 0;
    if(
        curr(parser).category.type != TOKEN_PUNCTUATION
        || curr(parser).category.subType != PUNCTUATION_PARENTH_CLOSED
    ) return 0;
    advance(parser);
    return stmt(parser);
}

int ifSTMT(Parser* parser) {
    if(
        curr(parser).category.type != TOKEN_KEYWORD
        || curr(parser).category.subType != KEYWORD_IF
    ) return 0;
    advance(parser);
    if(
        curr(parser).category.type != TOKEN_PUNCTUATION
        || curr(parser).category.subType != PUNCTUATION_PARENTH_OPEN
    ) return 0;
    advance(parser);
    if(expr(parser) == 0) return 0;
    if(
        curr(parser).category.type != TOKEN_PUNCTUATION
        || curr(parser).category.subType != PUNCTUATION_PARENTH_CLOSED
    ) return 0;
    advance(parser);
    return stmt(parser);
}

int returnSTMT(Parser* parser) {
    if(
        curr(parser).category.type != TOKEN_KEYWORD
        || curr(parser).category.subType != KEYWORD_RETURN
    ) return 0;
    advance(parser);
    expr(parser);
    if(
        curr(parser).category.type == TOKEN_PUNCTUATION
        && curr(parser).category.subType == PUNCTUATION_SEMICOLON
    ) {
        advance(parser);
        return 1;
    }
    return 0;
}

int breakSTMT(Parser* parser) {
    if(
        curr(parser).category.type != TOKEN_KEYWORD
        || curr(parser).category.subType != KEYWORD_BREAK
    ) return 0;
    advance(parser);
    if(
        curr(parser).category.type == TOKEN_PUNCTUATION
        && curr(parser).category.subType == PUNCTUATION_SEMICOLON
    ) {
        advance(parser);
        return 1;
    }
    return 0;
}

int blockSTMT(Parser* parser) {
    if(
        curr(parser).category.type != TOKEN_PUNCTUATION
        || curr(parser).category.subType != PUNCTUATION_BRACES_OPEN
    ) return 0;
    advance(parser);
    while(stmt(parser));
    if(
        curr(parser).category.type == TOKEN_PUNCTUATION
        && curr(parser).category.subType == PUNCTUATION_BRACES_CLOSED
    ) {
        advance(parser);
        return 1;
    }
    return 0;
}

int methodSTMT(Parser* parser) {
    if(
        curr(parser).category.type != TOKEN_KEYWORD
        || curr(parser).category.subType != KEYWORD_METHOD
    ) return 0;
    advance(parser);
    if(curr(parser).category.type != TOKEN_IDENTIFIER) return 0;
    advance(parser);
    if(
        curr(parser).category.type != TOKEN_PUNCTUATION
        || curr(parser).category.subType != PUNCTUATION_PARENTH_OPEN
    ) return 0;
    advance(parser);
    if(paramList(parser) == 0) return 0;
    if(
        curr(parser).category.type != TOKEN_PUNCTUATION
        || curr(parser).category.subType != PUNCTUATION_PARENTH_CLOSED
    ) return 0;
    advance(parser);
    return blockSTMT(parser);
}

int paramList(Parser* parser) {
    if(curr(parser).category.type == TOKEN_IDENTIFIER) {
        advance(parser);
        while(1) {
            if(
                curr(parser).category.type == TOKEN_PUNCTUATION 
                && curr(parser).category.subType == PUNCTUATION_COMMA
            ) {
                advance(parser); 
                if(curr(parser).category.type != TOKEN_IDENTIFIER) {
                    retreat(parser);
                    return 0;
                }
                advance(parser);
            } else break;
        }
    }
    // whatever I get, I have to process it in methodSTMT
    return 1;
}