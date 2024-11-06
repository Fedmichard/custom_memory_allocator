#include "buddy_allocator.h"

static uint8_t MyHeap[HEAP_SIZE];
BuddyAllocator allocator = {.memory = MyHeap};

int get_order(size_t size) {
    int order = 0;
    size = (size + PAGE_MIN_SIZE - 1) / PAGE_MIN_SIZE;

    while ((1 << order) < size) {
        order++;
    }
    
    return order;
}

void buddy_init() {

    // Initialize the free list with a single large block
    allocator.free[MAX] = (Block*)allocator.memory;
    allocator.free[MAX]->size = HEAP_SIZE;
    allocator.free[MAX]->next = NULL;
    allocator.free[MAX]->prev = NULL;
}

void buddy_split(int order) {
    if (order <= 0 || allocator.free[order] == NULL) {
        return;
    }

    // Take the first block in the current order and split it
    Block* block = allocator.free[order];
    allocator.free[order] = block->next;  // Remove it from the free list

    size_t halfSize = (1 << (order - 1)); // New size for split blocks

    Block* buddy1 = block;
    Block* buddy2 = (Block*)((uint8_t*)block + halfSize);

    buddy1->size = halfSize;
    buddy2->size = halfSize;

    // Insert buddies into the next lower order
    int new_order = order - 1;
    buddy1->next = allocator.free[new_order];
    if (allocator.free[new_order]) {
        allocator.free[new_order]->prev = buddy1;
    }
    allocator.free[new_order] = buddy1;

    buddy2->next = allocator.free[new_order];
    if (allocator.free[new_order]) {
        allocator.free[new_order]->prev = buddy2;
    }
    allocator.free[new_order] = buddy2;
}

void* buddy_alloc(size_t size) {
    int order = get_order(size);
    if (order > MAX) {
        return NULL; // Out of memory
    }

    // First, check if there's a block at the requested level
    if (allocator.free[order] != NULL) {
        // If block is available at the requested level, use it
        Block* block = allocator.free[order];
        allocator.free[order] = block->next;
        if (allocator.free[order]) {
            allocator.free[order]->prev = NULL;
        }

        block->next = block->prev = NULL; // Disconnect the block
        return (void*)block;
    }

    // If no block at the requested level, search higher levels
    int current_order = order + 1;
    while (current_order <= MAX && allocator.free[current_order] == NULL) {
        current_order++;
    }

    if (current_order > MAX) {
        return NULL; // No available block large enough
    }

    // Split blocks from higher levels until we reach the requested level
    while (current_order > order) {
        buddy_split(current_order);
        current_order--;
    }

    // Allocate the block from the free list at the requested level
    Block* block = allocator.free[order];
    allocator.free[order] = block->next;
    if (allocator.free[order]) {
        allocator.free[order]->prev = NULL;
    }

    block->next = block->prev = NULL; // Disconnect the block
    return (void*)block;
}

void print_heap() {
    printf("Heap State (Block List):\n");

    // Iterate through each level in the free list
    for (int i = 0; i <= MAX; i++) {
        Block* current = allocator.free[i];
        if (current) {
            printf("Level %d (Block size: %zu bytes):\n", i, (size_t)(1 << i));

            size_t allocated_at_level = 0;  // Track total allocated size at this level

            // Iterate over the blocks in this level and print their details
            while (current) {
                printf("  Block at %p: size = %d, next = %p, prev = %p\n", 
                       (void*)current, 
                       current->size, 
                       (void*)current->next, 
                       (void*)current->prev);
                allocated_at_level += current->size; // Sum up the sizes of allocated blocks
                current = current->next;
            }

            // Display the total allocated size at this level
            if (allocated_at_level > 0) {
                printf("  Total allocated at level %d: %zu bytes\n", i, allocated_at_level);
            }
        } else {
            printf("Level %d: empty\n", i);
        }
    }
}