#ifndef SYMTAB_H
#define SYMTAB_H

#define MAX_SYMBOL_COUNT 300

#include "../lexer/lexer.h"
#include "../semanticAnalyzer/semanticAnalyzer.h"

typedef enum { 
    SYMBOL_VARIABLE, 
    SYMBOL_METHOD 
} SymbolType;

typedef enum { 
    TYPE_NUMBER, 
    TYPE_STRING,
    TYPE_BOOL
} TypeSpec;

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

void startSemanticAnalyzer(char* charBuffer, Token* tokens);
SymbolTable* enterScope(SymbolTable* cur);
SymbolTable* exitScope(SymbolTable* curr);
Symbol* lookup(SymbolTable* table, char* name);
int addSymbol(SymbolTable* table, char* name, SymbolType type, TypeSpec typeSpec, int paramCount);

#endif