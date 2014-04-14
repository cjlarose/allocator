#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include <pthread.h>
#include "sequential_allocator.hpp"
#include "parallel_allocator.hpp"

const int SM_BLOCKS_PER_THREAD = 2048;
const int LG_BLOCKS_PER_THREAD = 128;

void *allocate(void *data) {
    Allocator *alloc = (Allocator *) data;
    void* ptrs[SM_BLOCKS_PER_THREAD + LG_BLOCKS_PER_THREAD];

    for (int round = 0; round < 1024; ++round) {
        int i = 0;
        for (; i < SM_BLOCKS_PER_THREAD; ++i)
            ptrs[i] = alloc->malloc(64);

        for (; i < LG_BLOCKS_PER_THREAD + SM_BLOCKS_PER_THREAD; ++i)
            ptrs[i] = alloc->malloc(1024);

        for (int j = 0; j < SM_BLOCKS_PER_THREAD + LG_BLOCKS_PER_THREAD; ++j)
            alloc->free(ptrs[j]);
    }

}

typedef struct {
    Allocator *alloc;
    int p;
} thread_data_t;

void *allocate_p(void *data) {
    thread_data_t *t_data = (thread_data_t *) data;
    int p = t_data->p;
    Allocator *alloc = t_data->alloc;
    for (int i = 0; i < p; ++i)
        allocate(alloc);
}

void test_par_alloc(Allocator *alloc, int p) {
    pthread_t *threads = (pthread_t *) malloc(sizeof(pthread_t) * p);
    for (int i = 0; i < p; ++i) {
        pthread_create(&threads[i], NULL, allocate, alloc);
    }
    for (int i = 0; i < p; ++i) {
        pthread_join(threads[i], NULL);
    }
}

struct timeval time_par_alloc(Allocator *alloc, int p) {
    struct timeval start, stop, elapsed;
    gettimeofday(&start, NULL);
    test_par_alloc(alloc, p);
    gettimeofday(&stop, NULL);
    elapsed.tv_sec = stop.tv_sec - start.tv_sec;
    elapsed.tv_usec = stop.tv_usec - start.tv_usec;
    return elapsed;
}

void test_seq_alloc(Allocator *alloc, int p) {
    pthread_t *threads = (pthread_t *) malloc(sizeof(pthread_t) * p);

    thread_data_t data;
    data.alloc = alloc;
    data.p = p;

    thread_data_t no_work_data;
    no_work_data.alloc = alloc;
    no_work_data.p = 0;

    for (int i = 0; i < p; ++i) {
        pthread_create(&threads[i], NULL, allocate_p, i == 0 ? &data : &no_work_data);
    }
    for (int i = 0; i < p; ++i) {
        pthread_join(threads[i], NULL);
    }
}

struct timeval time_seq_alloc(Allocator *alloc, int p) {
    struct timeval start, stop, elapsed;
    gettimeofday(&start, NULL);
    test_seq_alloc(alloc, p);
    gettimeofday(&stop, NULL);
    elapsed.tv_sec = stop.tv_sec - start.tv_sec;
    elapsed.tv_usec = stop.tv_usec - start.tv_usec;
    return elapsed;
}

void par_test(int p) {
    ParallelAllocator alloc = ParallelAllocator(p);
    struct timeval elapsed = time_par_alloc(&alloc, p);
    double elapsed_d = elapsed.tv_sec + elapsed.tv_usec / 1000000.0;
    std::cout << "(" << p << ", " << elapsed_d << ")\n";
}

int main() {
    Allocator *alloc;
    std::cout << "Program 1: Sequential\n";
    for (int p = 1; p <= 8; ++p) {
        alloc = new SequentialAllocator<2048, 128>();
        struct timeval elapsed = time_seq_alloc(alloc, p);
        double elapsed_d = elapsed.tv_sec + elapsed.tv_usec / 1000000.0;
        std::cout << "(" << p << ", " << elapsed_d << ")\n";
    }

    std::cout << "Program 2: Synchronized\n";
    for (int p = 1; p <= 8; ++p) {
        alloc = new SynchronizedSequentialAllocator<2048 * 8, 128 * 8>();
        struct timeval elapsed = time_par_alloc(alloc, p);
        double elapsed_d = elapsed.tv_sec + elapsed.tv_usec / 1000000.0;
        std::cout << "(" << p << ", " << elapsed_d << ")\n";
    }

    std::cout << "Program 3: Local Lists\n";
    for (int p = 1; p <= 8; ++p) {
        par_test(p);
    }

    return 0;
}
