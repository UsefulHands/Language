#include "grammar.h"
#include "../lexer/lexer.h"

int programPar(Parser* parser) {
    while(stmtPar(parser));
    if(currPar(parser).category.type == TOKEN_EOF) {
        advancePar(parser);
        return 1;
    } return 0;
}

int stmtPar(Parser* parser) {
    int startIndex = getCurrIndexPar(parser);
    if(declarationPar(parser) == 1) return 1;
    restorePar(parser, startIndex);
    if(exprPar(parser) == 1) {
        if(
            currPar(parser).category.type == TOKEN_PUNCTUATION
            && currPar(parser).category.subType == PUNCTUATION_SEMICOLON
        ) {
            advancePar(parser);
            return 1;
        }
    }
    restorePar(parser, startIndex);
    if(whileSTMTPar(parser) == 1) return 1;
    restorePar(parser, startIndex);
    if(ifSTMTPar(parser) == 1) return 1;
    restorePar(parser, startIndex);
    if(returnSTMTPar(parser) == 1) return 1;
    restorePar(parser, startIndex);
    if(breakSTMTPar(parser) == 1) return 1;
    restorePar(parser, startIndex);
    if(blockSTMTPar(parser) == 1) return 1;
    restorePar(parser, startIndex);
    if(methodSTMTPar(parser) == 1) return 1;
    return 0;
}

int declarationPar(Parser* parser) {
    if(typeSpecPar(parser) == 0) return 0;
    if(currPar(parser).category.type != TOKEN_IDENTIFIER) return 0;
    advancePar(parser);
    while(1) {
        if(
            currPar(parser).category.type == TOKEN_PUNCTUATION
            && currPar(parser).category.subType == PUNCTUATION_DOT
        ) {
            advancePar(parser);
            if(currPar(parser).category.type == TOKEN_IDENTIFIER) {
                advancePar(parser);
            } else return 0;
        } else break;
    }
    if(
        currPar(parser).category.type == TOKEN_PUNCTUATION
        && currPar(parser).category.subType == PUNCTUATION_SQUARE_B_OPEN
    ) {
        advancePar(parser);
        if(exprPar(parser) == 0) return 0;
        if(
            currPar(parser).category.type != TOKEN_PUNCTUATION
            || currPar(parser).category.subType != PUNCTUATION_SQUARE_B_CLOSED
        ) return 0;
        advancePar(parser);
    }
    if(
        currPar(parser).category.type != TOKEN_OPERATOR
        || currPar(parser).category.subType != OPERATOR_ASSIGN
    ) return 0;
    advancePar(parser);
    if(exprPar(parser) == 0) return 0;
    if(
        currPar(parser).category.type != TOKEN_PUNCTUATION
        || currPar(parser).category.subType != PUNCTUATION_SEMICOLON
    ) return 0;
    advancePar(parser);
    return 1;
}

int typeSpecPar(Parser* parser) {
    if(currPar(parser).category.type != TOKEN_KEYWORD) return 0;
    if(
        currPar(parser).category.subType != KEYWORD_NUMBER
        && currPar(parser).category.subType != KEYWORD_STRING
        && currPar(parser).category.subType != KEYWORD_BOOL
    ) return 0;
    advancePar(parser);
    return 1;
}

int exprPar(Parser* parser) {
    if(assignmentPar(parser) == 1) return 1;
    return 0;
}

