#include "allocator.hpp"
#include "sequential_allocator.hpp"
#include "parallel_allocator.hpp"
#include "libmymalloc.hpp"

extern "C" {

#ifdef PROG1
SequentialAllocator<false> *alloc;
int myInit(int num_cores) {
    auto myalloc = SequentialAllocator<false>();
#endif

#ifdef PROG2
SequentialAllocator<true> *alloc;
int myInit(int num_cores) {
    auto myalloc = SequentialAllocator<true>();
#endif

#ifdef PROG3
ParallelAllocator<false> *alloc;
int myInit(int num_cores) {
    auto myalloc = ParallelAllocator<false>(num_cores);
#endif

#ifdef PROG4
ParallelAllocator<true> *alloc;
int myInit(int num_cores) {
    auto myalloc = ParallelAllocator<true>(num_cores);
#endif

    alloc = &myalloc;
    return 0;
}

void *myMalloc(int size) {
    return alloc->malloc(size);
}

void myFree(void *ptr) {
    alloc->free(ptr);
}

}
