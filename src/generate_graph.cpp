#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include <pthread.h>
#include "sequential_allocator.hpp"
#include "parallel_allocator.hpp"

/*
void* allocate(void* ptr) {
    struct thread_var* vars = (struct thread_var*) ptr;
    int i;
    for (i = vars->offset; i < (vars->offset + vars->amount); i++) {
        vars->ptrs[i] = myMalloc(SIZE * sizeof(char));
        assert(vars->ptrs[i] != NULL);
    }
    for (i = vars->offset; i < (vars->offset + vars->amount); i++) {
        myFree(vars->ptrs[i]);
    }
}
*/

const int SM_BLOCKS_PER_THREAD = 2048;
const int LG_BLOCKS_PER_THREAD = 128;

void *allocate(void *data) {
    Allocator *alloc = (Allocator *) data;
    void* ptrs[SM_BLOCKS_PER_THREAD + LG_BLOCKS_PER_THREAD];

    for (int round = 0; round < 1024; ++round) {
        int i = 0;
        for (; i < SM_BLOCKS_PER_THREAD; ++i) {
            ptrs[i] = alloc->malloc(64);
            assert(ptrs[i] != NULL);
        }

        for (; i < LG_BLOCKS_PER_THREAD + SM_BLOCKS_PER_THREAD; ++i) {
            ptrs[i] = alloc->malloc(1024);
            assert(ptrs[i] != NULL);
        }

        for (int j = 0; j < SM_BLOCKS_PER_THREAD + LG_BLOCKS_PER_THREAD; ++j) {
            alloc->free(ptrs[j]);
        }
    }
}

void test_alloc(Allocator *alloc, int p) {
    pthread_t *threads = (pthread_t *) malloc(sizeof(pthread_t) * p);
    for (int i = 0; i < p; ++i) {
        pthread_create(&threads[i], NULL, allocate, alloc);
    }
    for (int i = 0; i < p; ++i) {
        pthread_join(threads[i], NULL);
    }
}

struct timeval time_alloc(Allocator *alloc, int p) {
    struct timeval start, stop, elapsed;
    gettimeofday(&start, NULL);
    test_alloc(alloc, p);
    gettimeofday(&stop, NULL);
    elapsed.tv_sec = stop.tv_sec - start.tv_sec;
    elapsed.tv_usec = stop.tv_usec - start.tv_usec;
    return elapsed;
}

int main() {
    Allocator *alloc;

    std::cout << "Program 2: Synchronized\n";
    for (int p = 1; p <= 8; ++p) {
        alloc = new SynchronizedSequentialAllocator<2048 * 8, 128 * 8>();
        struct timeval elapsed = time_alloc(alloc, p);
        double elapsed_d = elapsed.tv_sec + elapsed.tv_usec / 1000000.0;
        std::cout << "(" << p << ", " << elapsed_d << ")\n";
    }

    return 0;
}
/*
int main() {
    myInit(NUM_THREADS);
    void* ptrs[NUM_THREADS * BLOCKS_PER_THREAD];
    int i;

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setscope(&attr,PTHREAD_SCOPE_SYSTEM);
    pthread_t threads[NUM_THREADS];
    struct thread_var vars[NUM_THREADS];
    for (i = 0; i < NUM_THREADS; i++) {
        struct thread_var* var = &vars[i];
        var->offset = BLOCKS_PER_THREAD * i;
        var->amount = BLOCKS_PER_THREAD;
        var->ptrs = ptrs;
        pthread_create(&threads[i], &attr, allocate, (void*) var);
    }
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    return 0;
}
*/
