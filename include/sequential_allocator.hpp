#ifndef _SEQ_ALLOC_HPP_
#define _SEQ_ALLOC_HPP_ 

#include <cstddef>
#include <cstdint>
#include <assert.h>
#include "allocator.hpp"

template<std::size_t block_size>
struct FreeListNode {
    //uint64_t size = block_size; If I was using a real C++ compiler D:
    uint64_t size;
    struct FreeListNode *next;
    char data[block_size];
};

template<int length, std::size_t block_size>
class FreeList {
    public:
        FreeList();
        void *pop();
        void push(void *node);
    private:
        FreeListNode<block_size> nodes[length];
        FreeListNode<block_size> *head;
};

template<int length, std::size_t block_size>
FreeList<length, block_size>::FreeList() {
    for (int i = 0; i < length; ++i) {
        nodes[i].next = &nodes[i+1];
        nodes[i].size = block_size;
    }
    nodes[length - 1].next = NULL;
    head = nodes;
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

template<int length, std::size_t block_size>
void FreeList<length, block_size>::push(void *node) {
    auto old_head = head;
    head = (FreeListNode<block_size> *) node;
    head->next = old_head;
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
    char *block_start = ((char *) ptr) - sizeof(void *) - sizeof(uint64_t);
    int block_size = *((int *) block_start);
    if (block_size > 64)
        large_list.push((void *) block_start);
    else
        small_list.push((void *) block_start);
}

#endif
