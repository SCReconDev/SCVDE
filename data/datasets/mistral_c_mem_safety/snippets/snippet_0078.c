#include <stdio.h>
#include <stdlib.h>

void release_memory(int** ptr) {
    free(*ptr);
    *ptr = NULL;
}

void use_memory(int* ptr) {
    printf("Value: %d\n", *ptr);
}

int main() {
    int* ptr = (int*)malloc(sizeof(int));
    *ptr = 10;
    release_memory(&ptr);
    use_memory(ptr);
    return 0;
}