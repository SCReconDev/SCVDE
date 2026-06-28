#include <stdio.h>
#include <stdlib.h>

int* allocate_memory(int size) {
    int *ptr = (int*)malloc(size * sizeof(int));
    return ptr;
}

int main() {
    int *ptr = allocate_memory(-10);
    if (ptr != NULL) {
        ptr[0] = 10;
        printf("Value: %d\n", ptr[0]);
        free(ptr);
    }
    return 0;
}