#include <stdio.h>
#include <stdlib.h>

void release_memory(int* ptr) {
    free(ptr);
    printf("Memory released\n");
}

int main() {
    int* ptr = (int*)malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        ptr[i] = i;
    }
    release_memory(ptr);
    printf("Value: %d\n", ptr[0]);
    return 0;
}