#include <stdio.h>
#include <stdlib.h>
#include "test1.h"

int main () {
    void* ptr = malloc(6);
    // void* arr = calloc();
    printf(ptr);
    free(ptr);
    // realloc(ptr);

    printf("Hello World!\n");
    print("My Name is Fed!");

    return 0;
}