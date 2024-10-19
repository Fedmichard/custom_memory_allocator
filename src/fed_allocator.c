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

    printf("Size: %zu\n", HEAP_TOTAL_SIZE);
    printf("Size: %p\n", heapStart->next);
    printf("Size: %p\n", MyHeapArea);
    printf("Size: %p", (void*)heapStart);
}

// To Allocate new memory region, list is traversed and searched for best free memory
// (Best Fit)
// Smallest available free block
void* heapAlloc(size_t size) {
    MyHeapNode* currentHeapBlock;
    MyHeapNode* bestHeapBlock;
    uint32_t bestHeapBlockSize;

    // Initialize current block to start of the heap
    currentHeapBlock = heapStart;
    // Initialize best heap block to nothing for now
    bestHeapBlock = (MyHeapNode*)NULL;
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

    if (bestHeapBlock != NULL) {
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