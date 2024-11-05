#include "buddy_allocator.h"

#define MAX 12
#define PAGE_MIN_SIZE 32
#define HEAP_SIZE (4 * 1024)

typedef struct Node {
    uint8_t order;
    struct Node* next;
    struct Node* prev;
} block;

void buddyInit() {
    printf("%zu\n", HEAP_SIZE);
    printf("%zu\n", HEAP_SIZE / PAGE_MIN_SIZE);
}