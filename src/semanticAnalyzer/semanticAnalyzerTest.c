#include "semanticAnalyzerTest.h"
#include "semanticAnalyzer.h"
#include "../parser/parser.h"
#include "../lexer/lexer.h"
#include "../sourceBuffer/sourceBuffer.h"

void testSemanticAnalyzer() {
    char* fileLoc = "src/documents/semanticAnalyzerTest.txt";
    char* charBuffer = readSource(fileLoc);
    int tokenCount = 0;
    Token* tokens = loadTokensFromBuffer(charBuffer, &tokenCount);
    int parserResult = startParser(charBuffer, tokens); 
    if(parserResult == 1) {
        int semanticAnalyzerResult = startSemanticAnalyzer(tokens);
    }
}