int assignmentPar(Parser* parser) {
    int saved = getCurrIndexPar(parser);
    if(currPar(parser).category.type == TOKEN_IDENTIFIER) {
        advancePar(parser);
        while(1) {
            if(
                currPar(parser).category.type == TOKEN_PUNCTUATION
                && currPar(parser).category.subType == PUNCTUATION_DOT
            ) {
                advancePar(parser);
                if(currPar(parser).category.type == TOKEN_IDENTIFIER) {
                    advancePar(parser);
                } 
                else {
                    restorePar(parser, saved);
                    return 0;
                }
            } else break;
        }
        if(
            currPar(parser).category.type == TOKEN_PUNCTUATION
            && currPar(parser).category.subType == PUNCTUATION_SQUARE_B_OPEN
        ) {
            advancePar(parser);
            if(exprPar(parser) == 0) {
                restorePar(parser, saved);
                return logicOrPar(parser);
            }
            if(
                currPar(parser).category.type != TOKEN_PUNCTUATION
                || currPar(parser).category.subType != PUNCTUATION_SQUARE_B_CLOSED
            ) {
                restorePar(parser, saved);
                return logicOrPar(parser);
            }
            advancePar(parser);
        }
        if(
            currPar(parser).category.type == TOKEN_OPERATOR
            && currPar(parser).category.subType == OPERATOR_ASSIGN
        ) {
            advancePar(parser);
            if (assignmentPar(parser) == 1) return 1;
        }
    }
    restorePar(parser, saved);
    if (logicOrPar(parser) == 1) return 1;
    return 0;
}

int logicOrPar(Parser* parser) {
    if(logicAndPar(parser) == 0) return 0;
    while(1) {
        if(
            currPar(parser).category.type == TOKEN_KEYWORD
            && currPar(parser).category.subType == KEYWORD_OR
        ) advancePar(parser);
        else break;
        if(logicAndPar(parser) == 0) return 0;
    } return 1;
}

int logicAndPar(Parser* parser) {
    if(equalityPar(parser) == 0) return 0;
    while(1) {
        if(
            currPar(parser).category.type == TOKEN_KEYWORD
            && currPar(parser).category.subType == KEYWORD_AND
        ) advancePar(parser);
        else break;
        if(equalityPar(parser) == 0) return 0;
    } return 1;
}

int equalityPar(Parser* parser) {
    if(comparisonPar(parser) == 0) return 0;
    while(1) {
        if(
            currPar(parser).category.type == TOKEN_OPERATOR
            && (
                currPar(parser).category.subType == OPERATOR_EQUALS 
                || currPar(parser).category.subType == OPERATOR_NOT_EQU    
            )
        ) advancePar(parser);
        else break;
        if(comparisonPar(parser) == 0) return 0;
    } return 1;
}

int comparisonPar(Parser* parser) {
    if(termPar(parser) == 0) return 0;
    while(1) {
        if(
            currPar(parser).category.type == TOKEN_OPERATOR
            && (
                currPar(parser).category.subType == OPERATOR_GREATER_T 
                || currPar(parser).category.subType == OPERATOR_LESSER_T
                || currPar(parser).category.subType == OPERATOR_EQU_GREATER_T
                || currPar(parser).category.subType == OPERATOR_EQU_LESSER_T    
            )
        ) advancePar(parser);
        else break;
        if(termPar(parser) == 0) return 0;
    } return 1;
}

int termPar(Parser* parser) {
    if(factorPar(parser) == 0) return 0;
    while(1) {
        if(
            currPar(parser).category.type == TOKEN_OPERATOR
            && (
                currPar(parser).category.subType == OPERATOR_PLUS 
                || currPar(parser).category.subType == OPERATOR_MINUS    
            )
        ) advancePar(parser);
        else break;
        if(factorPar(parser) == 0) return 0;
    } return 1;
}

int factorPar(Parser* parser) {
    if(unaryPar(parser) == 0) return 0;
    while(1) {
        if(
            currPar(parser).category.type == TOKEN_OPERATOR
            && (
                currPar(parser).category.subType == OPERATOR_MULTI 
                || currPar(parser).category.subType == OPERATOR_DIVIDE    
            )
        ) advancePar(parser);
        else break;
        if(unaryPar(parser) == 0) return 0;
    } return 1;
}

int unaryPar(Parser* parser) {
    if(
        currPar(parser).category.type == TOKEN_KEYWORD
        && currPar(parser).category.subType == KEYWORD_NOT
    ) {
        advancePar(parser);
        return unaryPar(parser);
    } return primaryPar(parser);
}

