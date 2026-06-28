#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

int get_element(int *array, size_t index) {
    if (index >= ARRAY_SIZE) {
        fprintf(stderr, "Index out of bounds\n");
        return -1;
    }
    return array[index];
}

int main() {
    int array[ARRAY_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t index = 5;
    int element = get_element(array, index);
    if (element != -1) {
        printf("Element at index %zu: %d\n", index, element);
    }
    return 0;
}