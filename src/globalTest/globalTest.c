#include "globalTest.h"
#include "../lexer/lexerTest.h"
#include "../fileReader/fileReaderTest.h"

void testAll() {
    testTokenization();
    testFileReading();
}