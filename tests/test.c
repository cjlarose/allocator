#include "myMalloc.h"
#include <stdio.h>

int main() {
    myInit(1);
    char* ptrs[5];
    /*
    ptrs[0] = myMalloc(64);
    ptrs[1] = myMalloc(64);
    ptrs[2] = myMalloc(64);
    ptrs[3] = myMalloc(64);
    ptrs[4] = myMalloc(64);

    printf("\n");
    myFree(ptrs[4]);
    ptrs[4] = myMalloc(64);

    printf("\n");
    myFree(ptrs[4]);
    myFree(ptrs[3]);
    ptrs[3] = myMalloc(64);
    ptrs[4] = myMalloc(64);

    printf("\n");
    myFree(ptrs[4]);
    myFree(ptrs[3]);
    myFree(ptrs[2]);
    ptrs[2] = myMalloc(64);
    ptrs[3] = myMalloc(64);
    ptrs[4] = myMalloc(64);

    printf("\n");
    myFree(ptrs[4]);
    myFree(ptrs[3]);
    myFree(ptrs[2]);
    myFree(ptrs[1]);
    myFree(ptrs[0]);
    ptrs[0] = myMalloc(64);
    ptrs[1] = myMalloc(64);
    ptrs[2] = myMalloc(64);
    ptrs[3] = myMalloc(64);
    ptrs[4] = myMalloc(64);
    */

    ptrs[0] = myMalloc(64);
    *ptrs[0] = 7;
    myFree(ptrs[0]);
    ptrs[0] = myMalloc(64);
    printf("Should be 7: %d\n", *ptrs[0]);

    return 0;
}
