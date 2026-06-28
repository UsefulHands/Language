#include "lexerLoadTokensTest.h"
#include "lexer.h"
#include "../sourceBuffer/sourceBuffer.h"
#include <stdio.h>
#include <stdlib.h>

int testTokenLoading(void) {
    char* fileLoc = "src/documents/sourceBufferTest.txt";
    char* charBuffer = readSource(fileLoc);
    if(charBuffer == NULL) return 0;
    int tokenCount = 0;
    Token* tokens = loadTokensFromBuffer(charBuffer, &tokenCount);
    if(tokens == NULL) {
        free(charBuffer);
        return 0;
    }
    for(int i = 0; i < tokenCount; i++) {
        printf("%s %s\n", tokenTypeAsString[tokens[i].category.type], tokens[i].value);
    }
    int success = tokenCount > 0 && tokens[tokenCount - 1].category.type == TOKEN_EOF;
    free(tokens);
    free(charBuffer);
    return success;
}