int primaryPar(Parser* parser) {
    if(currPar(parser).category.type == TOKEN_NUMBER) {
        advancePar(parser);
        return 1;
    }
    if(currPar(parser).category.type == TOKEN_STRING) {
        advancePar(parser);
        return 1;
    }
    if(currPar(parser).category.type == TOKEN_IDENTIFIER) {
        advancePar(parser);
        while(1) {
            if(
                currPar(parser).category.type == TOKEN_PUNCTUATION
                && currPar(parser).category.subType == PUNCTUATION_DOT
            ) {
                advancePar(parser);
                if(currPar(parser).category.type == TOKEN_IDENTIFIER) {
                    advancePar(parser);
                } 
                else {
                    retreatPar(parser);
                    break;
                }
            }
            else break;
        }
        if(
            currPar(parser).category.type == TOKEN_PUNCTUATION
            && currPar(parser).category.subType == PUNCTUATION_PARENTH_OPEN
        ) {
            advancePar(parser);
            argListPar(parser);
            if(
                currPar(parser).category.type != TOKEN_PUNCTUATION
                || currPar(parser).category.subType != PUNCTUATION_PARENTH_CLOSED
            ) return 0;
            advancePar(parser);
        }
        if(
            currPar(parser).category.type == TOKEN_PUNCTUATION
            && currPar(parser).category.subType == PUNCTUATION_SQUARE_B_OPEN
        ) {
            advancePar(parser);
            if(exprPar(parser) == 0) return 0;
            if(
                currPar(parser).category.type == TOKEN_PUNCTUATION
                && currPar(parser).category.subType == PUNCTUATION_SQUARE_B_CLOSED
            ) advancePar(parser);
            else return 0;
        }
        return 1;
    }
    if(
        currPar(parser).category.type == TOKEN_KEYWORD
        && (
            currPar(parser).category.subType == KEYWORD_TRUE
            || currPar(parser).category.subType == KEYWORD_FALSE
            || currPar(parser).category.subType == KEYWORD_NULL
        )
    ) {
        advancePar(parser);
        return 1;
    }
    if(
        currPar(parser).category.type == TOKEN_PUNCTUATION
        && currPar(parser).category.subType == PUNCTUATION_PARENTH_OPEN
    ) {
        advancePar(parser);
        if(exprPar(parser) == 0) return 0;
        if(
            currPar(parser).category.type == TOKEN_PUNCTUATION
            && currPar(parser).category.subType == PUNCTUATION_PARENTH_CLOSED
        ) {
            advancePar(parser);
            return 1;
        }
    }
    return 0;
}

int whileSTMTPar(Parser* parser) {
    if(
        currPar(parser).category.type != TOKEN_KEYWORD
        || currPar(parser).category.subType != KEYWORD_WHILE
    ) return 0;
    advancePar(parser);
    if(
        currPar(parser).category.type != TOKEN_PUNCTUATION
        || currPar(parser).category.subType != PUNCTUATION_PARENTH_OPEN
    ) return 0;
    advancePar(parser);
    if(exprPar(parser) == 0) return 0;
    if(
        currPar(parser).category.type != TOKEN_PUNCTUATION
        || currPar(parser).category.subType != PUNCTUATION_PARENTH_CLOSED
    ) return 0;
    advancePar(parser);
    return stmtPar(parser);
}

int ifSTMTPar(Parser* parser) {
    if(
        currPar(parser).category.type != TOKEN_KEYWORD
        || currPar(parser).category.subType != KEYWORD_IF
    ) return 0;
    advancePar(parser);
    if(
        currPar(parser).category.type != TOKEN_PUNCTUATION
        || currPar(parser).category.subType != PUNCTUATION_PARENTH_OPEN
    ) return 0;
    advancePar(parser);
    if(exprPar(parser) == 0) return 0;
    if(
        currPar(parser).category.type != TOKEN_PUNCTUATION
        || currPar(parser).category.subType != PUNCTUATION_PARENTH_CLOSED
    ) return 0;
    advancePar(parser);
    return stmtPar(parser);
}

