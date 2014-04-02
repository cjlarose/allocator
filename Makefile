CC=g++
CFLAGS=--std=c++0x

INCLUDE_DIR=include
HEADERS=$(shell ls $(INCLUDE_DIR)/*.hpp)

SRC_DIR=src

.PHONY: libmymalloc
libmymalloc: libmymalloc1 libmymalloc2 libmymalloc3 libmymalloc4

libmymalloc1: $(SRC_DIR)/libmymalloc.cpp $(HEADERS)
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -D PROG1 -o libmymalloc1.o -c $<
	ar -rv libmymalloc1.a libmymalloc1.o

libmymalloc2: $(SRC_DIR)/libmymalloc.cpp $(HEADERS)
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -pthread -D PROG2 -o libmymalloc2.o -c $<
	ar -rv libmymalloc2.a libmymalloc2.o

libmymalloc3: $(SRC_DIR)/libmymalloc.cpp $(HEADERS)
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -pthread -D PROG3 -o libmymalloc3.o -c $<
	ar -rv libmymalloc3.a libmymalloc3.o

libmymalloc4: $(SRC_DIR)/libmymalloc.cpp $(HEADERS)
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -pthread -D PROG4 -o libmymalloc4.o -c $<
	ar -rv libmymalloc4.a libmymalloc4.o

clean:
	rm -f *.o *.a
