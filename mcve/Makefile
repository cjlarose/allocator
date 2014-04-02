 .PHONY: all clean
 all:
	g++ -std=c++0x -c -o mcve.o mcve.cpp
	ar -rv libmcve.a mcve.o
	gcc -pthread sample_test.c -L. -lmcve

clean:
	rm -f *.a *.o
