#include <stdio.h>
#include <stdlib.h>

void cleanup_memory() {
    int *ptr = (int *)malloc(sizeof(int));

    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    *ptr = 42;
    printf("Allocated value: %d\n", *ptr);

    free(ptr);
    ptr = NULL;
}

int main() {
    cleanup_memory();
    return 0;
}