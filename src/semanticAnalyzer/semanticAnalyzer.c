#include "semanticAnalyzer.h"
#include "../symtab/symtab.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* symbolTypeAsString[] = {
    "SYMBOL_VARIABLE", 
    "SYMBOL_METHOD"
};

char* typeSpecAsString[] = {
    "TYPE_NUMBER", 
    "TYPE_STRING",
    "TYPE_BOOL",
    "TYPE_NULL"
};

int startSemanticAnalyzer(Token* tokens) {
    SemanticChecker checker;
    checker.tokens = tokens;
    checker.index = 0;
    checker.table = malloc(sizeof(SymbolTable));
    checker.table->count = 0;
    checker.table->parent = NULL;
    int success = programSem(&checker);
    printf("\nSemantic Analyzer success: %d\n", success);
    if(success == 1) {
        int i = 0;
        while(i < checker.table->count) {
            printf("Name: %s, SymbolType: %s, TypeSpec: %s\n"
                , checker.table->symbols[i].name
                , symbolTypeAsString[checker.table->symbols[i].type]
                , typeSpecAsString[checker.table->symbols[i].typeSpec]);
            i++;
        }
    }
    while(checker.table != NULL) {
        checker.table = exitScope(checker.table);
    }
    return success;
}

SymbolTable* enterScope(SymbolTable* current) {
    SymbolTable* newScope = malloc(sizeof(SymbolTable));
    newScope->count = 0;
    newScope->parent = current;
    return newScope;
}

SymbolTable* exitScope(SymbolTable* current) {
    if(current == NULL) return NULL;
    SymbolTable* parent = current->parent;
    freeSymbolTable(current);
    return parent;
}

void freeSymbolTable(SymbolTable* table) {
    if(table == NULL) return;
    for(int i = 0; i < table->count; i++) {
        free(table->symbols[i].name);
    }
    free(table);
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

int getCurrIndexSem(SemanticChecker* checker) {
    return checker->index;
}

void restoreSem(SemanticChecker* checker, int saved) {
    checker->index = saved;
}

Token advanceSem(SemanticChecker* checker) {
    return checker->tokens[++checker->index];
}

Token retreatSem(SemanticChecker* checker) {
    return checker->tokens[--checker->index];
}

Token currSem(SemanticChecker* checker) {
    return checker->tokens[checker->index];
}
