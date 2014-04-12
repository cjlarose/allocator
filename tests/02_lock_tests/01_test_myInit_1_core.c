/*
 * Author: Cody Mingus
 *
 * Purpose: Make sure that myInit() can be called without causing any issues.
 * An issue could be a wrong returned status or a seg fault.
 */

#include "myMalloc.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int status = myInit(1);
    if (status != 0) {
        fprintf(stderr, "myInit() Test:\n");
        fprintf(stderr, "Return value: %d. Expected value: 0\n", status);
        fprintf(stderr, "It's highly unlikely that you ran out of memory.\n");
        fprintf(stderr, "1. Make sure that your machine has about 512K of RAM free\n");
        fprintf(stderr, "2. Make sure that myInit() returns a 0 unless malloc failed.\n");
        fprintf(stderr, "3. Make sure myInit() returns -1 if malloc did fail.\n");
        exit(1);
    }
    return 0;
}
