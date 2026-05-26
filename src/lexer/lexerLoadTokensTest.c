#include "lexerLoadTokensTest.h"
#include "lexer.h"
#include "../sourceBuffer/sourceBuffer.h"
#include <stdio.h>
#include <stdlib.h>

void testTokenLoading() {
    char* fileLoc = "src/documents/sourceBufferTest.txt";
    char* charBuffer = readSource(fileLoc);
    int tokenCount = 0;
    Token* tokens = loadTokensFromBuffer(charBuffer, &tokenCount);
    for(int i = 0; i < tokenCount; i++) {
        printf("%s %s\n", tokenTypeAsString[tokens[i].category.type], tokens[i].value);
    }
    free(tokens);
    free(charBuffer);
}