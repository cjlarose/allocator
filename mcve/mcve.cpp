#include <cstddef>

class Allocator {
public:
    virtual void *malloc(int size) {return nullptr;};
    virtual void free(void *ptr) {};
};

class SequentialAllocator: public Allocator {
public:
    SequentialAllocator() {};
    void *malloc(int size) {return nullptr;};
    void free(void *ptr) {};
};

extern "C" {

    SequentialAllocator *alloc;

    int myInit() {
        SequentialAllocator myalloc = SequentialAllocator();
        alloc = &myalloc;
        return 0;
    }

    void *myMalloc(int size) {
        return alloc->malloc(size);
    }

    void myFree(void *ptr) {
        alloc->free(ptr);
    }

}
