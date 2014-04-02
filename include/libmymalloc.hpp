extern "C" {
    int myInit(int num_cores);
    void *myMalloc(int size);
    void myFree(void *ptr);
}
