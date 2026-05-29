#include "parser.h"
#include "../lexer/lexer.h"
#include "../sourceBuffer/sourceBuffer.h"

void testParser() {
    char* fileLoc = "src/documents/parserTest.txt";
    char* charBuffer = readSource(fileLoc);
    int tokenCount = 0;
    Token* tokens = loadTokensFromBuffer(charBuffer, &tokenCount);
    startParser(charBuffer, tokens); 
}