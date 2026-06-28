#include <stdio.h>
#include <stdlib.h>

void free_memory(int *ptr) {
    free(ptr);
    printf("Memory freed.\n");
}

int main() {
    int *data = (int *)malloc(5 * sizeof(int));
    for (int i = 0; i < 5; i++) {
        data[i] = i;
    }
    free_memory(data);
    printf("Data[0]: %d\n", data[0]);
    return 0;
}