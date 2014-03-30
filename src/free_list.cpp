#include <cstddef>
#include "free_list.hpp"

template <long size, std::size_t block_size>
FreeList<size, block_size>::FreeList() {
    //constexpr std::size_t chunk_size = size * block_size;
}

template <long size, std::size_t block_size>
void *FreeList<size, block_size>::malloc() {
    return NULL;
}

template <long size, std::size_t block_size>
void FreeList<size, block_size>::free(void *ptr) {

}
