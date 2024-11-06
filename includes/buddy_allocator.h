#ifndef BUDDY_ALLOCATOR
#define BUDDY_ALLOCATOR

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define PAGE_MIN_SIZE 1
#define MAX 12
#define HEAP_SIZE (4 * 1024)

/*
 * A doubly linked list node structure for our memory blocks
 */
typedef struct Node {
    int size;
    struct Node* next;
    struct Node* prev;
} Block;

/*
 * encapsulates key components of the buddy memory allocator
 * to enable efficient management
 * defines the structure of the buddy allocator
 */
typedef struct BuddyAllocator {
    // Since each we can have 13 possible powers of 2, 2^(0 - 12) 
    // essentially splits our 4096 list into 12 "levels"
    Block* free[MAX + 1];
    /**
     * holds the pointer to a block of memory where allocator will manage allocations
     * points to contiguous block of memory we will manage one byte at a time
     * pointer to base address that the buddy allocator will perform
     * pointing to start of heap address
     */
    uint8_t* memory;
} BuddyAllocator;

int get_order(size_t size);
void buddy_init();
void* buddy_alloc(size_t size);

/**
 * TESTING
 */

void print_heap();

#endif