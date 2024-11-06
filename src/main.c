#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "buddy_allocator.h"
#include "fed_allocator.h"

int main() {
    /************************************************************
     * TESTING
     * **********************************************************/
    size_t num1 = 1000;
    size_t num2 = 1000;
    size_t num3 = 1000;
    size_t num4 = 1000;
    size_t num5 = 500;

    /*
    heapInit();
    printf("\nHeap Initialized.\n\n");

    void* node1 = heapAlloc(num1);

    if (node1) {
        printf("%u bytes at address: 0x%08X, stored in node1 successfully.\n", num1, node1);
    } else {
        printf("Failed to Allocate\n");
    }

    void* node2 = heapAlloc(num2);

    if (node2) {
        printf("%u bytes at address: 0x%08X, stored in node1 successfully.\n", num2, node2);
    } else {
        printf("Failed to Allocate\n");
    }

    printHeap();
    heapFree(node1);
    printHeap();

    */

    buddy_init();

    buddy_alloc(1000);

    print_heap();

}