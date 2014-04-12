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
    int i;
    char* large_chunks[NUM_LARGE_CHUNKS];
    char* small_chunks[NUM_SMALL_CHUNKS];

    // Mark each memory location
    for (i = 0; i < NUM_LARGE_CHUNKS; i++) {
		char* chunk = (char*) myMalloc(LARGE_CHUNK_SIZE);
		mark(chunk, LARGE_CHUNK_SIZE, i);
		large_chunks[i] = chunk;
    }
    for (i = 0; i < NUM_SMALL_CHUNKS; i++) {
		char* chunk = (char*) myMalloc(SMALL_CHUNK_SIZE);
		mark(chunk, SMALL_CHUNK_SIZE, i);
		small_chunks[i] = chunk;
    }

    // Free ALL the things
    for (i = 0; i < NUM_LARGE_CHUNKS; i++) {
    	myFree(large_chunks[i]);
    }
    for (i = 0; i < NUM_SMALL_CHUNKS; i++) {
    	myFree(small_chunks[i]);
    }

    // Re-malloc and make sure that each one was marked.
    for (i = 0; i < NUM_LARGE_CHUNKS; i++) {
		char* chunk = (char*) myMalloc(LARGE_CHUNK_SIZE);
		if (!isMarked(chunk, LARGE_CHUNK_SIZE)) {
			fprintf(stderr, "Failed: Test all chunks are disjoint ");
			fprintf(stderr, "Iteration Number: %d/%d\n", i, NUM_LARGE_CHUNKS);
			fprintf(stderr, "This may be because your pointers ");
			fprintf(stderr, "Are not lined up after being\nallocated the ");
			fprintf(stderr, "second time, or because they weren't evenly ");
			fprintf(stderr, "spaced when created. This\ncould also be caused ");
			fprintf(stderr, "by something else.\n");
			exit(1);
		}
    }
    for (i = 0; i < NUM_SMALL_CHUNKS; i++) {
		char* chunk = (char*) myMalloc(SMALL_CHUNK_SIZE);
		if (!isMarked(chunk, SMALL_CHUNK_SIZE)) {
			fprintf(stderr, "Failed: Test all chunks are disjoint ");
			fprintf(stderr, "Iteration Number: %d/%d\n", i, NUM_SMALL_CHUNKS);
			fprintf(stderr, "This may be because your pointers ");
			fprintf(stderr, "Are not lined up after being\nallocated the ");
			fprintf(stderr, "second time, or because they weren't evenly ");
			fprintf(stderr, "spaced when created. This\ncould also be caused ");
			fprintf(stderr, "by something else.\n");
			exit(1);
		}
    }

    return 0;
}
