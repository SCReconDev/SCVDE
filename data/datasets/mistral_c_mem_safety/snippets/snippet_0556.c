#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

void iterate_array() {
    int array[ARRAY_SIZE] = {0};
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("Element at index %d is %d\n", i, array[i]);
    }
}

int main() {
    iterate_array();
    return 0;
}