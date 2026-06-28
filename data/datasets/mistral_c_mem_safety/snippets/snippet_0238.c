#include <stdio.h>
#include <stdlib.h>

void release_memory(int *ptr) {
    free(ptr);
    printf("Memory released.\n");
}

int main() {
    int *data = (int *)malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }
    release_memory(data);
    printf("Using released memory: %d\n", data[0]);
    return 0;
}