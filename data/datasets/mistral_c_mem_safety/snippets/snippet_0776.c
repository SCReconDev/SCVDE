#include <stdio.h>

#define ARRAY_SIZE 10

void iterate_array(int* array) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("Array element at index %d: %d\n", i, array[i]);
    }
}

int main() {
    int array[ARRAY_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    iterate_array(array);
    return 0;
}