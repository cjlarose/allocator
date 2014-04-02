#ifndef _ALLOCATOR_HPP_
#define _ALLOCATOR_HPP_

class Allocator {
public:
    virtual void *malloc(int size) = 0;
    virtual void free(void *ptr) = 0;
};

#endif
