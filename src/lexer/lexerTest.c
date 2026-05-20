#include "lexerTest.h"
#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>

void testTokenization() {
    int testCount = 5;
    char* sentences[testCount];
    sentences[0] = "x = 5";
    sentences[1] = "if x > 10";
    sentences[2] = "y = x + 3";
    sentences[3] = "while x != 0";
    sentences[4] = "return y";
    TokenType expected[][10] = {
        {TOKEN_IDENTIFIER, TOKEN_OPERATOR, TOKEN_NUMBER},
        {TOKEN_KEYWORD, TOKEN_IDENTIFIER, TOKEN_OPERATOR, TOKEN_NUMBER},
        {TOKEN_IDENTIFIER, TOKEN_OPERATOR, TOKEN_IDENTIFIER, TOKEN_OPERATOR, TOKEN_NUMBER},
        {TOKEN_KEYWORD, TOKEN_IDENTIFIER, TOKEN_OPERATOR, TOKEN_NUMBER},
        {TOKEN_KEYWORD, TOKEN_IDENTIFIER},
    };
    int* tokenCounts = malloc(sizeof(int) * testCount);
    for(int i = 0; i < testCount; i++) {
        tokenCounts[i] = 0;
        Token* tokens = getTokens(sentences[i], &tokenCounts[i]);
        for(int j = 0; j < tokenCounts[i]; j++) {
            printf("%s %d %s\n", tokens[j].type == expected[i][j]?"[TRUE]  ":"[FALSE] ", tokens[j].type, tokens[j].value);
        }
        printf("\n");
    }
}