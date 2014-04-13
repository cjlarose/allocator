#include "allocator.hpp"
#include "sequential_allocator.hpp"
#include "parallel_allocator.hpp"
#include "libmymalloc.hpp"

#ifdef PROG1
SequentialAllocator *alloc;
int myInit(int num_cores) {
    alloc = new SequentialAllocator();
#endif

#ifdef PROG2
SequentialAllocator *alloc;
int myInit(int num_cores) {
    alloc = new SequentialAllocator();
#endif

#ifdef PROG3
ParallelAllocator *alloc;
int myInit(int num_cores) {
    alloc = new ParallelAllocator(num_cores);
#endif

#ifdef PROG4
ParallelAllocator *alloc;
int myInit(int num_cores) {
    alloc = new ParallelAllocator(num_cores);
#endif

    return 0;
}

void *myMalloc(int size) {
    return alloc->malloc(size);
}

void myFree(void *ptr) {
    alloc->free(ptr);
}
