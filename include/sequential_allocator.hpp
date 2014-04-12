#ifndef _SEQ_ALLOC_HPP_
#define _SEQ_ALLOC_HPP_ 

#include <cstddef>
#include "allocator.hpp"

template<std::size_t block_size>
struct FreeListNode {
    int size;
    struct FreeListNode *next;
    char data[block_size];
};

const int NUM_SMALL_BLOCKS = 4096;
const int NUM_LARGE_BLOCKS = 256;

const std::size_t SMALL_BLOCK_SZ = 64;
const std::size_t LARGE_BLOCK_SZ = 1024;

class SequentialAllocator: public Allocator {
    public:
        SequentialAllocator();
        void *malloc(int size);
        void free(void *ptr);
    private:
        FreeListNode<SMALL_BLOCK_SZ> small_list[NUM_SMALL_BLOCKS];
        FreeListNode<LARGE_BLOCK_SZ> large_list[NUM_LARGE_BLOCKS];
};

SequentialAllocator::SequentialAllocator() {
    for (int i = 0; i < NUM_SMALL_BLOCKS; ++i) {
        small_list[i].size = SMALL_BLOCK_SZ;
        small_list[i].next = &small_list[i+1];
    }
    small_list[NUM_SMALL_BLOCKS - 1].next = NULL;

    for (int i = 0; i < NUM_LARGE_BLOCKS; ++i) {
        large_list[i].size = LARGE_BLOCK_SZ;
        large_list[i].next = &large_list[i+1];
    }
    large_list[NUM_LARGE_BLOCKS - 1].next = NULL;
}

void *SequentialAllocator::malloc(int size) {
    return NULL;
}

void SequentialAllocator::free(void *ptr) {
}

#endif
