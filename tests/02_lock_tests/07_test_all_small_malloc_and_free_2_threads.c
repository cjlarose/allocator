/*
 * Author: Cody Mingus
 *
 * Purpose: Ensure that at least 2 threads can malloc without causing any
 * issues
 */

#include "myMalloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_BLOCKS 2048 * 8
#define SIZE 64
#define NUM_THREADS 2

struct thread_var {
    char** ptrs;
    int offset;
    int amount;
};

void* allocate(void* ptr) {
    struct thread_var* vars = (struct thread_var*) ptr;
    int i;
    for (i = vars->offset; i < (vars->offset + vars->amount); i++) {
        vars->ptrs[i] = myMalloc(SIZE * sizeof(char));
    }
}

int main() {
    myInit(NUM_THREADS);
    char* ptrs[NUM_BLOCKS];
    int i;

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setscope(&attr,PTHREAD_SCOPE_SYSTEM);
    pthread_t threads[NUM_THREADS];
    struct thread_var vars[NUM_THREADS];
    for (i = 0; i < NUM_THREADS; i++) {
        struct thread_var* var = &vars[i];
        var->offset = 2048 * i;
        var->amount = 2048;
        var->ptrs = ptrs;
        pthread_create(&threads[i], &attr, allocate, (void*) var);
    }
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    for (i = 0; i < 4096; i++) {
        myFree(ptrs[i]);
    }
    return 0;
}
