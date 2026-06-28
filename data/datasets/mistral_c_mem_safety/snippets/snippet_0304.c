#include <stdio.h>
#include <stdlib.h>

void allocate_memory(int size) {
    int *ptr = (int*) malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        ptr[i] = i;
    }
}

int main() {
    allocate_memory(10);
    return 0;
}