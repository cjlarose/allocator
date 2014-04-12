/*
 * Author: Cody Mingus
 *
 * Purpose: Ensure that at least one block can be free'd without any seg
 * faults.
 */

#include "myMalloc.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    myInit(1);
    char* ptr = myMalloc(64 * sizeof(char));
    myFree(ptr);
    return 0;
}
