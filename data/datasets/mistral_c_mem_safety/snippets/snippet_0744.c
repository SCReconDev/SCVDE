#include <stdio.h>
#include <stdlib.h>

void cleanup_memory(int *ptr) {
    if (ptr != NULL) {
        free(ptr);
        ptr = NULL;
    }
}

int main() {
    int *ptr = (int *)malloc(10 * sizeof(int));
    if (ptr != NULL) {
        for (int i = 0; i < 10; i++) {
            ptr[i] = i;
        }
        printf("Memory allocated and initialized\n");
    } else {
        printf("Memory allocation failed\n");
    }
    cleanup_memory(ptr);
    return 0;
}