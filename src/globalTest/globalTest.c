#include "globalTest.h"
#include "../lexer/lexerGetTokensTest.h"
#include "../lexer/lexerLoadTokensTest.h"
#include "../sourceBuffer/sourceBufferTest.h"
#include "../parser/parserTest.h"
#include "../semanticAnalyzer/semanticAnalyzerTest.h"

void testAll() {
    //testTokenization();
    //testTokenLoading();
    //testSourceRead();
    //testParser();
    testSemanticAnalyzer();
}