#include "my_malloc.h"
#include <math.h>

/* You *MUST* use this macro when calling my_sbrk to allocate the 
 * appropriate size. Failure to do so may result in an incorrect
 * grading!
 */
#define SBRK_SIZE 2048

/* If you want to use debugging printouts, it is HIGHLY recommended
 * to use this macro or something similar. If you produce output from
 * your code then you will receive a 20 point deduction. You have been
 * warned.
 */
#ifdef DEBUG
#define DEBUG_PRINT(x) printf x
#else
#define DEBUG_PRINT(x)
#endif


/* make sure this always points to the beginning of your current
 * heap space! if it does not, then the grader will not be able
 * to run correctly and you will receive 0 credit. remember that
 * only the _first_ call to my_malloc() returns the beginning of
 * the heap. sequential calls will return a pointer to the newly
 * added space!
 * Technically this should be declared static because we do not
 * want any program outside of this file to be able to access it
 * however, DO NOT CHANGE the way this variable is declared or
 * it will break the autograder.
 */
void* heap;

/* our freelist structure - this is where the current freelist of
 * blocks will be maintained. failure to maintain the list inside
 * of this structure will result in no credit, as the grader will
 * expect it to be maintained here.
 * Technically this should be declared static for the same reasons
 * as above, but DO NOT CHANGE the way this structure is declared
 * or it will break the autograder.
 */
metadata_t* freelist[8];
/**** SIZES FOR THE FREE LIST ****
 * freelist[0] -> 16
 * freelist[1] -> 32
 * freelist[2] -> 64
 * freelist[3] -> 128
 * freelist[4] -> 256
 * freelist[5] -> 512
 * freelist[6] -> 1024
 * freelist[7] -> 2048
 */

 // static function prototypes
 static void setupHeap();
 static int getIdx(int request_size);
 static void splitBlock(int splitIdx, int neededIdx, metadata_t *currBlock);
 static void mergeBlock(int mergeIdx, metadata_t *currBlock);

void* my_malloc(size_t size)
{
  	// calculate the needed size
	int total_size = size + sizeof(metadata_t);

	// if the requested size is beyond our largest block size
	if (total_size > SBRK_SIZE) {
		ERRNO = SINGLE_REQUEST_TOO_LARGE;
		return NULL;
	}
	// set up the heap if it is uninitialized
	if (!heap) {
		setupHeap();
		if (ERRNO == OUT_OF_MEMORY) {
			return NULL;
		}
	}
	// get index of the free list to allocate memory to the user
	int idx = getIdx(total_size);
	metadata_t *allocBlock = NULL;
	// if we have a memory block to allocate
	if (freelist[idx] != NULL) {
		// just simply return the first block
		allocBlock = freelist[idx];
		// if there is the next block
		if (allocBlock->next != NULL) {
			allocBlock->next->prev = NULL;
			freelist[idx] = allocBlock->next;
		} else {
			freelist[idx] = NULL;
		}
		// remove this block/
		allocBlock->in_use = 1;
		allocBlock->prev = NULL;
		allocBlock->next = NULL;

		// return the block
		return ((char*)allocBlock + sizeof(metadata_t));
	}
	// if we do not have a memory block to allocate
	// we split the second smallest blocks into blocks of needed size
	int splitIdx = idx + 1;
	while (freelist[splitIdx] == NULL) {
		splitIdx++;
	}
	// if there are no blocks to split
	if (splitIdx == 8) {
		// set up a new heap
		setupHeap();
		if (ERRNO == OUT_OF_MEMORY) {
			return NULL;
		}
	} else { // if a block can be split 
		splitBlock(splitIdx, idx, freelist[splitIdx]); // a recursive function
	}
	// call my_malloc() again to allocate memory
	allocBlock = my_malloc(size);
    // set the error code
    ERRNO = NO_ERROR;

  	return allocBlock;
}

void* my_calloc(size_t num, size_t size)
{
    // calculate the real size
    int realSize = num * size;
    // pass the real size to my_malloc()
    void* p = my_malloc(realSize);
    // set the allocated memory to 0
    char *ptr = (char*) p;
    char *end = ptr + realSize;
    while (ptr < end) {
        // dereference char pointer and give it the value 0
        *ptr = 0;
        ptr++;
    }
    // set the error code
    ERRNO = NO_ERROR;

    return p;
}

void my_free(void* ptr)
{
    // get the address of the metadata
    char *p = (char*) ptr;
    // get the address of the current 
    metadata_t *currBlock = (metadata_t*)(p - sizeof(metadata_t));
    // detect double free
    if (!currBlock->in_use) {
        ERRNO = DOUBLE_FREE_DETECTED;
        return;
    } else {
        currBlock->in_use = 0;
    }
    // recursively merge blocks if possible
    int idx = getIdx(currBlock->size);
    mergeBlock(idx, currBlock);

    // set the error code
    ERRNO = NO_ERROR;
}

