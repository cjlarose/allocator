#include "allocator.hpp"
#include "sequential_allocator.hpp"
#include "parallel_allocator.hpp"
#include "libmymalloc.hpp"

#ifdef PROG1
SequentialAllocator<> *alloc;
int myInit(int num_cores) {
    try {
        alloc = new SequentialAllocator<>();
#endif

#ifdef PROG2
SynchronizedSequentialAllocator *alloc;
int myInit(int num_cores) {
    try {
        alloc = new SynchronizedSequentialAllocator();
#endif

#ifdef PROG3
ParallelAllocator *alloc;
int myInit(int num_cores) {
    try {
        alloc = new ParallelAllocator(num_cores);
#endif

#ifdef PROG4
ParallelAllocator *alloc;
int myInit(int num_cores) {
    try {
        alloc = new ParallelAllocator(num_cores);
#endif

    } catch (std::bad_alloc& ba) {
        return -1;
    }

    return 0;
}

void *myMalloc(int size) {
    return alloc->malloc(size);
}

void myFree(void *ptr) {
    alloc->free(ptr);
}
