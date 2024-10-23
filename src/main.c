#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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

    size_t k;

    heapInit();
    printf("Heap Initialized.\n");

    void* node1 = heapAlloc(num1);

    if (node1) {
        printf("%u bytes at address: %p, stored in node1 successfully.\n", num1, node1);
    } else {
        printf("Failed to Allocate\n");
    }

    void* node2 = heapAlloc(num2);

    if (node2) {
        printf("%u bytes at address: %p, stored in node1 successfully.\n", num2, node2);
    } else {
        printf("Failed to Allocate\n");
    }

    void* node3 = heapAlloc(num3);

    if (node3) {
        printf("%u bytes at address: %p, stored in node1 successfully.\n", num3, node3);
    } else {
        printf("Failed to Allocate\n");
    }
    
    void* node5 = heapRealloc(node3, num5);

    if (node5) {
        printf("%u bytes at address: %p, reallocated.\n", num5, node5);
    } else {
        printf("Failed to Allocate\n");
    }

    heapFree(node5);
    printf("Freed space in %p\n", node5);

    void* node4 = heapAlloc(num4);

    if (node4) {
        printf("%u bytes at address: %p, stored in node1 successfully.\n", num4, node4);
    } else {
        printf("Failed to Allocate\n");
    }

}