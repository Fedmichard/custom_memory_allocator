#ifndef FED_ALLOCATOR_H
#define FED_ALLOCATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void heapInit();

void* heapAlloc();
void heapFree(void* ptr);
void* heapRealloc(void* ptr, size_t size);
void* heapCalloc(size_t num, size_t size);

void* heapCopy(void* dest, const void* source, size_t num);
void* heapSet(void* ptr, int value, size_t num);

static void printHeapHeader();
void printHeap();

#endif