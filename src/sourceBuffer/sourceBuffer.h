#ifndef SOURCE_BUFFER_H
#define SOURCE_BUFFER_H

#define MAX_CHARS_TO_READ 10000
#define MAX_CHARS_PER_ROW 150

char* readSource(char* fileLoc); // allocated; free with freeSourceBuffer.
void freeSourceBuffer(char* charBuffer);

#endif
