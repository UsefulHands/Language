#include "lexerGetTokensTest.h"
#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>

int testTokenization(void) {
    int testCount = 20;
    char* sentences[testCount];
    sentences[0] = "x = 5";
    sentences[1] = "x = -5";
    sentences[2] = "x = +3";
    sentences[3] = "x != -1";
    sentences[4] = "x == y";
    sentences[5] = "x >= 10";
    sentences[6] = "x <= 10";
    sentences[7] = "y x ;";
    sentences[8] = "{ x = 5 }";
    sentences[9] = "x = @";
    sentences[10] = "123abc";
    sentences[11] = "";
    sentences[12] = "x";
    sentences[13] = "==";
    sentences[14] = "if x > 10";
    sentences[15] = "y = x + 3";
    sentences[16] = "while x != 0";
    sentences[17] = "return y";
    sentences[18] = "x + -5";
    sentences[19] = "y -+5";
    TokenType expected[][10] = {
        {TOKEN_IDENTIFIER, TOKEN_OPERATOR, TOKEN_NUMBER},
        {TOKEN_IDENTIFIER, TOKEN_OPERATOR, TOKEN_NUMBER},
        {TOKEN_IDENTIFIER, TOKEN_OPERATOR, TOKEN_NUMBER},
        {TOKEN_IDENTIFIER, TOKEN_OPERATOR, TOKEN_NUMBER},
        {TOKEN_IDENTIFIER, TOKEN_OPERATOR, TOKEN_IDENTIFIER},
        {TOKEN_IDENTIFIER, TOKEN_OPERATOR, TOKEN_NUMBER},
        {TOKEN_IDENTIFIER, TOKEN_OPERATOR, TOKEN_NUMBER},
        {TOKEN_IDENTIFIER, TOKEN_IDENTIFIER, TOKEN_PUNCTUATION},
        {TOKEN_PUNCTUATION, TOKEN_IDENTIFIER, TOKEN_OPERATOR, TOKEN_NUMBER, TOKEN_PUNCTUATION},
        {TOKEN_IDENTIFIER, TOKEN_OPERATOR, TOKEN_INVALID},
        {TOKEN_INVALID},
        {},
        {TOKEN_IDENTIFIER},
        {TOKEN_OPERATOR},
        {TOKEN_KEYWORD, TOKEN_IDENTIFIER, TOKEN_OPERATOR, TOKEN_NUMBER},
        {TOKEN_IDENTIFIER, TOKEN_OPERATOR, TOKEN_IDENTIFIER, TOKEN_OPERATOR, TOKEN_NUMBER},
        {TOKEN_KEYWORD, TOKEN_IDENTIFIER, TOKEN_OPERATOR, TOKEN_NUMBER},
        {TOKEN_KEYWORD, TOKEN_IDENTIFIER},
        {TOKEN_IDENTIFIER, TOKEN_OPERATOR, TOKEN_NUMBER},
        {TOKEN_IDENTIFIER, TOKEN_OPERATOR, TOKEN_NUMBER}
    };
    int expectedCounts[] = {
        3, 3, 3, 3, 3,
        3, 3, 3, 5, 3,
        1, 0, 1, 1, 4,
        5, 4, 2, 3, 3
    };
    int success = 1;
    printf("\nTokens goes like: \n");
    for(int i = 0; i < testCount; i++) {
        int tokenCount = 0;
        Token* tokens = getTokens(sentences[i], &tokenCount);
        if(tokens == NULL) {
            success = 0;
            printf("[TOKEN_NULL]\n");
            continue;
        }
        for(int j = 0; j < tokenCount; j++) {
            printf("[%s -> %s] ", tokenTypeAsString[tokens[j].category.type] , tokens[j].value);
        }
        printf("\n");

        if(tokenCount != expectedCounts[i] + 1) {
            success = 0;
        } else {
            for(int j = 0; j < expectedCounts[i]; j++) {
                if(tokens[j].category.type != expected[i][j]) {
                    success = 0;
                }
            }
            if(tokens[expectedCounts[i]].category.type != TOKEN_EOF) {
                success = 0;
            }
        }
        free(tokens);
    }
    return success;
}
