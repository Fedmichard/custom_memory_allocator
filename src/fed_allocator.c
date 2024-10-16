#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "fed_allocator.h"

struct HeapNode {
    uint32_t size;
};

void fedAlloc() {
    printf("In Fed's Memory Allocator");
}