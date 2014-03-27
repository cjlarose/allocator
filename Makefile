CC=gcc
HDR=myMalloc.h

libmymalloc1: libmymalloc1.c $(HDR)
	$(CC) -c libmymalloc1.c
	ar -rv libmymalloc1.a libmymalloc1.o

libmymalloc2: libmymalloc2.c $(HDR)
	$(CC) -c libmymalloc2.c -lpthread
	ar -rv libmymalloc2.a libmymalloc2.o

libmymalloc3: libmymalloc3.c $(HDR)
	$(CC) -c libmymalloc3.c -lpthread
	ar -rv libmymalloc3.a libmymalloc3.o

libmymalloc4: libmymalloc4.c $(HDR)
	$(CC) -c libmymalloc4.c -lpthread
	ar -rv libmymalloc4.a libmymalloc4.o

clean:
	rm -f *.o *.a


