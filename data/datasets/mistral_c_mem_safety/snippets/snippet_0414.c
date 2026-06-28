#include <stdio.h>
#include <stdlib.h>

void allocate_memory() {
    int *ptr = (int *)malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        ptr[i] = i;
    }
}

int main() {
    allocate_memory();
    printf("Memory allocated and used\n");
    return 0;
}