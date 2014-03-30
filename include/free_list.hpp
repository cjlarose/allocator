#include <cstddef>

template <long size, std::size_t block_size>
class FreeList {
    public:
        FreeList();
        void *malloc();
        void free(void *ptr);

        class FreeListNode {
            long size_tag;
            FreeListNode *next;
            char data[block_size];
        };
    private:
        FreeListNode nodes[size];
        FreeListNode *head;
};
