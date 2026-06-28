#include "globalTest.h"
#include "../lexer/lexerGetTokensTest.h"
#include "../lexer/lexerLoadTokensTest.h"
#include "../sourceBuffer/sourceBufferTest.h"
#include "../parser/parserTest.h"
#include "../semanticAnalyzer/semanticAnalyzerTest.h"
#include <stdio.h>
#include <string.h>

static int runTest(char* testName, int (*testFn)(void)) {
    printf("\n\n=== %s ===\n", testName);
    int success = testFn();
    printf("\n%s: %s\n", testName, success == 1 ? "PASS" : "FAIL");
    return success;
}

static int testLexer(void) {
    int success = 1;
    if(runTest("Lexer tokenization", testTokenization) != 1) success = 0;
    if(runTest("Lexer load tokens", testTokenLoading) != 1) success = 0;
    return success;
}

static int testSourceBuffer(void) {
    return runTest("Source buffer", testSourceRead);
}

static int testParserRunner(void) {
    return runTest("Parser", testParser);
}

static int testSemanticRunner(void) {
    return runTest("Semantic analyzer", testSemanticAnalyzer);
}

static void printTestHelp(void) {
    printf("Available tests: all, lexer, lexer-tokens, lexer-load, source, parser, semantic\n");
}

static int testByName(char* testName) {
    if(strcmp(testName, "all") == 0) return testAll();
    if(strcmp(testName, "lexer") == 0) return testLexer();
    if(strcmp(testName, "lexer-tokens") == 0) return runTest("Lexer tokenization", testTokenization);
    if(strcmp(testName, "lexer-load") == 0) return runTest("Lexer load tokens", testTokenLoading);
    if(strcmp(testName, "source") == 0) return testSourceBuffer();
    if(strcmp(testName, "parser") == 0) return testParserRunner();
    if(strcmp(testName, "semantic") == 0) return testSemanticRunner();

    printf("Unknown test: %s\n", testName);
    printTestHelp();
    return 0;
}

int testSelected(int argc, char** argv) {
    int success = 1;
    for(int i = 1; i < argc; i++) {
        if(testByName(argv[i]) != 1) success = 0;
    }
    return success;
}

int testAll(void) {
    int success = 1;
    if(testSourceBuffer() != 1) success = 0;
    if(testLexer() != 1) success = 0;
    if(testParserRunner() != 1) success = 0;
    if(testSemanticRunner() != 1) success = 0;
    return success;
}
