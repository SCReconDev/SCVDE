#include <stdio.h>
#include <stdlib.h>

void use_released_memory(int* ptr) {
    printf("Value: %d\n", *ptr);
}

int main() {
    int* ptr = (int*)malloc(sizeof(int));
    *ptr = 10;
    free(ptr);
    use_released_memory(ptr);
    return 0;
}