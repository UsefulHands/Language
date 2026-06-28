#include "semanticAnalyzerTest.h"
#include "semanticAnalyzer.h"
#include "../parser/parser.h"
#include "../lexer/lexer.h"
#include "../sourceBuffer/sourceBuffer.h"
#include <stddef.h>

int testSemanticAnalyzer(void) {
    char* fileLoc = "src/documents/semanticAnalyzerTest.txt";
    char* charBuffer = readSource(fileLoc);
    if(charBuffer == NULL) return 0;
    int tokenCount = 0;
    Token* tokens = loadTokensFromBuffer(charBuffer, &tokenCount);
    if(tokens == NULL) return 0;
    int parserResult = startParser(charBuffer, tokens); 
    if(parserResult == 1) {
        return startSemanticAnalyzer(tokens);
    }
    return 0;
}