void* my_memmove(void* dest, const void* src, size_t num_bytes)
{
    char *d = (char *) dest;
    char *s = (char *) src;

    for (int i = 0; i < num_bytes; i++) {
    	d[i] = s[i];
    }
    // set the error code
    ERRNO = NO_ERROR;
  	return (void *) dest;
}




/*~~~~~~~~~~~~~HELPER FUNCTIONS~~~~~~~~~~~~~*/
static void setupHeap() {
	freelist[7] = my_sbrk(SBRK_SIZE);
	// if there is no space on the heap
	if ((int)freelist[7] == -1) {
		// set error code
		ERRNO = OUT_OF_MEMORY;
	}
	freelist[7]->in_use = 0;
	freelist[7]->size = SBRK_SIZE;
	freelist[7]->next = NULL;
	freelist[7]->prev = NULL;
	heap = freelist[7];
}

static int getIdx(int request_size) {
	int block_size = 16;
	int i = 0;
	while (i < 8) {
		if (request_size <= block_size) {
			return i;
		}
		block_size *= 2;
		i++;
	}
	return 0;
}

static void splitBlock(int splitIdx, int neededIdx, metadata_t *currBlock) {
	// base condition
	if (splitIdx == neededIdx) {
		return;
	} else {
		// if there is a buddy, split the first one
		if (currBlock->next != NULL) {
			metadata_t *temp = currBlock->next;
			// remove the splited block
			currBlock->prev = NULL;
			currBlock->next = NULL;
			currBlock->size /= 2;
			currBlock->in_use = 0;
			// next block becomes the head
			temp->prev = NULL;
			freelist[splitIdx] = temp;
		} else {
            // if there is not a buddy, split it directly
            currBlock->prev = NULL;
            currBlock->size /= 2;
            currBlock->in_use = 0;
			freelist[splitIdx] = NULL;
		}
		// the addresses of two new blocks
        splitIdx--;
        freelist[splitIdx] = currBlock;

		metadata_t *newBlock = (metadata_t *) ((char *) currBlock + currBlock->size);
		newBlock->size = currBlock->size;
		newBlock->in_use = 0;
		newBlock->next = NULL;
		newBlock->prev = currBlock;
        currBlock->next = newBlock;
        
		// recursion occurs here!
		splitBlock(splitIdx, neededIdx, currBlock);
	}
}

static void mergeBlock(int mergeIdx, metadata_t *currBlock) {
	// base case
	if (mergeIdx == 7) {
		return;
	}
	// add the current block to the freelist
	if (freelist[mergeIdx] != NULL) { // if there is any other blocks in the freelist[mergeIdx]
		freelist[mergeIdx]->prev = currBlock;
		currBlock->next = freelist[mergeIdx];
	}
	freelist[mergeIdx] = currBlock;
    // calculate the potential address (metadata address) of the buddy block
    metadata_t *buddyBlock = (metadata_t*) ((char*)currBlock + currBlock->size);
    if (buddyBlock == NULL) {
    	return;
    }
    // see if the buddy is free
    if (buddyBlock->in_use) {
    	return;
    }
    // see if two blocks are of the same size
    if (currBlock->size != buddyBlock->size) {
        return;
    }
    // see if two blocks are paired correctly
    int shift = (int)log2(currBlock->size) + 1;
    int currBit = ((int)((char*)currBlock-(char*)heap)) >> shift & 1;
    int buddyBit = ((int)((char*)buddyBlock-(char*)heap)) >> shift & 1;
    if (currBit != buddyBit) {
        return;
    }

    /*~~~~~~~if all criteira are met, merge the two blocks~~~~~~~*/

    currBlock->size *= 2;
    currBlock->in_use = 0;
    currBlock->next = NULL;
    currBlock->prev = NULL;
    // remove the two blocks from the free list
    if (buddyBlock->prev != NULL) {
    	buddyBlock->prev->next = buddyBlock->next;
    	if (buddyBlock->next != NULL) {
    		buddyBlock->next->prev = buddyBlock->prev;
    	}
    	buddyBlock->prev = NULL;
    	buddyBlock->next = NULL;
    	buddyBlock = NULL;
    }
    if (currBlock->next != NULL) {
    	freelist[mergeIdx] = currBlock->next;
    } else {
    	freelist[mergeIdx] = NULL;
    }
    // recursion occurs here!
    mergeBlock(mergeIdx++, currBlock);
}
