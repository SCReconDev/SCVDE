#include <stdio.h>
#include <stdlib.h>

void use_memory(int *ptr) {
    printf("Using memory: %d\n", *ptr);
}

int main() {
    int *ptr = (int *)malloc(sizeof(int));
    *ptr = 42;
    free(ptr);
    use_memory(ptr);
    return 0;
}