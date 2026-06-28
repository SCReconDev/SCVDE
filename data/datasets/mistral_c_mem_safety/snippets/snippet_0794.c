#include <stdio.h>
#include <stdlib.h>

void cleanup_memory(int *ptr) {
    if (ptr != NULL) {
        free(ptr);
    }
}

int main() {
    int *ptr = (int *)malloc(10 * sizeof(int));
    if (ptr != NULL) {
        for (int i = 0; i < 10; i++) {
            ptr[i] = i;
        }
        cleanup_memory(ptr);
    } else {
        printf("Memory allocation failed\n");
    }
    return 0;
}