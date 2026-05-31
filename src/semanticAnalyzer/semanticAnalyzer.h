#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include "../symtab/symtab.h"
#include "../lexer/lexer.h"

typedef struct {
    Token* tokens;
    int index;
    SymbolTable* table;
} SemanticChecker;

int semProgram(SemanticChecker* checker);
int semStmt(SemanticChecker* checker);
int semDeclaration(SemanticChecker* checker);
int semTypeSpec(SemanticChecker* checker);
int semExpr(SemanticChecker* checker);
int semAssignment(SemanticChecker* checker);
int semLogicOr(SemanticChecker* checker);
int semLogicAnd(SemanticChecker* checker);
int semEquality(SemanticChecker* checker);
int semComparison(SemanticChecker* checker);
int semTerm(SemanticChecker* checker);
int semFactor(SemanticChecker* checker);
int semUnary(SemanticChecker* checker);
int semPrimary(SemanticChecker* checker);
int semWhileSTMT(SemanticChecker* checker);
int semIfSTMT(SemanticChecker* checker);
int semReturnSTMT(SemanticChecker* checker);
int semBreakSTMT(SemanticChecker* checker);
int semBlockSTMT(SemanticChecker* checker);
int semMethodSTMT(SemanticChecker* checker);
int semParamList(SemanticChecker* checker);
int semArgList(SemanticChecker* checker);

#endif