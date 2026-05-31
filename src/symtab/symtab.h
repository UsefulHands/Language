#ifndef SYMTAB_H
#define SYMTAB_H

#include "../semanticAnalyzer/semanticAnalyzer.h"

int programSem(SemanticChecker* checker);
int stmtSem(SemanticChecker* checker);
int declarationSem(SemanticChecker* checker);
TypeSpec typeSpecSem(SemanticChecker* checker);
int exprSem(SemanticChecker* checker);
int assignmentSem(SemanticChecker* checker);
int logicOrSem(SemanticChecker* checker);
int logicAndSem(SemanticChecker* checker);
int equalitySem(SemanticChecker* checker);
int comparisonSem(SemanticChecker* checker);
int termSem(SemanticChecker* checker);
int factorSem(SemanticChecker* checker);
int unarySem(SemanticChecker* checker);
int primarySem(SemanticChecker* checker);
int whileSTMTSem(SemanticChecker* checker);
int ifSTMTSem(SemanticChecker* checker);
int returnSTMTSem(SemanticChecker* checker);
int breakSTMTSem(SemanticChecker* checker);
int blockSTMTSem(SemanticChecker* checker);
int methodSTMTSem(SemanticChecker* checker);
int paramListSem(SemanticChecker* checker);
int argListSem(SemanticChecker* checker);

#endif