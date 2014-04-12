/*
 * Author: Cody Mingus
 *
 * Purpose: Ensure that every block can be free'd without any seg
 * faults.
 */

#include "myMalloc.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    myInit(1);
    char* ptrs[2048];
    int i;
    for (i = 0; i < 2048; i++) {
        ptrs[i] = myMalloc(64 * sizeof(char));
    }
    for (i = 0; i < 2048; i++) {
        myFree(ptrs[i]);
    }
    return 0;
}
