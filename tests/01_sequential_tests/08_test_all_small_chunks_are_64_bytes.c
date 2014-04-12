/*
 * Author: Cody Mingus
 *
 * Purpose: Ensure that all small requests return chunks of size 64.
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
		char* chunk = (char*) myMalloc(1);
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
                fprintf(stderr, "Failed: Test each small chunk is 64B\n");
                fprintf(stderr, "All calls to malloc should return 64B\n");
                fprintf(stderr, "when: size <= 64\n");
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
