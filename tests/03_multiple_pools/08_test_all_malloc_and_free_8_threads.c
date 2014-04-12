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

#define SMALL_SIZE 64
#define LARGE_SIZE 1024
#define NUM_THREADS 8
#define NUM_SMALL_BLOCKS 2048 * NUM_THREADS
#define NUM_LARGE_BLOCKS 128 * NUM_THREADS

struct thread_var {
    char** small_ptrs;
    char** large_ptrs;
    int id;
};

void* allocate(void* ptr) {
    struct thread_var* vars = (struct thread_var*) ptr;
    int i, start;
    start = vars->id * 2048;
    for (i = start; i < (start + (NUM_SMALL_BLOCKS / NUM_THREADS)); i++) {
        vars->small_ptrs[i] = myMalloc(SMALL_SIZE * sizeof(char));
    }
    start = vars->id * 128;
    for (i = start; i < (start + (NUM_LARGE_BLOCKS / NUM_THREADS)); i++) {
        vars->large_ptrs[i] = myMalloc(LARGE_SIZE * sizeof(char));
    }
    start = vars->id * 2048;
    for (i = start; i < (start + (NUM_SMALL_BLOCKS / NUM_THREADS)); i++) {
        myFree(vars->small_ptrs[i]);
    }
    start = vars->id * 128;
    for (i = start; i < (start + (NUM_LARGE_BLOCKS / NUM_THREADS)); i++) {
        myFree(vars->large_ptrs[i]);
    }
}

int main() {
    myInit(NUM_THREADS);
    char* small_ptrs[NUM_SMALL_BLOCKS];
    char* large_ptrs[NUM_LARGE_BLOCKS];
    int i;

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setscope(&attr,PTHREAD_SCOPE_SYSTEM);
    pthread_t threads[NUM_THREADS];
    struct thread_var vars[NUM_THREADS];
    for (i = 0; i < NUM_THREADS; i++) {
        struct thread_var* var = &vars[i];
        var->id = i;
        var->small_ptrs = small_ptrs;
        var->large_ptrs = large_ptrs;
        pthread_create(&threads[i], &attr, allocate, (void*) var);
    }
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    return 0;
}
