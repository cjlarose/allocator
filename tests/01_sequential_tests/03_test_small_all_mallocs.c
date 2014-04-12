/*
 * Author: Cody Mingus
 *
 * Purpose: Ensure that all small sized blocks can be malloc'd without any
 * null pointers or seg faults.
 */

#include "myMalloc.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    myInit(1);
    int i;
    for (i = 0; i < 2048; i++) {
        char* ptr = myMalloc(64 * sizeof(char));
        if (ptr == NULL) {
            fprintf(stderr, "Malloc of small sized memory:\n");
            fprintf(stderr, "Poiner returned by myMalloc was null when calling\n");
            fprintf(stderr, "myMalloc() on iteration number: %d\n", i);
            exit(1);
        }
    }
    return 0;
}
