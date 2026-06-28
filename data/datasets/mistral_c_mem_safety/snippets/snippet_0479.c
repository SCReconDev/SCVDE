#include <stdio.h>
#include <stdlib.h>

int *create_array(int size) {
    int *ptr = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        ptr[i] = i;
    }
    return ptr;
}

int main() {
    int *array = create_array(10);
    printf("Array created.\n");
    return 0;
}