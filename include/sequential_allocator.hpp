#ifndef _SEQ_ALLOC_HPP_
#define _SEQ_ALLOC_HPP_ 

#include <cstddef>
#include <mutex>
#include "allocator.hpp"

template<std::size_t block_size>
struct FreeListNode {
    int size;
    struct FreeListNode *next;
    char data[block_size];
};

template<bool synchronized>
class SequentialAllocator: public Allocator {
    public:
        SequentialAllocator();
        void *malloc(int size);
        void free(void *ptr);
    private:
        FreeListNode<64> small_list[4096];
        FreeListNode<1024> large_list[256];
        //std::mutex mutex;
};

template <bool synchronized>
SequentialAllocator<synchronized>::SequentialAllocator() {
}

template <bool synchronized>
void *SequentialAllocator<synchronized>::malloc(int size) {
    return NULL;
}

template <bool synchronized>
void SequentialAllocator<synchronized>::free(void *ptr) {
}

#endif
