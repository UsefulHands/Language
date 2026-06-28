#include "globalTest/globalTest.h"
#include <stdio.h>

int main(int argc, char** argv) {
    int success = 0;

    if(argc <= 1) {
        success = testAll();
    } else {
        success = testSelected(argc, argv);
    }

    return success == 1 ? 0 : 1;
}
