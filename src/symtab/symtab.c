#include "symtab.h"
#include <stdlib.h>

int programSem(SemanticChecker* checker) {
    return 1;
    while(stmtSem(checker));
    return currSem(checker).category.type == TOKEN_EOF;
}

int stmtSem(SemanticChecker* checker) {
    if(
        currSem(checker).category.type == TOKEN_KEYWORD 
        && (
            currSem(checker).category.subType == KEYWORD_NUMBER ||
            currSem(checker).category.subType == KEYWORD_STRING ||
            currSem(checker).category.subType == KEYWORD_BOOL
        )
    ) return declarationSem(checker);
    if(exprSem(checker) == 1) {
        if(
            currSem(checker).category.type == TOKEN_PUNCTUATION
            && currSem(checker).category.subType == PUNCTUATION_SEMICOLON
        ) {
            advanceSem(checker);
            return 1;
        }
    }
    if(
        currSem(checker).category.type == TOKEN_KEYWORD 
        && currSem(checker).category.subType == KEYWORD_WHILE
    ) return whileSTMTSem(checker);
    if(
        currSem(checker).category.type == TOKEN_KEYWORD 
        && currSem(checker).category.subType == KEYWORD_IF
    ) return ifSTMTSem(checker);
    if(
        currSem(checker).category.type == TOKEN_KEYWORD 
        && currSem(checker).category.subType == KEYWORD_RETURN
    ) return returnSTMTSem(checker);
    if(
        currSem(checker).category.type == TOKEN_KEYWORD 
        && currSem(checker).category.subType == KEYWORD_BREAK
    ) return breakSTMTSem(checker);
    if(
        currSem(checker).category.type == TOKEN_PUNCTUATION 
        && currSem(checker).category.subType == PUNCTUATION_BRACES_OPEN
    ) return blockSTMTSem(checker);
    if(
        currSem(checker).category.type == TOKEN_KEYWORD 
        && currSem(checker).category.subType == KEYWORD_METHOD
    ) return methodSTMTSem(checker);
    return 0;
}

int declarationSem(SemanticChecker* checker) {
    TypeSpec spec = typeSpecSem(checker);
    if(spec == -1) return 0;
    if(currSem(checker).category.type != TOKEN_IDENTIFIER) return 0;
    char* name = currSem(checker).value;
    advanceSem(checker);
    while(1) {
        if(
            currSem(checker).category.type == TOKEN_PUNCTUATION
            && currSem(checker).category.subType == PUNCTUATION_DOT
        ) {
            advanceSem(checker);
            if(currSem(checker).category.type == TOKEN_IDENTIFIER) {
                advanceSem(checker);
            } else return 0;
        } else break;
    }
    if(
        currSem(checker).category.type != TOKEN_OPERATOR
        || currSem(checker).category.subType != OPERATOR_ASSIGN
    ) return 0;
    advanceSem(checker);
    if(exprSem(checker) == 0) return 0;
    if(
        currSem(checker).category.type != TOKEN_PUNCTUATION
        || currSem(checker).category.subType != PUNCTUATION_SEMICOLON
    ) return 0;
    advanceSem(checker);
    addSymbol(checker->table, name, SYMBOL_VARIABLE, spec, 0);
    return 1;
}

TypeSpec typeSpecSem(SemanticChecker* checker) {
    if(currSem(checker).category.type != TOKEN_KEYWORD) return -1;
    if(currSem(checker).category.subType == KEYWORD_NUMBER) {
        advanceSem(checker);
        return TYPE_NUMBER;
    }
    else if(currSem(checker).category.subType == KEYWORD_STRING) {
        advanceSem(checker);
        return TYPE_STRING;
    }
    else if(currSem(checker).category.subType == KEYWORD_BOOL) {
        advanceSem(checker);
        return TYPE_BOOL;
    } return -1;
}

int exprSem(SemanticChecker* checker) {
    if(assignmentSem(checker) == 1) return 1;
    return 0;
}

int assignmentSem(SemanticChecker* checker) {
    int saved = getCurrIndexSem(checker);
    if(currSem(checker).category.type == TOKEN_IDENTIFIER) {
        char* name = currSem(checker).value;
        advanceSem(checker);
        while(1) {
            if(
                currSem(checker).category.type == TOKEN_PUNCTUATION
                && currSem(checker).category.subType == PUNCTUATION_DOT
            ) {
                advanceSem(checker);
                if(currSem(checker).category.type == TOKEN_IDENTIFIER) {
                    advanceSem(checker);
                } else {
                    restoreSem(checker, saved);
                    return 0;
                }
            } else break;
        }
        if(
            currSem(checker).category.type == TOKEN_PUNCTUATION
            && currSem(checker).category.subType == PUNCTUATION_SQUARE_B_OPEN
        ) {
            advanceSem(checker);
            if(exprSem(checker) == 0) {
                restoreSem(checker, saved);
                return logicOrSem(checker);
            }
            if(
                currSem(checker).category.type != TOKEN_PUNCTUATION
                || currSem(checker).category.subType != PUNCTUATION_SQUARE_B_CLOSED
            ) {
                restoreSem(checker, saved);
                return logicOrSem(checker);
            }
            advanceSem(checker);
        }
        if(
            currSem(checker).category.type == TOKEN_OPERATOR
            && currSem(checker).category.subType == OPERATOR_ASSIGN
        ) {
            if(lookup(checker->table, name) == NULL) return 0;
            advanceSem(checker);
            if(assignmentSem(checker) == 1) return 1;
        }
    }
    restoreSem(checker, saved);
    if(logicOrSem(checker) == 1) return 1;
    return 0;
}