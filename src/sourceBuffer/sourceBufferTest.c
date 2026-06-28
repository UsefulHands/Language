#include "sourceBufferTest.h"
#include "sourceBuffer.h"
#include <stdio.h>
#include <stdlib.h>

int testSourceRead(void) {
    char* fileLoc = "src/documents/sourceBufferTest.txt";
    char* charBuffer = readSource(fileLoc);
    if(charBuffer == NULL) return 0;
    printf("\nBuffer goes like: \n[ ");
    int i = 0;
    while(charBuffer[i] != '\0') {
        if(charBuffer[i] == '\n') {
            printf("[\\n] \n");
        } else {
            printf("[%c] ", charBuffer[i]);
        }
        i++;
    }
    printf("[\\0] ]");
    free(charBuffer);
    return 1;
}
