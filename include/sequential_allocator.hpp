#ifndef _SEQ_ALLOC_HPP_
#define _SEQ_ALLOC_HPP_ 

#include "allocator.hpp"
#include "free_list.hpp"

class SequentialAllocator: public Allocator {
    public:
        void *malloc(int size);
        void free(void *ptr);
    private:
        FreeList<4096, 64> small_list;
        FreeList<256, 1024> large_list;
};

void *SequentialAllocator::malloc(int size) {
    if (size > 64)
        return large_list.pop();
    else
        return small_list.pop();
}

void SequentialAllocator::free(void *ptr) {
    char *block_start = ((char *) ptr) - offsetof(FreeListNode<64>, data);
    int block_size = *((int *) block_start);
    if (block_size > 64)
        large_list.push((void *) block_start);
    else
        small_list.push((void *) block_start);
}

#endif
