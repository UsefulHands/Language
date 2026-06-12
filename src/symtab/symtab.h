#ifndef SYMTAB_H
#define SYMTAB_H

#define MAX_NAME_SIZE 256

#include "../semanticAnalyzer/semanticAnalyzer.h"

int programSem(SemanticChecker* checker);
int stmtSem(SemanticChecker* checker);
int declarationSem(SemanticChecker* checker);
TypeSpec typeSpecSem(SemanticChecker* checker);
TypeSpec exprSem(SemanticChecker* checker);
TypeSpec assignmentSem(SemanticChecker* checker);
TypeSpec logicOrSem(SemanticChecker* checker);
TypeSpec logicAndSem(SemanticChecker* checker);
TypeSpec equalitySem(SemanticChecker* checker);
TypeSpec comparisonSem(SemanticChecker* checker);
TypeSpec termSem(SemanticChecker* checker);
TypeSpec factorSem(SemanticChecker* checker);
TypeSpec unarySem(SemanticChecker* checker);
TypeSpec primarySem(SemanticChecker* checker);
int whileSTMTSem(SemanticChecker* checker);
int ifSTMTSem(SemanticChecker* checker);
int returnSTMTSem(SemanticChecker* checker);
int breakSTMTSem(SemanticChecker* checker);
int blockSTMTSem(SemanticChecker* checker);
int methodSTMTSem(SemanticChecker* checker);
int paramListSem(SemanticChecker* checker);
int argListSem(SemanticChecker* checker);

#endif