#include "parserTest.h"
#include "parser.h"
#include "../lexer/lexer.h"
#include "../sourceBuffer/sourceBuffer.h"
#include <stddef.h>

int testParser(void) {
    char* fileLoc = "src/documents/parserTest.txt";
    char* charBuffer = readSource(fileLoc);
    if(charBuffer == NULL) return 0;
    int tokenCount = 0;
    Token* tokens = loadTokensFromBuffer(charBuffer, &tokenCount);
    if(tokens == NULL) return 0;
    return startParser(charBuffer, tokens);
}
