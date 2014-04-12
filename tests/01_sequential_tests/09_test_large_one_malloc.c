/*
 * Author: Cody Mingus
 *
 * Purpose: Ensure that at least 1 call to myMalloc can be made without
 * seg faulting. Also that the pointer returned is non-null.
 */

#include "myMalloc.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    myInit(1);
    char* ptr = myMalloc(1024 * sizeof(char));
    if (ptr == NULL) {
        fprintf(stderr, "1 Malloc of large sized memory:\n");
        fprintf(stderr, "Poiner returned by myMalloc was null when calling\n");
        fprintf(stderr, "myMalloc for the first time.\n");
    }
    return 0;
}
