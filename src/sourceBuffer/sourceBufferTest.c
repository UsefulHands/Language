#include "sourceBufferTest.h"
#include "sourceBuffer.h"
#include <stdio.h>

void testFileReading() {
    char* fileLoc = "src/documents/sourceBufferTest.txt";
    char* charBuffer = readSource(fileLoc);
    if(charBuffer == NULL) return;
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
}