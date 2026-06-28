#include <stdio.h>
#include <stdlib.h>

void use_released_memory(int *ptr) {
    printf("Using released memory: %d\n", *ptr);
}

int main() {
    int *ptr = (int *)malloc(sizeof(int));
    *ptr = 42;
    free(ptr);
    use_released_memory(ptr);
    return 0;
}