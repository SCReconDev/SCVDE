#include <stdio.h>
#include <stdlib.h>

int* safeResourceAllocation(size_t size) {
    int *ptr = (int*)malloc(size * sizeof(int));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    return ptr;
}

int main() {
    size_t size = 10;
    int *ptr = safeResourceAllocation(size);
    if (ptr != NULL) {
        for (size_t i = 0; i < size; i++) {
            ptr[i] = i;
        }
        free(ptr);
    }
    return 0;
}