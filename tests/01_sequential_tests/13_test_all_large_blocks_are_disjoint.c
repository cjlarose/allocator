/*
 * Author: Cody Mingus
 *
 * Purpose: Ensure that each block does not over lap with any other blocks.
 */

#include "myMalloc.h"
#include <stdlib.h>
#include <stdio.h>

#define NUM_LARGE_CHUNKS 128
#define LARGE_CHUNK_SIZE 1024
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
    int i;
    void* chunks[NUM_LARGE_CHUNKS];

    // Mark each memory location
    for (i = 0; i < NUM_LARGE_CHUNKS; i++) {
		char* chunk = (char*) myMalloc(LARGE_CHUNK_SIZE);
		mark(chunk, LARGE_CHUNK_SIZE, i);
		chunks[i] = chunk;
    }

    // Free ALL the things
    for (i = 0; i < NUM_LARGE_CHUNKS; i++) {
    	myFree(chunks[i]);
    }

    // Re-malloc and make sure that each one was marked.
    for (i = 0; i < NUM_LARGE_CHUNKS; i++) {
		char* chunk = (char*) myMalloc(LARGE_CHUNK_SIZE);
		if (!isMarked(chunk, LARGE_CHUNK_SIZE)) {
			fprintf(stderr, "Iteration Number: %d/%d\n", i, NUM_LARGE_CHUNKS);
			fprintf(stderr, "Test Failed! This may be because your pointers ");
			fprintf(stderr, "Are not lined up after being\nallocated the ");
			fprintf(stderr, "second time, or because they weren't evenly ");
			fprintf(stderr, "spaced when created. This\ncould also be caused ");
			fprintf(stderr, "by something else.\n");
			exit(1);
		}
    }

    return 0;
}
