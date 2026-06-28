#include <stdio.h>
#include <stdlib.h>

void use_freed_memory() {
    int *ptr = (int *)malloc(sizeof(int));
    *ptr = 10;
    free(ptr);
    printf("Value: %d\n", *ptr);
}

int main() {
    use_freed_memory();
    return 0;
}