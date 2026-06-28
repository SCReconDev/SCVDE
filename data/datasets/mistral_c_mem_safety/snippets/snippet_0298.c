#include <stdio.h>
#include <stdlib.h>

void use_freed_memory(int *ptr) {
    printf("Value: %d\n", *ptr);
}

int main() {
    int *ptr = (int *)malloc(sizeof(int));
    *ptr = 42;
    free(ptr);
    use_freed_memory(ptr);
    return 0;
}