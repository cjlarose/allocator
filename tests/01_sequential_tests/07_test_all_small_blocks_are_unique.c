/*
 * Author: Cody Mingus
 *
 * Purpose: Ensure that each block returned by myMalloc is unique block, not
 * one that has been returned by myMalloc before (unless it was free'd)
 */

#include "myMalloc.h"
#include <stdlib.h>
#include <stdio.h>

#define NUM_SMALL_CHUNKS 2048
#define SMALL_CHUNK_SIZE 64
typedef enum {false, true} bool;

void mark(char* memory, int size, int number) {
	int i;
	for (i = 0; i < size; i++) {
		memory[i] = (char) number;
	}
}

bool isMarked(char* memory, int size) {
	int i;
	for (i = 0; i < size-1; i++) {
		if (memory[i] != memory[i+1]) {
			return false;
		}
	}
	return true;
}

int main() {

	// Init and make a place to store the chunks.
    myInit(1);
    int i, j;
    char* chunks[NUM_SMALL_CHUNKS];

    // Allocate all the chunks
    for (i = 0; i < NUM_SMALL_CHUNKS; i++) {
		char* chunk = (char*) myMalloc(SMALL_CHUNK_SIZE);
		chunks[i] = chunk;
        mark(chunks[i], SMALL_CHUNK_SIZE, 0);
    }

    // Make sure that modifying one chunk doesn't change another
    for (i = 0; i < NUM_SMALL_CHUNKS; i++) {
        mark(chunks[i], SMALL_CHUNK_SIZE, 99);
        for (j = 0; j < NUM_SMALL_CHUNKS; j++) { // n squared. Oh god.
            if (i == j) {
                continue;
            }
            if (isMarked(chunks[j], SMALL_CHUNK_SIZE) && *chunks[j] == 99) {
                fprintf(stderr, "Failed: Test each small chunk is unique\n");
                fprintf(stderr, "Writing to one block of memory changed\n");
                fprintf(stderr, "information in a different chunk!\n");
                fprintf(stderr, "Make sure that each chunked returned is a\n");
                fprintf(stderr, "different spot in memory and whatever points\n");
                fprintf(stderr, "to the next free chunk is always updated.\n");
                exit(1);
            }
        }
        mark(chunks[i], SMALL_CHUNK_SIZE, 0);
    }

    // Free ALL the things
    for (i = 0; i < NUM_SMALL_CHUNKS; i++) {
    	myFree(chunks[i]);
    }

    return 0;
}
