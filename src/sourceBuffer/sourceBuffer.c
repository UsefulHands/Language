#include "sourceBuffer.h"
#include <stdio.h>
#include <stdlib.h>

char* readSource(char* fileLoc) {
    if(fileLoc == NULL) return NULL;
    FILE* file = fopen(fileLoc, "r");
    if(file == NULL)  {
        printf("%s", "file is NULL");
        return NULL;
    }
    char* charBuffer = malloc(sizeof(char) * MAX_CHARS_TO_READ + 1);
    char sentence[MAX_CHARS_PER_ROW];
    int index = 0;
    while(fgets(sentence, MAX_CHARS_PER_ROW, file)) {
        int i = 0;
        while(sentence[i] != '\0') {
            charBuffer[index++] = sentence[i++];
        }
    }
    charBuffer[index] = '\0';
    fclose(file);
    return charBuffer;
}