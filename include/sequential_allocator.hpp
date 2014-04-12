#ifndef _SEQ_ALLOC_HPP_
#define _SEQ_ALLOC_HPP_ 

#include <cstddef>
#include <assert.h>
#include "allocator.hpp"

template<std::size_t block_size>
struct FreeListNode {
    int size = block_size;
    struct FreeListNode *next;
    char data[block_size];
};

template<int length, std::size_t block_size>
class FreeList {
    public:
        FreeList();
        void *pop();
        void push(void *ptr);
    private:
        FreeListNode<block_size> nodes[length];
        FreeListNode<block_size> *head;
};

template<int length, std::size_t block_size>
FreeList<length, block_size>::FreeList() {
    for (int i = 0; i < length; ++i)
        nodes[i].next = &nodes[i+1];
    nodes[length - 1].next = NULL;
}

template<int length, std::size_t block_size>
void *FreeList<length, block_size>::pop() {
    auto client_block = head;
    if (client_block == NULL) {
        assert("Insufficient memory");
        return NULL;
    }
    head = client_block->next;
    return &client_block->data;
}

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
}

#endif
