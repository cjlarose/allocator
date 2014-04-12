/*
 * Author: Cody Mingus
 *
 * Purpose: Ensure that every block can be malloc'd without any seg
 * faults.
 */

#include "myMalloc.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_BLOCKS 2048 * 8
#define SIZE 64

int main() {
    myInit(1);
    char* ptrs[NUM_BLOCKS];
    int i;
    for (i = 0; i < NUM_BLOCKS; i++) {
        ptrs[i] = myMalloc(SIZE * sizeof(char));
    }
    for (i = 0; i < NUM_BLOCKS; i++) {
        myFree(ptrs[i]);
    }
    return 0;
}
