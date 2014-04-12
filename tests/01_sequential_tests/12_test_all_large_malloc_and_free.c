/*
 * Author: Cody Mingus
 *
 * Purpose: Ensure that all blocks can be free'd without any seg faults.
 */

#include "myMalloc.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    myInit(1);
    char* ptrs[128];
    int i;
    for (i = 0; i < 128; i++) {
        ptrs[i] = myMalloc(1024 * sizeof(char));
    }
    for (i = 0; i < 128; i++) {
        myFree(ptrs[i]);
    }
    return 0;
}
