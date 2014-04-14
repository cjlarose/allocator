#ifndef _FREE_LIST_HPP_
#define _FREE_LIST_HPP_ 

#include <cstddef>

template<std::size_t block_size>
struct FreeListNode {
    int size;
    int flags;
    struct FreeListNode *next;
    char data[block_size];
};

enum FREE_LIST_FLAG {
    UNSYNCHRONIZED = 1,
    SYNCHRONIZED = 2
};

template<int length, std::size_t block_size>
class FreeList {
    public:
        FreeList(int flags);
        void *pop();
        void push(void *node);
    private:
        FreeListNode<block_size> nodes[length];
        FreeListNode<block_size> *head;
};

/*
 * Initialize list by making a singly-linked list and tagging each node with a
 * block size.
 */
template<int length, std::size_t block_size>
FreeList<length, block_size>::FreeList(int flags) {
    for (int i = 0; i < length; ++i) {
        nodes[i].next = &nodes[i+1];
        nodes[i].size = block_size;
        nodes[i].flags = flags;
    }
    nodes[length - 1].next = NULL;
    head = nodes;
}

/*
 * Pop the head of the list off and give the data member to the caller. Advance
 * the head pointer.
 */
template<int length, std::size_t block_size>
void *FreeList<length, block_size>::pop() {
    auto client_block = head;
    if (client_block == NULL)
        return NULL;
    head = client_block->next;
    return &client_block->data;
}

template<int length, std::size_t block_size>
void FreeList<length, block_size>::push(void *node) {
    auto old_head = head;
    head = (FreeListNode<block_size> *) node;
    head->next = old_head;
}

#endif
