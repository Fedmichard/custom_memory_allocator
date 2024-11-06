#include "buddy_allocator.h"

static uint8_t MyHeap[HEAP_SIZE];

BuddyAllocator allocator = {.memory = MyHeap};

/**
 * right now there's 7 different levels from 0 - 12
 * since our minimum is n = 5 or 2^(5) = 32
 * max is 4096 (2^12)
 * 12 - 5 = 7 different levels
 * level 7 = 4096
 * level 1 = 32
 * level 0 = <32
 */
int get_order(size_t size) {
    // order will start at 0 which represents < 32
    int order = 0;
    /**
     * if size = 1000
     * 1000 + 32 - 1 / 32
     * = 32. ...
     * 32 = 2^5 which means 1000 is level 5
     * 5/7 = 10/12 (1024 bits)
     */
    size = (size + PAGE_MIN_SIZE - 1) / PAGE_MIN_SIZE;

    while ((1 << order) < size) {
        order++;
    }
    
    return order;
}

void buddy_init() {
    for (int i = 0; i <= MAX; i++) {
        allocator.free[i] = NULL;
    }

    // Initialize the free list with the largest block at order 12
    allocator.free[MAX] = (Block*)allocator.memory;
    allocator.free[MAX]->size = HEAP_SIZE;
    allocator.free[MAX]->next = NULL;
    allocator.free[MAX]->prev = NULL;
}

static void buddy_split(BuddyAllocator* alloc, int order) {
    // grabs first free block from the given order (if 1000 bits then order 5)
    Block* block = alloc->free[order];

    // if no block is available for splitting
    if (!block) {
        return;
    }

    // removes the block from the list of free spaces
    // if someone tries to access this order later it will point to the next block
    alloc->free[order] = block->next;

    if (alloc->free[order]) {
        alloc->free[order]->prev = NULL;
    }

    // finds the half way point of that power of 2 order
    uint8_t half = (1 << order) / 2;
    
    // our two buddies;
    Block* buddy1 = block;
    Block* buddy2 = (Block*)((uint8_t*)block + half);

    // set buddy size
    buddy1->size = half;
    buddy2->size = half;

    // add buddy2 to the free list of the next smaller order
    // if the previous order was 2^10 each block would be separated in size 2^9 and 2^9
    // if order was 10, now its 9
    int new_order = order - 1;

    // updates the next pointer of the 2nd buddy to point to curr first block in free list
    // before we add buddy 2 to the list we make it point to head of the new list
    buddy2->next = alloc->free[new_order];

    // check if the new_order already has a block in it
    if (alloc->free[new_order]) {
        // if it does it makes that blocks prev point to buddy2
        alloc->free[new_order]->prev = buddy2;
    }

    alloc->free[new_order] = buddy2;

    // add buddy1 to the free list of the next smaller order
    // same process
    buddy1->next = alloc->free[new_order];

    if (alloc->free[new_order]) {
        alloc->free[new_order]->prev = buddy1;
    }

    alloc->free[new_order] = buddy1;
}

void* buddy_alloc(size_t size) {
    // get the order of requested size
    // if size is 1000, order is 10
    int order = get_order(size);
    printf("%zu\n", order);
    
    if (order > MAX) {
        // out of memory (request is too large)
        return NULL;
    }

    for (int i = order; i <= MAX; i++) {
        if (allocator.free[i]) {
            Block* allocated = allocator.free[i];

            // if the block is larger, split it into smaller blocks
            if (i > order) {
                buddy_split(&allocator, i);
            }

            // remove the block from the free list and return it
            /*
            Block* allocated = allocator.free[i];
            allocator.free[i] = allocated->next;
            return allocated;
            */

           // remove the block from the free list
           allocator.free[i] = allocated->next;

           if (allocator.free[i]) {
            allocator.free[i]->prev = NULL;
           }

           // mark the block as allocated
           allocated->next = NULL;

           // return allocated block back to the user 
           return (void*)allocated;
        }
    }
    
    return NULL;
}

/**
 * TESTING
 */

// Function to print the entire heap memory (in hexadecimal)
void print_heap() {
    printf("Heap State (Block List):\n");

    // Traverse each order of the free list
    for (int i = 0; i <= MAX; i++) {
        Block* current = allocator.free[i];
        if (current) {
            printf("Order %d (Block size: %zu bytes):\n", i, (size_t)(1 << i));

            // Traverse the blocks in the current free list order
            while (current) {
                printf("  Block at %p: size = %d, next = %p, prev = %p\n", 
                       (void*)current, 
                       current->size, 
                       (void*)current->next, 
                       (void*)current->prev);

                current = current->next;
            }
        } else {
            printf("Order %d: empty\n", i); // Output if no block in current order
        }
    }
}