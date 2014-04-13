#ifndef _SEQ_ALLOC_HPP_
#define _SEQ_ALLOC_HPP_ 

#include <mutex>
#include "allocator.hpp"
#include "free_list.hpp"

template <int num_small_blocks = 2048, int num_large_blocks = 128>
class SequentialAllocator: public Allocator {
    public:
        void *malloc(int size);
        void free(void *ptr);
    private:
        FreeList<num_small_blocks, 64> small_list;
        FreeList<num_large_blocks, 1024> large_list;
};

template <int sm_cnt, int lg_cnt>
void *SequentialAllocator<sm_cnt, lg_cnt>::malloc(int size) {
    if (size > 64)
        return large_list.pop();
    else
        return small_list.pop();
}

template <int sm_cnt, int lg_cnt>
void SequentialAllocator<sm_cnt, lg_cnt>::free(void *ptr) {
    char *block_start = ((char *) ptr) - offsetof(FreeListNode<64>, data);
    int block_size = *((int *) block_start);
    if (block_size > 64)
        large_list.push((void *) block_start);
    else
        small_list.push((void *) block_start);
}

class SynchronizedSequentialAllocator: public Allocator {
    public:
        void *malloc(int size);
        void free(void *ptr);
    private:
        SequentialAllocator<2048 * 8, 128 * 8> alloc;
        std::mutex mtx;
};

void *SynchronizedSequentialAllocator::malloc(int size) {
    mtx.lock();
    alloc.malloc(size);
    mtx.unlock();
}

void SynchronizedSequentialAllocator::free(void *ptr) {
    mtx.lock();
    alloc.free(ptr);
    mtx.unlock();
}

#endif
