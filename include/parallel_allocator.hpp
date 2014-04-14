#ifndef _PAR_ALLOC_HPP_
#define _PAR_ALLOC_HPP_ 

#include <cstddef>
#include <vector>
#include <pthread.h>
#include "allocator.hpp"
#include "sequential_allocator.hpp"

class ParallelAllocator: public Allocator {
    public:
        ParallelAllocator(int num_cores);
        void *malloc(int size);
        void free(void *ptr);
    private:
        std::vector<SequentialAllocator<>> allocators;
        int next_allocator;
        pthread_key_t key;
        SequentialAllocator<> *get_allocator();
};

ParallelAllocator::ParallelAllocator(int num_cores) {
    allocators = std::vector<SequentialAllocator<>>(num_cores);
    next_allocator = 0;
    pthread_key_create(&key, NULL);
}

SequentialAllocator<> *ParallelAllocator::get_allocator() {
    void *allocator = pthread_getspecific(key);
    if (allocator == NULL) {
        allocator = &allocators.at(next_allocator++);
        pthread_setspecific(key, allocator);
    }
    return (SequentialAllocator<> *) allocator;
}

void *ParallelAllocator::malloc(int size) {
    return get_allocator()->malloc(size);
}

void ParallelAllocator::free(void *ptr) {
    return get_allocator()->free(ptr);
}

class ParallelAllocatorWithOverflow: public Allocator {
    public:
        ParallelAllocatorWithOverflow(int num_cores);
        void *malloc(int size);
        void free(void *ptr);
    private:
        ParallelAllocator par_alloc;
        SynchronizedSequentialAllocator<> overflow;
};

ParallelAllocatorWithOverflow::ParallelAllocatorWithOverflow(int num_cores)
: par_alloc(ParallelAllocator(num_cores)) {
}


void *ParallelAllocatorWithOverflow::malloc(int size) {
    void *ptr = par_alloc.malloc(size);
    if (ptr == NULL)
        return overflow.malloc(size);
    return ptr;
}

void ParallelAllocatorWithOverflow::free(void *ptr) {
    FreeListNode<64> *node = (FreeListNode<64> *) (((char *) ptr) - offsetof(FreeListNode<64>, data));
    if (node->flags & SYNCHRONIZED)
        overflow.free(ptr);
    else
        par_alloc.free(ptr);
}

#endif
