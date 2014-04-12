#ifndef _PAR_ALLOC_HPP_
#define _PAR_ALLOC_HPP_ 

#include <cstddef>
#include <vector>
#include "allocator.hpp"
#include "sequential_allocator.hpp"

class ParallelAllocator: public Allocator {
    public:
        ParallelAllocator(int num_cores);
        void *malloc(int size);
        void free(void *ptr);
    private:
        std::vector<SequentialAllocator> allocators;
};

#endif
