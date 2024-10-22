#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "fed_allocator.h"

#define HEAP_NODE_SIZE sizeof(MyHeapNode) // Size of a single node in our heap
#define HEAP_TOTAL_SIZE (4 * 1024) // Size of the entire size of heap (4kb which is typical size of Node)

typedef struct MyHeapNodeType {
    uint32_t size; // Size of memory segment in bytes, without size of control data
    uint8_t used; // (Size of Bool) Flag to track if memory block is being used
    struct MyHeapNodeType* next; // Pointer to next node in list
    struct MyHeapNodeType* prev; // Pointer to previous node in list
} MyHeapNode; // Alias to MyHeapNode (so I don't have to write struct each time I use it)

// Static Means it can only be accessed within this file and its lifetime is throughout program duration
static unsigned char MyHeapArea[HEAP_TOTAL_SIZE]; 
static MyHeapNode* heapStart = (MyHeapNode*)MyHeapArea; // Never Modified and will always point at start of heap list

// Initializing our heap by setting up the first node of the heap
void heapInit() {
    heapStart = (MyHeapNode*)MyHeapArea;
    heapStart->size = HEAP_TOTAL_SIZE - HEAP_NODE_SIZE;
    heapStart->next = NULL;
    heapStart->prev = NULL;
}

// To Allocate new memory region, list is traversed and searched for best free memory
// (Best Fit)
// Smallest available free block
// malloc()
void* heapAlloc(size_t size) {
    MyHeapNode* currentHeapBlock;
    MyHeapNode* bestHeapBlock;
    uint32_t bestHeapBlockSize;

    // Initialize current block to start of the heap
    currentHeapBlock = heapStart;
    // Initialize best heap block to nothing for now
    bestHeapBlock = (MyHeapNode*)NULL; // No real reason to this since NULL will already defined as pointer constant
    // Initialize with an invalid size
    bestHeapBlockSize = HEAP_TOTAL_SIZE + 1;

    while (currentHeapBlock) {
        // Check if the current block matches and fits the best (so far)
        if ( (!currentHeapBlock->used) &&
             (currentHeapBlock->size >= size + HEAP_NODE_SIZE) &&
             (currentHeapBlock->size <= bestHeapBlockSize)) {

            bestHeapBlock = currentHeapBlock;
            bestHeapBlockSize = currentHeapBlock -> size;
        }

        currentHeapBlock = currentHeapBlock->next;
    }

    // If there was a best heap block found
    if (bestHeapBlock != NULL) {
        // new pointer that will point to allocated block
        MyHeapNode* heapNodeAllocate;

        // Found a block that matches, split it and return the top of the memory area to the user
        // The best matching block is decreased by the needed memory area
        bestHeapBlock->size = bestHeapBlock->size - size - HEAP_NODE_SIZE;
        // new heap node is after the current heap + the size of its control data + allocated memory size
        heapNodeAllocate = (MyHeapNode*)(((unsigned char*)bestHeapBlock) + HEAP_NODE_SIZE + bestHeapBlock->size);
        heapNodeAllocate->size = size;
        heapNodeAllocate->used = 1;
        heapNodeAllocate->next = bestHeapBlock->next;
        heapNodeAllocate->prev = bestHeapBlock;

        if (bestHeapBlock->next != NULL) {
            // next block exists
            bestHeapBlock->next->prev = heapNodeAllocate;
        }

        bestHeapBlock->next = heapNodeAllocate;

        // return pointer to memory of new heap node after control data
        return (void*)((unsigned char*)heapNodeAllocate + HEAP_NODE_SIZE);
    }
    
    return NULL;
}

// free()
// can take any data type pointer
void heapFree(void* ptr) {
    if (ptr == NULL) {
        return;
    }

    /* get actual healp node */
    MyHeapNode* currentNode = (MyHeapNode*)((unsigned char*)ptr - HEAP_NODE_SIZE);

    // check if the current node exists in our stack, if it is null return
    if (currentNode == NULL) {
        return;
    }

    // set the current node to be "unused"
    currentNode->used = 0;

    // now check if we can merge with next block
    // if the next node exists
    if (currentNode->next) {
        // if the next node isn't being used (== 0)
        if (!currentNode->next->used) {
            // add the size of the next block and its control data to current block
            currentNode->size += currentNode->prev->size;
            currentNode->size += HEAP_NODE_SIZE;

            // remove the next block
            // link current block to the next-next block
            currentNode->next = currentNode->next->next;

            // link next next block to current block if next next block exists
            // current->next already points to next-next block
            if (currentNode->next != NULL) {
                currentNode->next->prev = currentNode;
            }
        }
    }

    //check if we can merge the previous block
    if (currentNode->prev) {
        // check if the previous block is being used
        if (!currentNode->prev->used) {
            // add size of freed memory region and its control data to previous block
            currentNode->prev->size += currentNode->size;
            currentNode->prev->size += HEAP_NODE_SIZE;

            // remove freed block from list
            // link previous block to next block
            currentNode->prev->next = currentNode->next;
        }
    }
}

void* heapRealloc(void* ptr, size_t size) {
    void* p;

    // allocate new block of requested size
    p = heapAlloc(size);
    // if p == null
    if (!p) {
        return p; // return null in case of failure
    }

    // copy buffer of original block
    if (ptr) {
        size_t sizeToCopy;
        size_t originalSize = ((MyHeapNode*)((unsigned char*)ptr - HEAP_NODE_SIZE))->size;

        // copy data of original memory to new only
        if (originalSize < size) {
            sizeToCopy = originalSize;
        } else {
            sizeToCopy = size;
        }


    }
}