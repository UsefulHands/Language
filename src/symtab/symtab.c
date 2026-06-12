#include "symtab.h"
#include <stdlib.h>
#include <string.h>

int programSem(SemanticChecker* checker) {
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
    if(exprSem(checker) != -1) {
        if(
            currSem(checker).category.type == TOKEN_PUNCTUATION
            && currSem(checker).category.subType == PUNCTUATION_SEMICOLON
        ) {
            advanceSem(checker);
            return 1;
        }
    }
    return 0;
}

int declarationSem(SemanticChecker* checker) {
    TypeSpec spec = typeSpecSem(checker);
    if(spec == -1) return 0;
    if(currSem(checker).category.type != TOKEN_IDENTIFIER) return 0;
    char fullName[MAX_NAME_SIZE];
    strcpy(fullName, currSem(checker).value);
    advanceSem(checker);
    while(1) {
        if(
            currSem(checker).category.type == TOKEN_PUNCTUATION
            && currSem(checker).category.subType == PUNCTUATION_DOT
        ) {
            advanceSem(checker);
            if(currSem(checker).category.type == TOKEN_IDENTIFIER) {
                strcat(fullName, ".");
                strcat(fullName, currSem(checker).value);
                advanceSem(checker);
            } else return 0;
        } else break;
    }
    if(
        currSem(checker).category.type == TOKEN_PUNCTUATION
        && currSem(checker).category.subType == PUNCTUATION_SQUARE_B_OPEN
    ) {
        advanceSem(checker);
        if(exprSem(checker) == -1) return 0;
        if(
            currSem(checker).category.type != TOKEN_PUNCTUATION
            || currSem(checker).category.subType != PUNCTUATION_SQUARE_B_CLOSED
        ) return 0;
        advanceSem(checker);
    }
    if(
        currSem(checker).category.type != TOKEN_OPERATOR
        || currSem(checker).category.subType != OPERATOR_ASSIGN
    ) return 0;
    advanceSem(checker);
    TypeSpec exprType = exprSem(checker);
    if(exprType == -1) return 0;
    if(exprType != TYPE_NULL && exprType != spec) return 0;
    if(
        currSem(checker).category.type != TOKEN_PUNCTUATION
        || currSem(checker).category.subType != PUNCTUATION_SEMICOLON
    ) return 0;
    advanceSem(checker);
    addSymbol(checker->table, fullName, SYMBOL_VARIABLE, spec, 0);
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

TypeSpec exprSem(SemanticChecker* checker) {
    return assignmentSem(checker);
}

TypeSpec assignmentSem(SemanticChecker* checker) {
    int saved = getCurrIndexSem(checker);
    if(currSem(checker).category.type == TOKEN_IDENTIFIER) {
        char fullName[MAX_NAME_SIZE];
        strcpy(fullName, currSem(checker).value);
        advanceSem(checker);
        while(1) {
            if(
                currSem(checker).category.type == TOKEN_PUNCTUATION
                && currSem(checker).category.subType == PUNCTUATION_DOT
            ) {
                advanceSem(checker);
                if(currSem(checker).category.type == TOKEN_IDENTIFIER) {
                    strcat(fullName, ".");
                    strcat(fullName, currSem(checker).value);
                    advanceSem(checker);
                } else {
                    restoreSem(checker, saved);
                    return -1;
                }
            } else break;
        }
        if(
            currSem(checker).category.type == TOKEN_PUNCTUATION
            && currSem(checker).category.subType == PUNCTUATION_SQUARE_B_OPEN
        ) {
            advanceSem(checker);
            if(exprSem(checker) == -1) {
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
            Symbol* sym = lookup(checker->table, fullName);
            if(sym == NULL) return -1;
            advanceSem(checker);
            TypeSpec t = assignmentSem(checker);
            if(t != -1) return sym->typeSpec;
        }
    }
    restoreSem(checker, saved);
    return logicOrSem(checker);
}

TypeSpec logicOrSem(SemanticChecker* checker) {
    TypeSpec t = logicAndSem(checker);
    if(t == -1) return -1;
    while(1) {
        if(
            currSem(checker).category.type == TOKEN_KEYWORD
            && currSem(checker).category.subType == KEYWORD_OR
        ) advanceSem(checker);
        else break;
        if(logicAndSem(checker) == -1) return -1;
    } return t;
}

TypeSpec logicAndSem(SemanticChecker* checker) {
    TypeSpec t = equalitySem(checker);
    if(t == -1) return -1;
    while(1) {
        if(
            currSem(checker).category.type == TOKEN_KEYWORD
            && currSem(checker).category.subType == KEYWORD_AND
        ) advanceSem(checker);
        else break;
        if(equalitySem(checker) == -1) return -1;
    } return t;
}

TypeSpec equalitySem(SemanticChecker* checker) {
    TypeSpec t = comparisonSem(checker);
    if(t == -1) return -1;
    while(1) {
        if(
            currSem(checker).category.type == TOKEN_OPERATOR
            && (
                currSem(checker).category.subType == OPERATOR_EQUALS
                || currSem(checker).category.subType == OPERATOR_NOT_EQU
            )
        ) advanceSem(checker);
        else break;
        if(comparisonSem(checker) == -1) return -1;
        t = TYPE_BOOL;
    } return t;
}

TypeSpec comparisonSem(SemanticChecker* checker) {
    TypeSpec t = termSem(checker);
    if(t == -1) return -1;
    while(1) {
        if(
            currSem(checker).category.type == TOKEN_OPERATOR
            && (
                currSem(checker).category.subType == OPERATOR_GREATER_T
                || currSem(checker).category.subType == OPERATOR_LESSER_T
                || currSem(checker).category.subType == OPERATOR_EQU_GREATER_T
                || currSem(checker).category.subType == OPERATOR_EQU_LESSER_T
            )
        ) advanceSem(checker);
        else break;
        if(termSem(checker) == -1) return -1;
        t = TYPE_BOOL;
    } return t;
}

TypeSpec termSem(SemanticChecker* checker) {
    TypeSpec t = factorSem(checker);
    if(t == -1) return -1;
    while(1) {
        if(
            currSem(checker).category.type == TOKEN_OPERATOR
            && (
                currSem(checker).category.subType == OPERATOR_PLUS
                || currSem(checker).category.subType == OPERATOR_MINUS
            )
        ) advanceSem(checker);
        else break;
        if(factorSem(checker) == -1) return -1;
    } return t;
}

TypeSpec factorSem(SemanticChecker* checker) {
    TypeSpec t = unarySem(checker);
    if(t == -1) return -1;
    while(1) {
        if(
            currSem(checker).category.type == TOKEN_OPERATOR
            && (
                currSem(checker).category.subType == OPERATOR_MULTI
                || currSem(checker).category.subType == OPERATOR_DIVIDE
            )
        ) advanceSem(checker);
        else break;
        if(unarySem(checker) == -1) return -1;
    } return t;
}

TypeSpec unarySem(SemanticChecker* checker) {
    if(
        currSem(checker).category.type == TOKEN_KEYWORD
        && currSem(checker).category.subType == KEYWORD_NOT
    ) {
        advanceSem(checker);
        return unarySem(checker);
    } return primarySem(checker);
}

TypeSpec primarySem(SemanticChecker* checker) { 
    if(currSem(checker).category.type == TOKEN_NUMBER) {
        advanceSem(checker);
        return TYPE_NUMBER;
    }
    if(currSem(checker).category.type == TOKEN_STRING) {
        advanceSem(checker);
        return TYPE_STRING;
    }
    if(currSem(checker).category.type == TOKEN_IDENTIFIER) {
        char fullName[MAX_NAME_SIZE];
        strcpy(fullName, currSem(checker).value);
        advanceSem(checker);
        while(1) {
            if(
                currSem(checker).category.type == TOKEN_PUNCTUATION
                && currSem(checker).category.subType == PUNCTUATION_DOT
            ) {
                advanceSem(checker);
                if(currSem(checker).category.type == TOKEN_IDENTIFIER) {
                    strcat(fullName, ".");
                    strcat(fullName, currSem(checker).value);
                    advanceSem(checker);
                } else {
                    retreatSem(checker);
                    break;
                }
            } else break;
        }
        if(
            currSem(checker).category.type == TOKEN_PUNCTUATION
            && currSem(checker).category.subType == PUNCTUATION_PARENTH_OPEN
        ) {
            advanceSem(checker);
            argListSem(checker);
            if(
                currSem(checker).category.type != TOKEN_PUNCTUATION
                || currSem(checker).category.subType != PUNCTUATION_PARENTH_CLOSED
            ) return -1;
            advanceSem(checker);
            Symbol* sym = lookup(checker->table, fullName);
            if(sym == NULL) return -1;
            return sym->typeSpec;
        }
        if(
            currSem(checker).category.type == TOKEN_PUNCTUATION
            && currSem(checker).category.subType == PUNCTUATION_SQUARE_B_OPEN
        ) {
            advanceSem(checker);
            if(exprSem(checker) == -1) return -1;
            if(
                currSem(checker).category.type == TOKEN_PUNCTUATION
                && currSem(checker).category.subType == PUNCTUATION_SQUARE_B_CLOSED
            ) advanceSem(checker);
            else return -1;
        }
        Symbol* sym = lookup(checker->table, fullName);
        if(sym == NULL) return -1;
        return sym->typeSpec;
    }
    if(
        currSem(checker).category.type == TOKEN_KEYWORD
        && (
            currSem(checker).category.subType == KEYWORD_TRUE
            || currSem(checker).category.subType == KEYWORD_FALSE
        )
    ) {
        advanceSem(checker);
        return TYPE_BOOL;
    }
    if(
        currSem(checker).category.type == TOKEN_KEYWORD
        && currSem(checker).category.subType == KEYWORD_NULL
    ) {
        advanceSem(checker);
        return TYPE_NULL;
    }
    if(
        currSem(checker).category.type == TOKEN_PUNCTUATION
        && currSem(checker).category.subType == PUNCTUATION_PARENTH_OPEN
    ) {
        advanceSem(checker);
        TypeSpec t = exprSem(checker);
        if(t == -1) return -1;
        if(
            currSem(checker).category.type == TOKEN_PUNCTUATION
            && currSem(checker).category.subType == PUNCTUATION_PARENTH_CLOSED
        ) {
            advanceSem(checker);
            return t;
        }
    }
    return -1;
}

int whileSTMTSem(SemanticChecker* checker) {
    advanceSem(checker);
    if(
        currSem(checker).category.type != TOKEN_PUNCTUATION
        || currSem(checker).category.subType != PUNCTUATION_PARENTH_OPEN
    ) return 0;
    advanceSem(checker);
    if(exprSem(checker) == -1) return 0;
    if(
        currSem(checker).category.type != TOKEN_PUNCTUATION
        || currSem(checker).category.subType != PUNCTUATION_PARENTH_CLOSED
    ) return 0;
    advanceSem(checker);
    return stmtSem(checker);
}

int ifSTMTSem(SemanticChecker* checker) {
    advanceSem(checker);
    if(
        currSem(checker).category.type != TOKEN_PUNCTUATION
        || currSem(checker).category.subType != PUNCTUATION_PARENTH_OPEN
    ) return 0;
    advanceSem(checker);
    if(exprSem(checker) == -1) return 0;
    if(
        currSem(checker).category.type != TOKEN_PUNCTUATION
        || currSem(checker).category.subType != PUNCTUATION_PARENTH_CLOSED
    ) return 0;
    advanceSem(checker);
    return stmtSem(checker);
}

int returnSTMTSem(SemanticChecker* checker) {
    advanceSem(checker);
    exprSem(checker);
    if(
        currSem(checker).category.type == TOKEN_PUNCTUATION
        && currSem(checker).category.subType == PUNCTUATION_SEMICOLON
    ) {
        advanceSem(checker);
        return 1;
    } return 0;
}

int breakSTMTSem(SemanticChecker* checker) {
    advanceSem(checker);
    if(
        currSem(checker).category.type == TOKEN_PUNCTUATION
        && currSem(checker).category.subType == PUNCTUATION_SEMICOLON
    ) {
        advanceSem(checker);
        return 1;
    } return 0;
}

int blockSTMTSem(SemanticChecker* checker) {
    advanceSem(checker);
    checker->table = enterScope(checker->table);
    while(stmtSem(checker));
    checker->table = exitScope(checker->table);
    if(
        currSem(checker).category.type == TOKEN_PUNCTUATION
        && currSem(checker).category.subType == PUNCTUATION_BRACES_CLOSED
    ) {
        advanceSem(checker);
        return 1;
    } return 0;
}

int methodSTMTSem(SemanticChecker* checker) {
    advanceSem(checker);
    if(currSem(checker).category.type != TOKEN_IDENTIFIER) return 0;
    char fullName[MAX_NAME_SIZE];
    strcpy(fullName, currSem(checker).value);
    advanceSem(checker);
    while(1) {
        if(
            currSem(checker).category.type == TOKEN_PUNCTUATION
            && currSem(checker).category.subType == PUNCTUATION_DOT
        ) {
            advanceSem(checker);
            if(currSem(checker).category.type == TOKEN_IDENTIFIER) {
                strcat(fullName, ".");
                strcat(fullName, currSem(checker).value);
                advanceSem(checker);
            } else return 0;
        } else break;
    }
    if(
        currSem(checker).category.type != TOKEN_PUNCTUATION
        || currSem(checker).category.subType != PUNCTUATION_PARENTH_OPEN
    ) return 0;
    advanceSem(checker);
    checker->table = enterScope(checker->table);
    int paramCount = paramListSem(checker);
    if(paramCount == -1) {
        checker->table = exitScope(checker->table);
        return 0;
    }
    if(
        currSem(checker).category.type != TOKEN_PUNCTUATION
        || currSem(checker).category.subType != PUNCTUATION_PARENTH_CLOSED
    ) {
        checker->table = exitScope(checker->table);
        return 0;
    }
    advanceSem(checker);
    if(
        currSem(checker).category.type != TOKEN_PUNCTUATION
        || currSem(checker).category.subType != PUNCTUATION_BRACES_OPEN
    ) {
        checker->table = exitScope(checker->table);
        return 0;
    }
    advanceSem(checker);
    while(stmtSem(checker));
    addSymbol(checker->table->parent, fullName, SYMBOL_METHOD, TYPE_NUMBER, paramCount);
    checker->table = exitScope(checker->table);
    if(
        currSem(checker).category.type != TOKEN_PUNCTUATION
        || currSem(checker).category.subType != PUNCTUATION_BRACES_CLOSED
    ) return 0;
    advanceSem(checker);
    return 1;
}

int paramListSem(SemanticChecker* checker) {
    int count = 0;
    if(currSem(checker).category.type == TOKEN_IDENTIFIER) {
        addSymbol(checker->table, currSem(checker).value, SYMBOL_VARIABLE, TYPE_NUMBER, 0);
        advanceSem(checker);
        count++;
        while(1) {
            if(
                currSem(checker).category.type == TOKEN_PUNCTUATION
                && currSem(checker).category.subType == PUNCTUATION_COMMA
            ) {
                advanceSem(checker);
                if(currSem(checker).category.type != TOKEN_IDENTIFIER) {
                    retreatSem(checker);
                    return -1;
                }
                addSymbol(checker->table, currSem(checker).value, SYMBOL_VARIABLE, TYPE_NUMBER, 0);
                advanceSem(checker);
                count++;
            } else break;
        }
    }
    return count;
}

int argListSem(SemanticChecker* checker) {
    if(exprSem(checker) == -1) return 1;
    while(1) {
        if(
            currSem(checker).category.type == TOKEN_PUNCTUATION
            && currSem(checker).category.subType == PUNCTUATION_COMMA
        ) {
            advanceSem(checker);
            if(exprSem(checker) == -1) return 0;
        } else break;
    }
    return 1;
}