int returnSTMTPar(Parser* parser) {
    if(
        currPar(parser).category.type != TOKEN_KEYWORD
        || currPar(parser).category.subType != KEYWORD_RETURN
    ) return 0;
    advancePar(parser);
    exprPar(parser);
    if(
        currPar(parser).category.type == TOKEN_PUNCTUATION
        && currPar(parser).category.subType == PUNCTUATION_SEMICOLON
    ) {
        advancePar(parser);
        return 1;
    } return 0;
}

int breakSTMTPar(Parser* parser) {
    if(
        currPar(parser).category.type != TOKEN_KEYWORD
        || currPar(parser).category.subType != KEYWORD_BREAK
    ) return 0;
    advancePar(parser);
    if(
        currPar(parser).category.type == TOKEN_PUNCTUATION
        && currPar(parser).category.subType == PUNCTUATION_SEMICOLON
    ) {
        advancePar(parser);
        return 1;
    } return 0;
}

int blockSTMTPar(Parser* parser) {
    if(
        currPar(parser).category.type != TOKEN_PUNCTUATION
        || currPar(parser).category.subType != PUNCTUATION_BRACES_OPEN
    ) return 0;
    advancePar(parser);
    while(stmtPar(parser));
    if(
        currPar(parser).category.type == TOKEN_PUNCTUATION
        && currPar(parser).category.subType == PUNCTUATION_BRACES_CLOSED
    ) {
        advancePar(parser);
        return 1;
    } return 0;
}

int methodSTMTPar(Parser* parser) {
    if(
        currPar(parser).category.type != TOKEN_KEYWORD
        || currPar(parser).category.subType != KEYWORD_METHOD
    ) return 0;
    advancePar(parser);
    if(currPar(parser).category.type != TOKEN_IDENTIFIER) return 0;
    advancePar(parser);
    while(1) {
        if(
            currPar(parser).category.type == TOKEN_PUNCTUATION
            && currPar(parser).category.subType == PUNCTUATION_DOT
        ) {
            advancePar(parser);
            if(currPar(parser).category.type == TOKEN_IDENTIFIER) {
                advancePar(parser);
            } else return 0;
        } else break;
    }
    if(
        currPar(parser).category.type != TOKEN_PUNCTUATION
        || currPar(parser).category.subType != PUNCTUATION_PARENTH_OPEN
    ) return 0;
    advancePar(parser);
    if(paramListPar(parser) == 0) return 0;
    if(
        currPar(parser).category.type != TOKEN_PUNCTUATION
        || currPar(parser).category.subType != PUNCTUATION_PARENTH_CLOSED
    ) return 0;
    advancePar(parser);
    return blockSTMTPar(parser);
}

int paramListPar(Parser* parser) {
    if(currPar(parser).category.type == TOKEN_IDENTIFIER) {
        advancePar(parser);
        while(1) {
            if(
                currPar(parser).category.type == TOKEN_PUNCTUATION 
                && currPar(parser).category.subType == PUNCTUATION_COMMA
            ) {
                advancePar(parser); 
                if(currPar(parser).category.type != TOKEN_IDENTIFIER) {
                    retreatPar(parser);
                    return 0;
                }
                advancePar(parser);
            } else break;
        }
    }
    // whatever I get (epsilon or not), I have to process it in methodSTMT
    return 1;
}

int argListPar(Parser* parser) {
    if(exprPar(parser) == 0) return 1;  // epsilon
    while(1) {
        if(
            currPar(parser).category.type == TOKEN_PUNCTUATION
            && currPar(parser).category.subType == PUNCTUATION_COMMA
        ) {
            advancePar(parser);
            if(exprPar(parser) == 0) return 0;
        } else break;
    }
    return 1;
}