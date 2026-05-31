#include "symtab.h"
#include <stdlib.h>

void startSemanticAnalyzer(char* charBuffer, Token* tokens) {
    SemanticChecker checker;
    checker.tokens = tokens;
    checker.index = 0;
    checker.table = malloc(sizeof(SymbolTable));
    checker.table->count = 0;
    checker.table->parent = NULL;
    int success = semProgram(&checker);
    printf("\nSemantic Analyzer success: %d", success);
}

SymbolTable* enterScope(SymbolTable* current) {
    SymbolTable* newScope = malloc(sizeof(SymbolTable));
    newScope->count = 0;
    newScope->parent = current;
    return newScope;
}

SymbolTable* exitScope(SymbolTable* current) {
    SymbolTable* parent = current->parent;
    for(int i = 0; i < current->count; i++) {
        free(current->symbols[i].name);
    }
    free(current);
    return parent;
}

Symbol* lookup(SymbolTable* table, char* name) {
    while(table != NULL) {
        for(int i = table->count - 1; i >= 0; i--) {
            if(strcmp(table->symbols[i].name, name) == 0) return &table->symbols[i];          
        } 
        table = table->parent;  
    } return NULL;
}

int addSymbol(SymbolTable* table, char* name, SymbolType type, TypeSpec typeSpec, int paramCount) {
    if(table->count >= MAX_SYMBOL_COUNT) return -1;
    for(int i = 0; i < table->count; i++) {
        if(strcmp(table->symbols[i].name, name) == 0) return -1;
    }
    Symbol* s = &table->symbols[table->count++];
    s->name = strdup(name);
    s->type = type;
    s->typeSpec = typeSpec;
    s->paramCount = paramCount;
    return 0;
}