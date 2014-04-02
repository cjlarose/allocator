CC=g++
CFLAGS=--std=c++0x

INCLUDE_DIR=include
HEADERS=$(shell ls $(INCLUDE_DIR)/*.hpp)

SRC_DIR=src
BUILD_DIR=build

.PHONY: libmymalloc
libmymalloc: libmymalloc1 libmymalloc2 libmymalloc3 libmymalloc4

libmymalloc1: $(SRC_DIR)/libmymalloc.cpp $(HEADERS)
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -D PROG1 -o $(BUILD_DIR)/libmymalloc1.o -c $<
	ar -rv libmymalloc1.a $(BUILD_DIR)/libmymalloc1.o

libmymalloc2: $(SRC_DIR)/libmymalloc.cpp $(HEADERS)
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -pthread -D PROG2 -o $(BUILD_DIR)/libmymalloc2.o -c $<
	ar -rv libmymalloc2.a $(BUILD_DIR)/libmymalloc2.o

libmymalloc3: $(SRC_DIR)/libmymalloc.cpp $(HEADERS)
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -pthread -D PROG3 -o $(BUILD_DIR)/libmymalloc3.o -c $<
	ar -rv libmymalloc3.a $(BUILD_DIR)/libmymalloc3.o

libmymalloc4: $(SRC_DIR)/libmymalloc.cpp $(HEADERS)
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -pthread -D PROG4 -o $(BUILD_DIR)/libmymalloc4.o -c $<
	ar -rv libmymalloc4.a $(BUILD_DIR)/libmymalloc4.o

.PHONY: test
test:
	gcc -lpthread libmymalloc1.a -O sample_test.c
	./sample_test.a

clean:
	rm -f $(BUILD_DIR)/* *.a
