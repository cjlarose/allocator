/*
 * Author: Cody Mingus
 *
 * Purpose: Ensure that all large requests return chunks of size 1024.
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
    int i, j;
    char* chunks[NUM_LARGE_CHUNKS];

    // Allocate all the chunks
    for (i = 0; i < NUM_LARGE_CHUNKS; i++) {
		char* chunk = (char*) myMalloc(65);
		chunks[i] = chunk;
        mark(chunks[i], LARGE_CHUNK_SIZE, 0);
    }

    // Make sure that modifying one chunk doesn't change another
    for (i = 0; i < NUM_LARGE_CHUNKS; i++) {
        mark(chunks[i], LARGE_CHUNK_SIZE, 99);
        for (j = 0; j < NUM_LARGE_CHUNKS; j++) { // n squared. Oh god.
            if (i == j) {
                continue;
            }
            if (isMarked(chunks[j], LARGE_CHUNK_SIZE) && *chunks[j] == 99) {
                fprintf(stderr, "Failed: Test each large chunk is 1024B\n");
                fprintf(stderr, "All calls to myMalloc should return 1024\n");
                fprintf(stderr, "when: 64 > size <= 1024\n");
                exit(1);
            }
        }
        mark(chunks[i], LARGE_CHUNK_SIZE, 0);
    }

    // Free ALL the things
    for (i = 0; i < NUM_LARGE_CHUNKS; i++) {
    	myFree(chunks[i]);
    }

    return 0;
}
