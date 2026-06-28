#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#define MAX_SYMBOL_COUNT 300

#include "../lexer/lexer.h"

typedef enum { 
    SYMBOL_VARIABLE, 
    SYMBOL_METHOD 
} SymbolType;

extern char* symbolTypeAsString[];

typedef enum { 
    TYPE_NUMBER, 
    TYPE_STRING,
    TYPE_BOOL,
    TYPE_NULL
} TypeSpec;

extern char* typeSpecAsString[];

typedef struct Symbol {
    char* name;
    SymbolType type;
    TypeSpec typeSpec;
    int paramCount;
} Symbol;

typedef struct SymbolTable {
    Symbol symbols[MAX_SYMBOL_COUNT];
    int count;
    struct SymbolTable* parent;
} SymbolTable;

typedef struct {
    Token* tokens;
    int index;
    SymbolTable* table;
} SemanticChecker;

int startSemanticAnalyzer(Token* tokens);

SymbolTable* enterScope(SymbolTable* cur); // allocated; free with exitScope.
SymbolTable* exitScope(SymbolTable* curr);
void freeSymbolTable(SymbolTable* table);
Symbol* lookup(SymbolTable* table, char* name);
int addSymbol(SymbolTable* table, char* name, SymbolType type, TypeSpec typeSpec, int paramCount);

int getCurrIndexSem(SemanticChecker* checker);
void restoreSem(SemanticChecker* checker, int saved);
Token advanceSem(SemanticChecker* checker);
Token retreatSem(SemanticChecker* checker);
Token currSem(SemanticChecker* checker);

#endif
